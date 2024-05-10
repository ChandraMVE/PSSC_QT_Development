


/**
 SERIALDEBUGDEBUG.C File

  @Company
    Microchip Technology Inc.

  @File Name
 SerialDebugDebug.c

  @Summary
    This is the file used to control the Loads

  @Description
    This source file provides SerialDebug communication with UART configurator,
 * 
 *
 */

#include "SerialDebug.h"
#include "mcc_generated_files/uart2.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/reset.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ADCRead.h"
#include "PistonMotor.h"
#include "ValveMotor.h"
#include "ShakerMotor.h"
#include "TemperatureControl.h"
#include "PistonEncoder.h"
#include "TECControl.h"
#include "Alarm.h"
#include "Error.h"

static uint8_t DebugRx_Data;
static uint8_t DebugRx_DataCounter;
static uint8_t DebugRx_Counter;
static uint16_t DebugTx_Counter;
static uint8_t DebugTx_AckVal;

static uint8_t DebugCRC_Array[64];

bool DebugFlag_ServiceRequest;
bool DebugFlag_TestRequest;
bool DebugFlag_AckStatus;

void SerialDebug_SendByte(uint8_t bData);
static int16_t SerialDebug_PrintString(const char * string, int16_t i);
static uint8_t SerialDebug_PrintInteger(uint32_t number, uint8_t digits);
static uint8_t SerialDebug_PrintFloat(float number, uint8_t afterPoint);
void SerialDebug_SendACK(void);
void SerialDebug_SendNACK(void);

/**
 * @brief This function initializes SerialDebug Variables
 * @param Nothing
 * @return Nothing
 */
void SerialDebug_Initialise(void)
{
    uint8_t tempCount = 0;
    uint16_t tempVal = 0;
    DebugRx_DataCounter = 0;
    DebugRx_Counter = 0;
    DebugTx_Counter = 0;
    DebugRx_Data = 0;
    DebugTx_AckVal = 0;
    DebugFlag_ServiceRequest = false;
    DebugFlag_TestRequest = false;
    DebugFlag_AckStatus = false;
    
    // Update Major minor and Test Version also with this changes
    tempCount = SerialDebug_PrintString("Version: v00.01.07\n\r\n", tempCount);
    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
    tempVal = RESET_GetCause();
    RESET_CauseClearAll();
    tempCount = 0;
    tempCount = SerialDebug_PrintString("Reset Value:\t", tempCount);
    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
    tempCount = SerialDebug_PrintInteger(tempVal, 5);
    tempCount = SerialDebug_PrintString("\n\r\n\r", tempCount);
    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
}

/**
 * @brief This function is Handler to perform serial debug operations
 * @param Nothing
 * @return Nothing
 */
void SerialDebug_Handler(void)
{

bool flagSet = false;
bool flagControl = false;
uint8_t tempCount = 0;
uint8_t fourthNum = 0;
uint8_t thirdNum = 0;
uint8_t secondNum = 0;
uint8_t firstNum = 0;
uint8_t recCrc = 0;
uint8_t bData = 0;
uint8_t i = 0;
uint8_t totalCount = 0;
uint16_t wData = 0;

volatile uint32_t tempWord = 0;

float fData = 0;

    switch ( SerialDebug.RxStatus) 
    {
        case SERIALDEBUG_STATE_IDLE:
            tempCount = UART2_ReadBuffer(SerialDebug.RxARRY, 0xFF);
            if (tempCount != 0) 
            {
                if ( SerialDebug.RxARRY[0] == '#') 
                {
                    SerialDebug.RxStatus = SERIALDEBUG_STATE_WAITING;
                    SerialDebug.RxIndex = tempCount;
                    DebugRx_Counter = SerialDebug.RxIndex;
                }
            }
            DebugTx_Counter++;
            if(DebugTx_Counter > MAX_WAITTIME)
            {
                DebugTx_Counter = 0;
                if ((DebugFlag_ServiceRequest == true) || (DebugFlag_TestRequest == true))
                {
                    DebugFlag_ServiceRequest = false;
                    DebugFlag_TestRequest = false;
                    //Continuous transmission of the following parameters.
                    SerialDebug_SendByte('#');
                    DebugCRC_Array[totalCount++] = '#';
                    if(DebugFlag_TestRequest == true)
                    {
                    //    Ambient Temperature
                        SerialDebug_SendByte('Y');
                        SerialDebug_SendByte('C');
                        wData = ADCRead_GetAmbTemp();
                        tempCount = SerialDebug_PrintInteger(wData, MAX_AMB_DIGIT);
                        tempCount = SerialDebug_PrintString(",", tempCount);
                        UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                        totalCount = totalCount + tempCount + 2;
                    }
                    else
                    {
                        SerialDebug_SendByte('Y');
                        DebugCRC_Array[totalCount++] = 'Y';
                    }
                    // Chamber Temperature
                    SerialDebug_SendByte('A');
                    DebugCRC_Array[totalCount++] = 'A';
                    tempWord = TemperatureControl_GetTempADC();
                    tempCount = SerialDebug_PrintInteger(tempWord, MAX_ADC_DIGIT);
                    tempCount = SerialDebug_PrintString(",", tempCount);
                    totalCount = SerialDebug_CRCArrayFill(SerialDebug.TxARRY, totalCount, tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                    
                    // Chamber Pressure
                    SerialDebug_SendByte('B');
                    DebugCRC_Array[totalCount++] = 'B';
                    tempWord = TemperatureControl_GetPressADC();
                    tempCount = SerialDebug_PrintInteger(tempWord, MAX_ADC_DIGIT);
                    tempCount = SerialDebug_PrintString(",", tempCount);
                    totalCount = SerialDebug_CRCArrayFill(SerialDebug.TxARRY, totalCount, tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                    
                    // Piston Position
                    SerialDebug_SendByte('F');
                    DebugCRC_Array[totalCount++] = 'F';
                    fData = PistonMotor_GetPostion();
                    tempCount = SerialDebug_PrintFloat(fData, DIGIT_AFTER_DECIMAL);
                    tempCount = SerialDebug_PrintString(",", tempCount);
                    totalCount = SerialDebug_CRCArrayFill(SerialDebug.TxARRY, totalCount, tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                    
                    // Valve Position
                    SerialDebug_SendByte('D');
                    DebugCRC_Array[totalCount++] = 'D';
                    bData = ValveMotor_GetPostion();
                    tempCount = SerialDebug_PrintInteger(bData, 0);
                    tempCount = SerialDebug_PrintString(",", tempCount);
                    totalCount = SerialDebug_CRCArrayFill(SerialDebug.TxARRY, totalCount, tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                    
                    // Shaker Speed
                    SerialDebug_SendByte('H');
                    DebugCRC_Array[totalCount++] = 'H';
                    tempWord = ShakerMotor_GetSpeed();
                    tempCount = SerialDebug_PrintInteger(tempWord, MAX_SHAKER_DIGIT);
                    tempCount = SerialDebug_PrintString(",", tempCount);
                    totalCount = SerialDebug_CRCArrayFill(SerialDebug.TxARRY, totalCount, tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                    
                    // Error Codes
                    SerialDebug_SendByte('E');
                    DebugCRC_Array[totalCount++] = 'E';
                    tempWord = Error_GetFaultCount();
                    tempCount = SerialDebug_PrintInteger(tempWord, 4);
                    tempCount = SerialDebug_PrintString(",", tempCount);
                    totalCount = SerialDebug_CRCArrayFill(SerialDebug.TxARRY, totalCount, tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                    
                    // Ack Status if any command is received
                    if(true == DebugFlag_AckStatus)
                    {
                        DebugFlag_AckStatus = false;
                        SerialDebug_SendByte('Z');
                        DebugCRC_Array[totalCount++] = 'Z';
                        tempWord = DebugTx_AckVal;
                        tempCount = SerialDebug_PrintInteger(tempWord, 2);
                        tempCount = SerialDebug_PrintString(",", tempCount);
                        totalCount = SerialDebug_CRCArrayFill(SerialDebug.TxARRY, totalCount, tempCount);
                        UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                    }
                    
                    // CRC Calculate
                    SerialDebug_SendByte('W');
                    tempWord = SerialDebug_CalCRC(DebugCRC_Array, totalCount);
                    tempCount = SerialDebug_PrintInteger(tempWord, 3);
                    tempCount = SerialDebug_PrintString("$", tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);

                }
                
//                SerialDebug_SendByte('E');
//                tempWord = Error_GetFaultCount();
//                tempCount = SerialDebug_PrintInteger(tempWord, 4);
//                tempCount = SerialDebug_PrintString("$", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                
//                fData = TECControl_GetPTerm();
//                tempCount = SerialDebug_PrintFloat(fData, 3);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                fData = TECControl_GetITerm();
//                tempCount = SerialDebug_PrintFloat(fData, 3);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                fData = TECControl_GetDTerm();
//                tempCount = SerialDebug_PrintFloat(fData, 3);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                
//                fData = PistonMotor_GetPostion();
//                tempCount = SerialDebug_PrintFloat(fData, DIGIT_AFTER_DECIMAL);
//                tempCount = SerialDebug_PrintString(",", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                bData = ValveMotor_GetPostion();
//                tempCount = SerialDebug_PrintInteger(bData, 0);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                
                fData = TECControl_GetPTerm();
                tempCount = SerialDebug_PrintFloat(fData, 3);
                tempCount = SerialDebug_PrintString(",\t", tempCount);
                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                fData = TECControl_GetITerm();
                tempCount = SerialDebug_PrintFloat(fData, 3);
                tempCount = SerialDebug_PrintString(",\t", tempCount);
                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                fData = TECControl_GetDTerm();
                tempCount = SerialDebug_PrintFloat(fData, 3);
                tempCount = SerialDebug_PrintString(",\t", tempCount);
                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                fData = TECControl_GetState();
                tempCount = SerialDebug_PrintFloat(fData, 0);
                tempCount = SerialDebug_PrintString(",\t", tempCount);
                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                tempWord = TECControl_GetValue();
                tempCount = SerialDebug_PrintInteger(tempWord, 0);
                tempCount = SerialDebug_PrintString(",\t", tempCount);
                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                tempWord = TemperatureControl_GetTempADC();
                tempCount = SerialDebug_PrintInteger(tempWord, 0);
                tempCount = SerialDebug_PrintString(",\t", tempCount);
                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                tempWord = TemperatureControl_GetPressADC();
                tempCount = SerialDebug_PrintInteger(tempWord, 0);
                tempCount = SerialDebug_PrintString(",\t", tempCount);
                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                tempWord = Error_GetFaultCount();
                tempCount = SerialDebug_PrintInteger(tempWord, 4);
                tempCount = SerialDebug_PrintString(",\t", tempCount);
                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);

//                tempWord = MAX_PRESS_LIMIT_COUNT;
//                tempCount = SerialDebug_PrintInteger(tempWord, 6);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = MAX_TEMP_LIMIT_COUNT;
//                tempCount = SerialDebug_PrintInteger(tempWord, 6);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = ADCRead_GetAmbTemp();
//                tempCount = SerialDebug_PrintInteger(tempWord, 3);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = PistonEncoder_GetCountA();
//                tempCount = SerialDebug_PrintInteger(tempWord, 5);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = PistonEncoder_GetCountB();
//                tempCount = SerialDebug_PrintInteger(tempWord, 5);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = (uint16_t)TECControl_GetStatus();
//                tempCount = SerialDebug_PrintInteger(tempWord, 1);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = (uint16_t)TECControl.ErrorFlags.TECTemp;
//                tempCount = SerialDebug_PrintInteger(tempWord, 1);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = (uint16_t)TECControl.ErrorFlags.TECPress;
//                tempCount = SerialDebug_PrintInteger(tempWord, 1);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = (uint16_t)TECControl_GetControl();
//                tempCount = SerialDebug_PrintInteger(tempWord, 1);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);

//                tempWord = (uint16_t)ValveMotor_GetSetPostion();
//                tempCount = SerialDebug_PrintInteger(tempWord, 1);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = (uint16_t)ValveMotor_GetPostion();
//                tempCount = SerialDebug_PrintInteger(tempWord, 1);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                
//                tempWord = (uint16_t)ValveMotor_GetStatus();
//                tempCount = SerialDebug_PrintInteger(tempWord, 1);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = (uint16_t)ValveMotor_GetState();
//                tempCount = SerialDebug_PrintInteger(tempWord, 1);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                
//                tempWord = (uint16_t)Error_GetFlag();
//                tempCount = SerialDebug_PrintInteger(tempWord, 1);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = (uint16_t)Error_GetCount();
//                tempCount = SerialDebug_PrintInteger(tempWord, 1);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
//                tempWord = (uint16_t)ShakerMotor_GetPulseErrCheck();
//                tempCount = SerialDebug_PrintInteger(tempWord, 1);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                tempWord = (uint16_t)ShakerMotor_ErrCounter();
                tempCount = SerialDebug_PrintInteger(tempWord, 1);
                tempCount = SerialDebug_PrintString(",\t", tempCount);
                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                
//                tempWord = (uint16_t)LoadState;
//                tempCount = SerialDebug_PrintInteger(tempWord, 0);
//                tempCount = SerialDebug_PrintString(",\t", tempCount);
//                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                
                tempCount = 0;
                tempCount = SerialDebug_PrintString("\n\r", tempCount);
                UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
            }
            
        break;

        case SERIALDEBUG_STATE_WAITING:
            // Check any remaining data received
            for(tempCount = 0; tempCount <= SerialDebug.RxIndex; tempCount++) 
            {
                // If End of Frame received
                if ( SerialDebug.RxARRY[tempCount] == '$') 
                {
                    SerialDebug.RxStatus = SERIALDEBUG_STATE_COMMAND;
                    break;
                }
            }
            tempCount = UART2_ReadBuffer(&SerialDebug.RxARRY[SerialDebug.RxIndex], 0xFF);
            if ( tempCount != 0) 
            {
                SerialDebug.RxIndex += tempCount;
                DebugRx_Counter = DebugRx_Counter + tempCount;
                
                for(tempCount = 0; tempCount < SerialDebug.RxIndex; tempCount++) 
                {
                    // If End of Frame received
                    if ( SerialDebug.RxARRY[tempCount] == '$') 
                    {
                        SerialDebug.RxStatus = SERIALDEBUG_STATE_COMMAND;
                        break;
                    }
                }
            }
            else
            {
                DebugRx_Counter++;
                if(DebugRx_Counter > MAX_WAITTIME)
                {
                    DebugRx_Counter = 0;
                    SerialDebug.RxStatus = SERIALDEBUG_STATE_IDLE;
                }
            }

        break;

        case SERIALDEBUG_STATE_COMMAND:
            // Process the command received
            switch (SerialDebug.RxARRY[1]) 
            {
                //Read Chamber Temperature
                case ('a') :
                case ('A') :
                    SerialDebug_SendByte('#');
                    SerialDebug_SendByte('A');
                    tempWord = TemperatureControl_GetTempADC();
                    tempCount = SerialDebug_PrintInteger(tempWord, MAX_ADC_DIGIT);
                    tempCount = SerialDebug_PrintString("$", tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);

                break;
                //Read Chamber Pressure
                case ('b') :
                case ('B') :
                    SerialDebug_SendByte('#');
                    SerialDebug_SendByte('B');
                    tempWord = TemperatureControl_GetPressADC();
                    tempCount = SerialDebug_PrintInteger(tempWord, MAX_ADC_DIGIT);
                    tempCount = SerialDebug_PrintString("$", tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);

                break;
                //Read Ambient Temperature
                case ('c') :
                case ('C') :
                    SerialDebug_SendByte('#');
                    SerialDebug_SendByte('C');
                    wData = ADCRead_GetAmbTemp();
                    tempCount = SerialDebug_PrintInteger(wData, MAX_AMB_DIGIT);
                    tempCount = SerialDebug_PrintString("$", tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);

                break;
                //Read Valve Position
                case ('d') :
                case ('D') :
                    SerialDebug_SendByte('#');
                    SerialDebug_SendByte('D');
                    bData = (uint8_t)ValveMotor_GetStatus();
                    tempCount = SerialDebug_PrintInteger(bData, 0);
                    tempCount = SerialDebug_PrintString(",", tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                    bData = ValveMotor_GetPostion();
                    tempCount = SerialDebug_PrintInteger(bData, 0);
                    tempCount = SerialDebug_PrintString("$", tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);

                break;
                //Read Piston Motor Status and Piston Position
                case ('f') :
                case ('F') :
                    SerialDebug_SendByte('#');
                    SerialDebug_SendByte('F');
                    bData = (uint8_t)PistonMotor_GetStatus();
                    tempCount = SerialDebug_PrintInteger(bData, 0);
                    tempCount = SerialDebug_PrintString(",", tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                    fData = PistonMotor_GetPostion();
                    tempCount = SerialDebug_PrintFloat(fData, DIGIT_AFTER_DECIMAL);
                    tempCount = SerialDebug_PrintString("$", tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);

                break;

                //Read Stepper Motor Status and Stepper rpm
                case ('h') :
                case ('H') :
                    SerialDebug_SendByte('#');
                    SerialDebug_SendByte('H');
                    bData = (uint8_t)ShakerMotor_GetStatus();
                    tempCount = SerialDebug_PrintInteger(bData, 0);
                    tempCount = SerialDebug_PrintString(",", tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
                    wData = ShakerMotor_GetSpeed();
                    tempCount = SerialDebug_PrintFloat(wData, MAX_SHAKER_DIGIT);
                    tempCount = SerialDebug_PrintString("$", tempCount);
                    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);

                break;

                //Control Valve Motor
                case ('k') : 
                case ('K') :

                    //Find the DebugRx_DataCounter length of the string
                    for (i = 0; SerialDebug.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    DebugRx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < DebugRx_DataCounter) && (SerialDebug.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == DebugRx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = firstNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = secondNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = SerialDebug.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                    recCrc = atoi((char *)&SerialDebug.RxARRY[thirdNum + 1]);
                    if(recCrc == SerialDebug_CalCRC(SerialDebug.RxARRY, thirdNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        bData = SerialDebug.RxARRY[secondNum + 1] - '0';
                        ValveMotor_UpdatePostion(flagSet, bData);
                        SerialDebug_SendACK();
                    }
                    else
                    {
                        SerialDebug_SendNACK();
                    }

                break;
                //Control Piston Motor
                case ('m') : 
                case ('M') :
                    
                    //Find the DebugRx_DataCounter length of the string
                    for (i = 0; SerialDebug.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    DebugRx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < DebugRx_DataCounter) && (SerialDebug.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == DebugRx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = firstNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = secondNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = SerialDebug.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                    recCrc = atoi((char *)&SerialDebug.RxARRY[thirdNum + 1]);
                    if(recCrc == SerialDebug_CalCRC(SerialDebug.RxARRY, thirdNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        wData = atoi((char *)&SerialDebug.RxARRY[secondNum + 1]);
                        fData = (float) wData / 100;
                        PistonMotor_UpdatePostion(flagSet, fData);
                        SerialDebug_SendACK();
                    }
                    else
                    {
                        SerialDebug_SendNACK();
                    }
                    
                break;
                //Control Shaker Motor
                case ('o') : 
                case ('O') :
                    
                    //Find the DebugRx_DataCounter length of the string
                    for (i = 0; SerialDebug.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    DebugRx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < DebugRx_DataCounter) && (SerialDebug.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == DebugRx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = firstNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = secondNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = SerialDebug.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                    recCrc = atoi((char *)&SerialDebug.RxARRY[thirdNum + 1]);
                    if(recCrc == SerialDebug_CalCRC(SerialDebug.RxARRY, thirdNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        wData = atoi((char *)&SerialDebug.RxARRY[secondNum + 1]);
                        ShakerMotor_UpdateSpeed(flagSet, wData);
                        SerialDebug_SendACK();
                    }
                    else
                    {
                        SerialDebug_SendNACK();
                    }
                    

                break;
                //Control TEC Module
                case ('p') : 
                case ('P') :
                    
                    //Find the DebugRx_DataCounter length of the string
                    for (i = 0; SerialDebug.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    DebugRx_DataCounter = i;

                    //find first data number
                    for ( i = 0; ((i < DebugRx_DataCounter) && (SerialDebug.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == DebugRx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the second number
                    for ( i = (firstNum + 1); ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number
                    for ( i = secondNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != ',')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the fourth number i.e. CRC code
                    for ( i = thirdNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    fourthNum = i;
                    // If the third number field does not exist quit
                    if ( fourthNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = SerialDebug.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                    if(bData)
                    {
                        flagSet = true;
                    }
                    else
                    {
                        flagSet = false;
                    }
                    bData = SerialDebug.RxARRY[secondNum - 1] - '0';      // convert ascii to integer
                    if(bData)
                    {
                        flagControl = true;
                    }
                    else
                    {
                        flagControl = false;
                    }
                    recCrc = atoi((char *)&SerialDebug.RxARRY[fourthNum + 1]);
                    if(recCrc == SerialDebug_CalCRC(SerialDebug.RxARRY, fourthNum))
                    {
                        tempWord = atol((char *)&SerialDebug.RxARRY[thirdNum + 1]);
                        TECControl_UpdateTemp(flagSet, flagControl, tempWord);
                        SerialDebug_SendACK();
                    }
                    else
                    {
                        SerialDebug_SendNACK();
                    }
                    
                break;
                //Status of Error Buzzer and Buzzer default volume
                case ('q') : 
                case ('Q') :
                    
                    //Find the DebugRx_DataCounter length of the string
                    for (i = 0; SerialDebug.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    DebugRx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < DebugRx_DataCounter) && (SerialDebug.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == DebugRx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = firstNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = secondNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = SerialDebug.RxARRY[firstNum - 1] - '0';      // convert ascii to integer                    
                    recCrc = atoi((char *)&SerialDebug.RxARRY[thirdNum + 1]);
                    if(recCrc == SerialDebug_CalCRC(SerialDebug.RxARRY, thirdNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        wData = atoi((char *)&SerialDebug.RxARRY[secondNum + 1]);
                        Alarm_UpdateVolume(flagSet, wData);
                        SerialDebug_SendACK();
                    }
                    else
                    {
                        SerialDebug_SendNACK();
                    }
                    
                break;
                // Alarm Error Control
                case ('r') : 
                case ('R') :
                    
                    //Find the DebugRx_DataCounter length of the string
                    for (i = 0; SerialDebug.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    DebugRx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < DebugRx_DataCounter) && (SerialDebug.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    
                    // If there are no Partition characters quit
                    if ( firstNum == DebugRx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    
                    // Find the beginning of the second number i.e. CRC code
                    for ( i = firstNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = SerialDebug.RxARRY[firstNum - 1] - '0';
                    recCrc = atoi((char *)&SerialDebug.RxARRY[secondNum + 1]);
                    if(recCrc == SerialDebug_CalCRC(SerialDebug.RxARRY, secondNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        Alarm_UpdateError(flagSet);
                        SerialDebug_SendACK();
                    }
                    else
                    {
                        SerialDebug_SendNACK();
                    }
                    
                break;
                // Alarm Control
                case ('s') : 
                case ('S') :
                    
                    //Find the DebugRx_DataCounter length of the string
                    for (i = 0; SerialDebug.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    DebugRx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < DebugRx_DataCounter) && (SerialDebug.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    
                    // If there are no Partition characters quit
                    if ( firstNum == DebugRx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    
                    // Find the beginning of the second number i.e. CRC code
                    for ( i = firstNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = SerialDebug.RxARRY[firstNum - 1] - '0';
                    recCrc = atoi((char *)&SerialDebug.RxARRY[secondNum + 1]);
                    if(recCrc == SerialDebug_CalCRC(SerialDebug.RxARRY,(secondNum - 1)))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        Alarm_UpdateAlarm(flagSet);
                        SerialDebug_SendACK();
                    }
                    else
                    {
                        SerialDebug_SendNACK();
                    }
                    
                    
                    
                    
                break;
                //Set/Clear Error Codes
                case ('t') : 
                case ('T') :
                    
                    //Find the DebugRx_DataCounter length of the string
                    for (i = 0; SerialDebug.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    DebugRx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < DebugRx_DataCounter) && (SerialDebug.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == DebugRx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = firstNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = secondNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = SerialDebug.RxARRY[firstNum - 1] - '0';      // convert ascii to integer                   
                    
                    recCrc = atoi((char *)&SerialDebug.RxARRY[thirdNum + 1]);
                    if(recCrc == SerialDebug_CalCRC(SerialDebug.RxARRY, thirdNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        wData = atoi((char *)&SerialDebug.RxARRY[secondNum + 1]);
                        ErrorDebug_UpdateStatus(flagSet, wData);
                        SerialDebug_SendACK();
                    }
                    else
                    {
                        SerialDebug_SendNACK();
                    }

                break;
                //
                case ('y') : 
                case ('Y') :
                    
                    //Find the DebugRx_DataCounter length of the string
                    for (i = 0; SerialDebug.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    DebugRx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < DebugRx_DataCounter) && (SerialDebug.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == DebugRx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = firstNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = secondNum; ((i < DebugRx_DataCounter) && \
                            (SerialDebug.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == DebugRx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = SerialDebug.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                    recCrc = atoi((char *)&SerialDebug.RxARRY[thirdNum + 1]);
                    if(recCrc == SerialDebug_CalCRC(SerialDebug.RxARRY,thirdNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                            ShakerMotor_UpdateSpeed(0, 0);
                            PistonMotor_UpdatePostion(1, 0);
                            ValveMotor_UpdatePostion(1, VALVE_POSITION_OUTLET);
                        }

                        DebugFlag_ServiceRequest = false;
                        DebugFlag_TestRequest = flagSet;
                        tempWord = atol((char *)&SerialDebug.RxARRY[secondNum + 1]);
                        TECControl_UpdateTemp(0, 0, tempWord);
                        SerialDebug_SendACK();
                    }
                    else
                    {
                        SerialDebug_SendNACK();
                    }
                    
//                    SerialDebug_CalCRC();
                    
                break;
                //
                case ('z') : 
                case ('Z') :
                    
                    //Find the DebugRx_DataCountergth of the string
                    for (i = 0; SerialDebug.RxARRY[i] != '$'; i++) 
                    {

                    } //look for end of string marker
                    DebugRx_DataCounter = i;

                    //find first data number
                    for ( i = 0; ((i < DebugRx_DataCounter) && (SerialDebug.RxARRY[i] != '$')); i++) 
                    {
                        
                    }
                    firstNum = i;
//                    bData = atoi((char *)SerialDebug.RxARRY[firstNum - 2]);      // convert ascii to integer
//                    if(bData)
//                    {
//                        flagSet = true;
//                    }
//                    else
//                    {
//                        flagSet = false;
//                    }
//                    DebugFlag_TestRequest = false;
//                    DebugFlag_ServiceRequest = flagSet;
                    
                break;

                default:
                break;
                
            }
            SerialDebug.RxStatus = SERIALDEBUG_STATE_IDLE;
        break;

        default:
        break;
    }

    
}

/**
 * @brief This function transmits one byte data serially
 * @param data
 * @return Nothing
 */
void SerialDebug_SendByte(uint8_t bData)
{
//    if(UART2_IsTxReady())
//    {
        UART2_Write(bData);
//    }
}

/**
 * @brief This function transmits two bytes data into ascii format
 * @param Data
 * @return Nothing
 */

static int16_t SerialDebug_PrintString(const char * string, int16_t i)
{
  int16_t j = 0;

  while(string[j]){
    SerialDebug.TxARRY[i++] = string[j++];
  }
  SerialDebug.TxARRY[i]=0;

  return i;
}


/**
 * @brief This function transmits two bytes data into ascii format
 * @param Data
 * @return Nothing
 */

//static int8_t SerialDebug_PrintInteger(int16_t number, int8_t digits, int8_t forceNeg)
//{
//  int16_t i = 0;
//  int8_t value = 0;
//  int8_t started = 0;
//  int8_t j = 0;
//
//  if(number == 0) {
//    SerialDebug.TxARRY[j++] = '0';
//  }
//  else {
//    // If number is negative number or force negative is non zero
//    if ( (number < 0) || forceNeg) {
//      SerialDebug.TxARRY[j++] = '-';
//    }
//
//    if (number < 0) {
//      number = -number;
//    }
//
//    started = 0; //To detect the starting non zero character
//    for ( i=10000; (i>0 && j < digits); i /= 10) {
//      value = 0;
//
//      if ( number >= i) {
//        started = 1;
//      	value = number / i;
//        number = number - (value * i);
//      }
//      value = value + '0';              //converted to ascii
//      if (started) {
//        SerialDebug.TxARRY[j++] = value;
//      }
//    }
//  }
//
//  SerialDebug.TxARRY[j] = 0;
//
//  return j;
//}

static uint8_t SerialDebug_PrintInteger(uint32_t number, uint8_t digits)
{
    uint8_t i = 0;
    uint8_t len = 0;
    uint8_t j = 0;
    uint8_t str[10];

    if(number == 0) 
    {
        str[j++] = '0';
    }

    while (number) 
    { 
        str[j++] = (number % 10) + '0'; 
        number = number / 10; 
    }
    while(j < digits)
    {
        str[j++] = '0';
    }
    len = j;
    j = len - 1;
    
    for ( i = 0; i < len; i++) 
    {
        SerialDebug.TxARRY[i] = str[j--];
    }

//  SerialDebug.TxARRY[j] = 0;

  return len;
}


/**
 * @brief This function transmits float data into ascii format
 * @param Data
 * @return Nothing
 */

static uint8_t SerialDebug_PrintFloat(float number, uint8_t afterPoint)
{
    uint8_t i = 0;
    uint8_t digitPrinted;
    uint8_t left;
    uint32_t whole;	

    whole = (uint32_t) number;
    number = number - (float) whole;
    digitPrinted = SerialDebug_PrintInteger(whole, 1);

    if ( afterPoint != 0) 
    {
//        SerialDebug.TxARRY[digitPrinted++] = '.';
    }

    for(i = 0;i < afterPoint;i++)
    {
        number = number * 10;
        left = (uint8_t) number % 10;
        SerialDebug.TxARRY[digitPrinted++] = left + '0';
    }
    return digitPrinted;
}

uint8_t SerialDebug_CalCRC(uint8_t *ptr, uint8_t count)
{
    uint8_t  crc = 0;
    uint8_t crcPoly = 0x07;
    uint8_t i,j;

    for(j = 0; j < count; j++)
    {
        crc = crc ^ (uint8_t) *ptr++ ;
        for(i = 0; i < 8; i++)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ crcPoly;
            else
                crc = crc << 1;
        }
    }
    return (crc);
}

uint8_t SerialDebug_CRCArrayFill(const char * string, uint8_t i, uint8_t k)
{
    uint8_t j = 0;
    uint8_t m = 0;

    for(m = 0; m < k; m++)
    {
        DebugCRC_Array[i++] = string[j++];
    } 

  return i;
}

void SerialDebug_SendACK(void)  
{
    DebugTx_AckVal = 0x06;
    DebugFlag_AckStatus = true;
}

void SerialDebug_SendNACK(void)
{
    DebugTx_AckVal = 0x15;
    DebugFlag_AckStatus = true;
}

void SerialDebug_PrintDebugString(const char * string, uint8_t len )
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t k = 0;

  for(k = 0; k <= len; k++)
  {
    SerialDebug.TxARRY[i++] = string[j++];
  }
  SerialDebug.TxARRY[i]=0;
  i = SerialDebug_PrintString("\n\r",i);
  UART2_WriteBuffer(SerialDebug.TxARRY, i);
//  DebugFlag_TestRequest = true;
//  DebugFlag_AckStatus = true;
}

void SerialDebug_PrintACK(uint8_t tempAck)
{
    uint16_t tempWord = 0;
    uint16_t tempCount = 0;
    SerialDebug_SendByte('#');
    SerialDebug_SendByte('Z');
    tempWord = (uint16_t)tempAck;
    tempCount = SerialDebug_PrintInteger(tempWord, 2);
    tempCount = SerialDebug_PrintString("\n\r", tempCount);
    UART2_WriteBuffer(SerialDebug.TxARRY, tempCount);
}