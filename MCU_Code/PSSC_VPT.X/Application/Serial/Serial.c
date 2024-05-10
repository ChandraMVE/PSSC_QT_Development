

/**
 SERIAL.C File

  @Company
    Microchip Technology Inc.

  @File Name
 serial.c

  @Summary
    This is the file used to control the Green and Red LED

  @Description
    This source file provides Serial communication with UART configurator,
 * 
 *
 */

#include "Serial.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/pin_manager.h"
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

static SerialLoad_ETYP LoadState;

static uint8_t Rx_Data;
static uint8_t Rx_DataCounter;
static uint8_t Rx_Counter;
static uint16_t Tx_Counter;
static uint8_t Tx_AckVal;
static uint32_t SerialTemp;

static uint8_t SerialCRC_Array[64];

bool Flag_ServiceRequest;
bool Flag_TestRequest;
bool Flsg_VersionRequest;
bool Flag_AckStatus;
bool Serial_LoadStatus;
bool Serial_FlagValve;
bool Serial_FlagPiston;
bool SerialFlag_InitTemp;

void Serial_SendByte(uint8_t bData);
static int16_t Serial_PrintString(const char * string, int16_t i);
static uint8_t Serial_PrintInteger(uint32_t number, uint8_t digits);
static uint8_t Serial_PrintFloat(float number, uint8_t afterPoint);
uint8_t Serial_CRCArrayFill(const char * string, uint8_t i, uint8_t k);
void Serial_SendACK(void);
void Serial_SendNACK(void);
void Serial_LoadManager(void);

extern void SerialDebug_PrintDebugString(const char * string, uint8_t len );
//extern void SerialDebug_PrintACK(uint8_t tempAck);

/**
 * @brief This function initializes Serial Variables
 * @param Nothing
 * @return Nothing
 */
void Serial_Initialise(void)
{
    LoadState = SERIAL_SHAKER_CONTROL;
    Rx_DataCounter = 0;
    Rx_Counter = 0;
    Tx_Counter = 0;
    Rx_Data = 0;
    Tx_AckVal = 0;
    SerialTemp = 0;
    Flag_ServiceRequest = false;
    Flag_TestRequest = false;
    Flsg_VersionRequest = false;
    Flag_AckStatus = false;
    Serial_LoadStatus = false;
    Serial_FlagValve = false;
    Serial_FlagPiston = false;
    SerialFlag_InitTemp = false;
}

/**
 * @brief This function is called from schedular with interval time
 *          This function checks the command received from the som and perform the actions 
 * @param Nothing
 * @return Nothing
 */
void Serial_Handler(void)
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

    switch ( Serial.RxStatus) 
    {
        case SERIAL_STATE_IDLE:
            tempCount = UART1_ReadBuffer(Serial.RxARRY, 0xFF);
            if (tempCount != 0) 
            {
                if ( Serial.RxARRY[0] == '#') 
                {
                    Serial.RxStatus = SERIAL_STATE_WAITING;
                    Serial.RxIndex = tempCount;
                    Rx_Counter = Serial.RxIndex;
                }
            }
            Tx_Counter++;
            //Transmits the serial data frame every second
            if(Tx_Counter > MAX_WAITTIME)
            {
                Tx_Counter = 0;
                if ((Flag_ServiceRequest == true) || (Flag_TestRequest == true))
                {
                    //Continuous transmission of the following parameters.
                    Serial_SendByte('#');
                    SerialCRC_Array[totalCount++] = '#';
                    if(Flag_TestRequest == true)
                    {
                    //    Ambient Temperature
                        Serial_SendByte('Y');
                        Serial_SendByte('C');
                        SerialCRC_Array[totalCount++] = 'Y';
                        SerialCRC_Array[totalCount++] = 'C';
                        wData = ADCRead_GetAmbTemp();
                        tempCount = Serial_PrintInteger(wData, MAX_AMB_DIGIT);
                        tempCount = Serial_PrintString(",", tempCount);
                        totalCount = Serial_CRCArrayFill(Serial.TxARRY, totalCount, tempCount);
                        UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    }
                    else
                    {
                        Serial_SendByte('Y');
                        SerialCRC_Array[totalCount++] = 'Y';
                    }
                    // Chamber Temperature
                    Serial_SendByte('A');
                    SerialCRC_Array[totalCount++] = 'A';
                    tempWord = TemperatureControl_GetTempADC();
                    tempCount = Serial_PrintInteger(tempWord, MAX_ADC_DIGIT);
                    tempCount = Serial_PrintString(",", tempCount);
                    totalCount = Serial_CRCArrayFill(Serial.TxARRY, totalCount, tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    
                    // Chamber Pressure
                    Serial_SendByte('B');
                    SerialCRC_Array[totalCount++] = 'B';
                    tempWord = TemperatureControl_GetPressADC();
                    tempCount = Serial_PrintInteger(tempWord, MAX_ADC_DIGIT);
                    tempCount = Serial_PrintString(",", tempCount);
                    totalCount = Serial_CRCArrayFill(Serial.TxARRY, totalCount, tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    
                    // Piston Position
                    Serial_SendByte('F');
                    SerialCRC_Array[totalCount++] = 'F';
                    fData = PistonMotor_GetPostion();
                    tempCount = Serial_PrintFloat(fData, DIGIT_AFTER_DECIMAL);
                    tempCount = Serial_PrintString(",", tempCount);
                    totalCount = Serial_CRCArrayFill(Serial.TxARRY, totalCount, tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    
                    // Valve Position
                    Serial_SendByte('D');
                    SerialCRC_Array[totalCount++] = 'D';
                    bData = ValveMotor_GetPostion();
                    tempCount = Serial_PrintInteger(bData, 0);
                    tempCount = Serial_PrintString(",", tempCount);
                    totalCount = Serial_CRCArrayFill(Serial.TxARRY, totalCount, tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    
                    // Shaker Speed
                    Serial_SendByte('H');
                    SerialCRC_Array[totalCount++] = 'H';
                    wData = ShakerMotor_GetSpeed();
                    tempCount = Serial_PrintInteger(wData, MAX_SHAKER_DIGIT);
                    tempCount = Serial_PrintString(",", tempCount);
                    totalCount = Serial_CRCArrayFill(Serial.TxARRY, totalCount, tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    
                    // Error Codes
                    Serial_SendByte('E');
                    SerialCRC_Array[totalCount++] = 'E';
                    wData = Error_GetFaultCount();
                    tempCount = Serial_PrintInteger(wData, 4);
                    tempCount = Serial_PrintString(",", tempCount);
                    totalCount = Serial_CRCArrayFill(Serial.TxARRY, totalCount, tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    
                    // Ack Status if any command is received
//                    if(true == Flag_AckStatus)
//                    {
//                        Flag_AckStatus = false;
//                        Serial_SendByte('Z');
//                        SerialCRC_Array[totalCount++] = 'Z';
//                        tempWord = (uint32_t)Tx_AckVal;
//                        tempCount = Serial_PrintInteger(tempWord, 2);
//                        tempCount = Serial_PrintString(",", tempCount);
//                        totalCount = Serial_CRCArrayFill(Serial.TxARRY, totalCount, tempCount);
//                        UART1_WriteBuffer(Serial.TxARRY, tempCount);
//                    }
                    
                    // CRC Calculate
                    Serial_SendByte('W');
                    tempWord = Serial_CalCRC(SerialCRC_Array, totalCount);
                    tempCount = Serial_PrintInteger(tempWord, 3);
                    tempCount = Serial_PrintString("$", tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);

                }
                else if(Flsg_VersionRequest == true)
                {
                    Flag_TestRequest = true;
                    Serial_SendByte('#');
                    Serial_SendByte('V');
                    SerialCRC_Array[totalCount++] = '#';
                    SerialCRC_Array[totalCount++] = 'V';
                    tempCount = Serial_PrintInteger(MAJOR_SW_VERSION, 2);
                    totalCount = Serial_CRCArrayFill(Serial.TxARRY, totalCount, tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    tempCount = Serial_PrintInteger(MINOR_SW_VERSION, 2);
                    totalCount = Serial_CRCArrayFill(Serial.TxARRY, totalCount, tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    tempCount = Serial_PrintInteger(TEST_SW_VERSION, 2);
                    tempCount = Serial_PrintString(",", tempCount);
                    totalCount = Serial_CRCArrayFill(Serial.TxARRY, totalCount, tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    tempWord = Serial_CalCRC(SerialCRC_Array, totalCount);
                    tempCount = Serial_PrintInteger(tempWord, 3);
                    tempCount = Serial_PrintString("$", tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                }
            }
            
        break;
        // if data frame is not fully received we will wait here till end of frame is received
        case SERIAL_STATE_WAITING:
            // Check any remaining data received
            for(tempCount = 0; tempCount <= Serial.RxIndex; tempCount++) 
            {
                // If End of Frame received
                if ( Serial.RxARRY[tempCount] == '$') 
                {
                    if(tempCount > 31)
                    {
                        tempCount = 31;
                    }
                    SerialDebug_PrintDebugString(Serial.RxARRY,tempCount);
                    Serial.RxStatus = SERIAL_STATE_COMMAND;
                    break;
                }
            }
            tempCount = UART1_ReadBuffer(&Serial.RxARRY[Serial.RxIndex], 0xFF);
            if ( tempCount != 0) 
            {
                Serial.RxIndex += tempCount;
                Rx_Counter = Rx_Counter + tempCount;
                
                for(tempCount = 0; tempCount < Serial.RxIndex; tempCount++) 
                {
                    // If End of Frame received
                    if ( Serial.RxARRY[tempCount] == '$') 
                    {
                        if(tempCount > 31)
                        {
                            tempCount = 31;
                        }
                        SerialDebug_PrintDebugString(Serial.RxARRY,tempCount);
                        Serial.RxStatus = SERIAL_STATE_COMMAND;
                        break;
                    }
                }
            }
            else
            {
                Rx_Counter++;
                if(Rx_Counter > MAX_WAITTIME)
                {
                    Rx_Counter = 0;
                    Serial.RxStatus = SERIAL_STATE_IDLE;
                }
            }
        break;
        // if data is received fully search which command is received
        case SERIAL_STATE_COMMAND:
            // Process the command received
            switch (Serial.RxARRY[1]) 
            {
                //Read Chamber Temperature
                case ('a') :
                case ('A') :
                    Serial_SendByte('#');
                    Serial_SendByte('A');
                    tempWord = TemperatureControl_GetTempADC();
                    tempCount = Serial_PrintInteger(tempWord, MAX_ADC_DIGIT);
                    tempCount = Serial_PrintString("$", tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);

                break;
                //Read Chamber Pressure
                case ('b') :
                case ('B') :
                    Serial_SendByte('#');
                    Serial_SendByte('B');
                    tempWord = TemperatureControl_GetPressADC();
                    tempCount = Serial_PrintInteger(tempWord, MAX_ADC_DIGIT);
                    tempCount = Serial_PrintString("$", tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);

                break;
                //Read Ambient Temperature
                case ('c') :
                case ('C') :
                    Serial_SendByte('#');
                    Serial_SendByte('C');
                    wData = ADCRead_GetAmbTemp();
                    tempCount = Serial_PrintInteger(wData, MAX_AMB_DIGIT);
                    tempCount = Serial_PrintString("$", tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);

                break;
                //Read Valve Position
                case ('d') :
                case ('D') :
                    Serial_SendByte('#');
                    Serial_SendByte('D');
                    bData = (uint8_t)ValveMotor_GetStatus();
                    tempCount = Serial_PrintInteger(bData, 0);
                    tempCount = Serial_PrintString(",", tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    bData = ValveMotor_GetPostion();
                    tempCount = Serial_PrintInteger(bData, 0);
                    tempCount = Serial_PrintString("$", tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);

                break;
                //Read Piston Motor Status and Piston Position
                case ('f') :
                case ('F') :
                    Serial_SendByte('#');
                    Serial_SendByte('F');
                    bData = (uint8_t)PistonMotor_GetStatus();
                    tempCount = Serial_PrintInteger(bData, 0);
                    tempCount = Serial_PrintString(",", tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    fData = PistonMotor_GetPostion();
                    tempCount = Serial_PrintFloat(fData, DIGIT_AFTER_DECIMAL);
                    tempCount = Serial_PrintString("$", tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);

                break;
                
                //Read Cycle Running Status 
                case ('g') :
                case ('G') :
                     //Find the Rx_DataCounter length of the string
                    for (i = 0; Serial.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    Rx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < Rx_DataCounter) && (Serial.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    
                    // If there are no Partition characters quit
                    if ( firstNum == Rx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    
                    // Find the beginning of the second number i.e. CRC code
                    for ( i = firstNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = Serial.RxARRY[firstNum - 1] - '0';              // convert ascii to integer
                    recCrc = atoi((char *)&Serial.RxARRY[secondNum + 1]);
                    if(recCrc == Serial_CalCRC(Serial.RxARRY, secondNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        Error_SetCycleRunSts(flagSet);
                        Serial_SendACK();
                    }
                    else
                    {
                        Serial_SendNACK();
                    }
                    
                break;

                //Read Stepper Motor Status and Stepper rpm
                case ('h') :
                case ('H') :
                    Serial_SendByte('#');
                    Serial_SendByte('H');
                    bData = (uint8_t)ShakerMotor_GetStatus();
                    tempCount = Serial_PrintInteger(bData, 0);
                    tempCount = Serial_PrintString(",", tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);
                    wData = ShakerMotor_GetSpeed();
                    tempCount = Serial_PrintFloat(wData, MAX_SHAKER_DIGIT);
                    tempCount = Serial_PrintString("$", tempCount);
                    UART1_WriteBuffer(Serial.TxARRY, tempCount);

                break;

                //Control Valve Motor
                case ('k') : 
                case ('K') :

                    //Find the Rx_DataCounter length of the string
                    for (i = 0; Serial.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    Rx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < Rx_DataCounter) && (Serial.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == Rx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = firstNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = secondNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = Serial.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                    recCrc = atoi((char *)&Serial.RxARRY[thirdNum + 1]);
                    if(recCrc == Serial_CalCRC(Serial.RxARRY, thirdNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        bData = Serial.RxARRY[secondNum + 1] - '0';
                        ValveMotor_UpdatePostion(flagSet, bData);
                        Serial_SendACK();
                    }
                    else
                    {
                        Serial_SendNACK();
                    }
                    
                break;
                //Control Piston Motor
                case ('m') : 
                case ('M') :
                    
                    //Find the Rx_DataCounter length of the string
                    for (i = 0; Serial.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    Rx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < Rx_DataCounter) && (Serial.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == Rx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = firstNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = secondNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = Serial.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                    recCrc = atoi((char *)&Serial.RxARRY[thirdNum + 1]);
                    if(recCrc == Serial_CalCRC(Serial.RxARRY, thirdNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        wData = atoi((char *)&Serial.RxARRY[secondNum + 1]);
                        fData = (float) wData / 100;
                        PistonMotor_UpdatePostion(flagSet, fData);
                        Serial_SendACK();
                    }
                    else
                    {
                        Serial_SendNACK();
                    }
                    
                break;
                //Control Shaker Motor
                case ('o') : 
                case ('O') :
                    
                    //Find the Rx_DataCounter length of the string
                    for (i = 0; Serial.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    Rx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < Rx_DataCounter) && (Serial.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == Rx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = firstNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = secondNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = Serial.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                    recCrc = atoi((char *)&Serial.RxARRY[thirdNum + 1]);
                    if(recCrc == Serial_CalCRC(Serial.RxARRY, thirdNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        wData = atoi((char *)&Serial.RxARRY[secondNum + 1]);
                        ShakerMotor_UpdateSpeed(flagSet, wData);
                        Serial_SendACK();
                    }
                    else
                    {
                        Serial_SendNACK();
                    }

                break;
                //Control TEC Module
                case ('p') : 
                case ('P') :
                    
                    //Find the Rx_DataCounter length of the string
                    for (i = 0; Serial.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    Rx_DataCounter = i;

                    //find first data number
                    for ( i = 0; ((i < Rx_DataCounter) && (Serial.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == Rx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the second number
                    for ( i = (firstNum + 1); ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number
                    for ( i = secondNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != ',')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the second number field does not exist quit
                    if ( thirdNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the fourth number i.e. CRC code
                    for ( i = thirdNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    fourthNum = i;
                    // If the third number field does not exist quit
                    if ( fourthNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = Serial.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                    if(bData)
                    {
                        flagSet = true;
                    }
                    else
                    {
                        flagSet = false;
                    }
                    bData = Serial.RxARRY[secondNum - 1] - '0';      // convert ascii to integer
                    if(bData)
                    {
                        flagControl = true;
                    }
                    else
                    {
                        flagControl = false;
                    }
                    recCrc = atoi((char *)&Serial.RxARRY[fourthNum + 1]);
                    if(recCrc == Serial_CalCRC(Serial.RxARRY, fourthNum))
                    {
                        tempWord = atol((char *)&Serial.RxARRY[thirdNum + 1]);
                        TECControl_UpdateTemp(flagSet, flagControl, tempWord);
                        Serial_SendACK();
                    }
                    else
                    {
                        Serial_SendNACK();
                    }
                break;
                //Status of Error Buzzer and Buzzer default volume
                case ('q') : 
                case ('Q') :
                    
                    //Find the Rx_DataCounter length of the string
                    for (i = 0; Serial.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    Rx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < Rx_DataCounter) && (Serial.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == Rx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = firstNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = secondNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = Serial.RxARRY[firstNum - 1] - '0';      // convert ascii to integer                    
                    recCrc = atoi((char *)&Serial.RxARRY[thirdNum + 1]);
                    if(recCrc == Serial_CalCRC(Serial.RxARRY, thirdNum))
                    {
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        wData = atoi((char *)&Serial.RxARRY[secondNum + 1]);
                        Alarm_UpdateVolume(flagSet, wData);
                        Serial_SendACK();
                    }
                    else
                    {
                        Serial_SendNACK();
                    }

                break;
                // Alarm Error Control
                case ('r') : 
                case ('R') :
                    
                    //Find the Rx_DataCounter length of the string
                    for (i = 0; Serial.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    Rx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < Rx_DataCounter) && (Serial.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    
                    // If there are no Partition characters quit
                    if ( firstNum == Rx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    
                    // Find the beginning of the second number i.e. CRC code
                    for ( i = firstNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = Serial.RxARRY[firstNum - 1] - '0';
                    recCrc = atoi((char *)&Serial.RxARRY[secondNum + 1]);
                    if(recCrc == Serial_CalCRC(Serial.RxARRY, secondNum))
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
                        Serial_SendACK();
                    }
                    else
                    {
                        Serial_SendNACK();
                    }
                    
                break;
                // Alarm Control
                case ('s') : 
                case ('S') :
                    
                    //Find the Rx_DataCounter length of the string
                    for (i = 0; Serial.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    Rx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < Rx_DataCounter) && (Serial.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    
                    // If there are no Partition characters quit
                    if ( firstNum == Rx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    
                    // Find the beginning of the second number i.e. CRC code
                    for ( i = firstNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = Serial.RxARRY[firstNum - 1] - '0';
                    recCrc = atoi((char *)&Serial.RxARRY[secondNum + 1]);
                    if(recCrc == Serial_CalCRC(Serial.RxARRY,(secondNum)))
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
                        Serial_SendACK();
                    }
                    else
                    {
                        Serial_SendNACK();
                    }
                    
                break;
                //Set/Clear Error Codes
                case ('t') : 
                case ('T') :
                    
                    //Find the Rx_DataCounter length of the string
                    for (i = 0; Serial.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    Rx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < Rx_DataCounter) && (Serial.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == Rx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = firstNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = secondNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the third number field does not exist quit
                    if ( thirdNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    
                    bData = Serial.RxARRY[firstNum - 1] - '0';      // convert ascii to integer                   
                    recCrc = atoi((char *)&Serial.RxARRY[thirdNum + 1]);
                    if(recCrc == Serial_CalCRC(Serial.RxARRY, thirdNum))
                    {
                        wData = atoi((char *)&Serial.RxARRY[secondNum + 1]);
                        if(bData)
                        {
                            if(wData == 0U)
                            {
                                flagSet = false;
                                Serial_FlagPiston = true;
                                Serial_FlagValve = true;
                                Serial_LoadStatus = true;
                                LoadState = SERIAL_SHAKER_CONTROL;
                            }
                            else
                            {
                                flagSet = true;
                            }
                        }
                        else
                        {
                            flagSet = false;
                        }
//                        wData = atoi((char *)&Serial.RxARRY[secondNum + 1]);
                        Error_SetCycleRunSts(flagSet);
                        Error_UpdateStatus(flagSet, wData);
                        Serial_SendACK();
                    }
                    else
                    {
                        Serial_SendNACK();
                    }

                break;
                //
                case ('y') : 
                case ('Y') :
                    
                    //Find the Rx_DataCounter length of the string
                    for (i = 0; Serial.RxARRY[i] != '$'; i++) 
                    {
                        
                    } //look for end of string marker
                    Rx_DataCounter = i;

                    //find first data numberr
                    for ( i = 0; ((i < Rx_DataCounter) && (Serial.RxARRY[i] != ',')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    // If there are no Partition characters quit
                    if ( firstNum == Rx_DataCounter) 
                    {
                        //If only one value is received write here operation of that single value
                        break;
                    }
                    // Find the beginning of the second number
                    for ( i = (firstNum + 1); ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != ',')); i++) 
                    {

                    }
                    secondNum = i;
                    // If the second number field does not exist quit
                    if ( secondNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    
                    // Find the beginning of the third number
                    for ( i = secondNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != ',')); i++) 
                    {

                    }
                    thirdNum = i;
                    // If the second number field does not exist quit
                    if ( thirdNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    // Find the beginning of the third number i.e. CRC code
                    for ( i = thirdNum; ((i < Rx_DataCounter) && \
                            (Serial.RxARRY[i] != 'W')); i++) 
                    {

                    }
                    fourthNum = i;
                    // If the third number field does not exist quit
                    if ( fourthNum == Rx_DataCounter) 
                    {
                        break;
                    }
                    
//                    bData = Serial.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                    recCrc = atoi((char *)&Serial.RxARRY[fourthNum + 1]);
                    if(recCrc == Serial_CalCRC(Serial.RxARRY,fourthNum))
                    {  
                        bData = Serial.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                        if(bData)
                        {
//                            flagSet = true;
//                            ShakerMotor_UpdateSpeed(0, 0);
//                            PistonMotor_UpdatePostion(0, 0);
//                            ValveMotor_UpdatePostion(0, VALVE_POSITION_OUTLET);
                            Serial_FlagPiston = true;
                            Serial_FlagValve = true;
                        }
                        else
                        {
//                            ShakerMotor_UpdateSpeed(0, 0);
//                            PistonMotor_UpdatePostion(1, 0);
//                            ValveMotor_UpdatePostion(1, VALVE_POSITION_OUTLET);
                            Serial_FlagPiston = true;
                            Serial_FlagValve = true;
                        }
                        
                        bData = Serial.RxARRY[secondNum - 1] - '0';      // convert ascii to integer
                        if(bData)
                        {
                            flagSet = true;
                        }
                        else
                        {
                            flagSet = false;
                        }
                        Error_SetCycleRunSts(flagSet);
                        
                        if(Flsg_VersionRequest == false)
                        {
                            Flsg_VersionRequest = true;
                        }
//                        Flag_ServiceRequest = false;
//                        Flag_TestRequest = true;
                        tempWord = atol((char *)&Serial.RxARRY[thirdNum + 1]);
#if (TEC_PID_DIFF == ENABLE)
                    if(flagSet == true)
                    {
                        TECControl_SetTempDiff(tempWord);
                    }
#endif
                        SerialTemp = tempWord;
                        if(false == SerialFlag_InitTemp)
                        {
                            SerialFlag_InitTemp = true;
                            TECControl_SetDefaultVal(SerialTemp);
                        }
//                        TECControl_UpdateTemp(0, 0, tempWord);
                        Serial_LoadStatus = true;
                        LoadState = SERIAL_SHAKER_CONTROL;
                        Serial_SendACK();
                    }
                    else
                    {
                        Serial_SendNACK();
                    }
                    
                break;
                //
                case ('z') : 
                case ('Z') :
                    
                    //Find the Rx_DataCountergth of the string
                    for (i = 0; Serial.RxARRY[i] != '$'; i++) 
                    {

                    } //look for end of string marker
                    Rx_DataCounter = i;

                    //find first data number
                    for ( i = 0; ((i < Rx_DataCounter) && (Serial.RxARRY[i] != '$')); i++) 
                    {
                        
                    }
                    firstNum = i;
                    bData = Serial.RxARRY[firstNum - 1] - '0';      // convert ascii to integer
                    if(bData)
                    {
                        flagSet = true;
                    }
                    else
                    {
                        flagSet = false;
                    }
//                    Flag_TestRequest = false;
//                    Flag_ServiceRequest = flagSet;
                    
                break;

                default:
                break;
                
            }
            Serial.RxStatus = SERIAL_STATE_IDLE;
        break;

        default:
        break;
    }

    if(true == Serial_LoadStatus)
    {
        Serial_LoadManager();
    }
    
}

/**
 * @brief This function transmits one byte data serially
 * @param data
 * @return Nothing
 */
void Serial_SendByte(uint8_t bData)
{
//    if(UART1_IsTxReady())
//    {
        UART1_Write(bData);
//    }
}

/**
 * @brief This function transmits two bytes data into ascii format
 * @param Data
 * @return number of bytes to be transmitted
 */

static int16_t Serial_PrintString(const char * string, int16_t i)
{
  int16_t j = 0;

  while(string[j]){
    Serial.TxARRY[i++] = string[j++];
  }
  Serial.TxARRY[i]=0;

  return i;
}


/**
 * @brief This function transmits two bytes data into ascii format
 * @param Data
 * @return number of bytes to be transmitted
 */

static uint8_t Serial_PrintInteger(uint32_t number, uint8_t digits)
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
        Serial.TxARRY[i] = str[j--];
    }

//  Serial.TxARRY[j] = 0;

  return len;
}


/**
 * @brief This function transmits float data into ascii format
 * @param Data
 * @return number of bytes to be transmitted
 */

static uint8_t Serial_PrintFloat(float number, uint8_t afterPoint)
{
    uint8_t i = 0;
    uint8_t digitPrinted;
    uint8_t left;
    uint32_t whole;	

    whole = (uint32_t) number;
    number = number - (float) whole;
    digitPrinted = Serial_PrintInteger(whole, 1);

    if ( afterPoint != 0) 
    {
//        Serial.TxARRY[digitPrinted++] = '.';
    }

    for(i = 0;i < afterPoint;i++)
    {
        number = number * 10;
        left = (uint8_t) number % 10;
        Serial.TxARRY[digitPrinted++] = left + '0';
    }
    return digitPrinted;
}

uint8_t Serial_CalCRC(uint8_t *ptr, uint8_t count)
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


uint8_t Serial_CRCArrayFill(const char * string, uint8_t i, uint8_t k)
{
    uint8_t j = 0;
    uint8_t m = 0;

    for(m = 0; m < k; m++)
    {
      SerialCRC_Array[i++] = string[j++];
    }

  return i;
}

void Serial_SendACK(void)
{
    uint16_t tempWord = 0;
    uint16_t tempCount = 0;
    Serial_SendByte('#');
    Serial_SendByte('Z');
    tempWord = (uint16_t)0x06;
//    SerialDebug_PrintACK(0x06);
    tempCount = Serial_PrintInteger(tempWord, 2);
    tempCount = Serial_PrintString("$", tempCount);
    UART1_WriteBuffer(Serial.TxARRY, tempCount);
}

void Serial_SendNACK(void)
{
    uint16_t tempWord = 0;
    uint16_t tempCount = 0;
    Serial_SendByte('#');
    Serial_SendByte('Z');
    tempWord = (uint16_t)0x15;
//    SerialDebug_PrintACK(0x15);
    tempCount = Serial_PrintInteger(tempWord, 2);
    tempCount = Serial_PrintString("$", tempCount);
    UART1_WriteBuffer(Serial.TxARRY, tempCount);
}

void Serial_LoadManager(void)
{
    uint32_t tempVal;
    
    switch(LoadState)
    {
        case SERIAL_SHAKER_CONTROL :
            ShakerMotor_UpdateSpeed(false, 0); 
            LoadState = SERIAL_SHAKER_WAITING;
        break;
            
        case SERIAL_SHAKER_WAITING :
            
            if(0 == ShakerMotor_GetSpeed())
            {
                LoadState = SERIAL_TEMP_CONTROL;
            }
        break;
        
        case SERIAL_TEMP_CONTROL :
            TECControl_UpdateTemp(0, 0, SerialTemp);
            LoadState = SERIAL_TEMP_WAITING;
            
        break;
        
        case SERIAL_TEMP_WAITING :
            tempVal = TemperatureControl_GetTempADC();
            if(SerialTemp != 0)
            {
                if((tempVal <= (SerialTemp + SERIAL_TEMP_TOL))  &&      \
                        (tempVal >= (SerialTemp - SERIAL_TEMP_TOL)))
                {
                    LoadState = SERIAL_VALVE_CONTROL;
                }
            }
            else
            {
                LoadState = SERIAL_VALVE_CONTROL;
            }
        break;  
        
        case SERIAL_VALVE_CONTROL :
            ValveMotor_UpdatePostion(Serial_FlagValve, VALVE_POSITION_OUTLET);
            LoadState = SERIAL_VALVE_WAITING;
            
        break;
        
        case SERIAL_VALVE_WAITING :
            
            if(VALVE_POSITION_OUTLET == ValveMotor_GetPostion())
            {
                LoadState = SERIAL_PISTON_CONTROL;
            }
        break;
        
        case SERIAL_PISTON_CONTROL :
            PistonMotor_UpdatePostion(Serial_FlagPiston, 0.0f); 
            LoadState = SERIAL_PISTON_WAITING;
        break;
            
        case SERIAL_PISTON_WAITING :
            
            if(0.0f == PistonMotor_GetPostion())
            {
                LoadState = SERIAL_SHAKER_CONTROL;
                Serial_LoadStatus = false;

            }
        break;
        
        default : 
            Serial_LoadStatus = false;
            LoadState = SERIAL_SHAKER_CONTROL;
        break;
    }
}


