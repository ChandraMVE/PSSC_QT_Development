/**
 ******************************************************************************
 * @file       Temperature Control.c
 * @author     Dnyaneshwar 
 * @date       13 Jan 2021
 * @brief      This is a source file reads the ADC value of thermistor sensor  
 *              and PSSC VPT 
 ******************************************************************************
 * Redistribution in source and binary forms, with or without modification,
 * are not permitted. Use in source code needs the written approval of the author.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************
 */

/*
================================================================================
File name:    TemperatureControl.c
                    
Originator:   Dnyaneshwar Pawar

Platform:     dsPIC33CK128MP206
Compiler:     XC16 V1.60
IDE     :     MPLAB X IDE V5.20

Description: 
  


Class Methods:
  
    

Resources:
  None

================================================================================
 History:	
-*-----*-----------*------------------------------------*-----------------------
       13-01-2021  Initial Write                        Dnyaneshwar Pawar
--------------------------------------------------------------------------------
*/

#include "xc.h"
#include <stdbool.h>
#include "TemperatureControl.h"
#include "../mcc_generated_files/spi1.h"
#include "mcc_generated_files/pin_manager.h"

/**
 * @brief This method Initializes the Parameter variables to read the External ADC using SPI communication 
 * @param Nothing
 * @return Nothing
 */
void TemperatureControl_Initialise(void)
{
    SS1OUT_SetDigitalOutput();                                      // Slave Select Pin defined as output
    SS1OUT_SetHigh();
    
    TemperatureControl.Command_ARRY[PROG_RST] = 0x8500;            // Reset program registers (RST) (1000 0101 00000000)
    TemperatureControl.Command_ARRY[FEATURE_SEL] = 0x0710;            // feature select register (0000 011 1 0001 0000)
    TemperatureControl.Command_ARRY[INPUT_RANGE0] = 0x0B05;			// WRITE Channel 0 Input Range. I need range 0b0110(0000 1011 00000110) 05h address + \RD/WR = 1 + range 
    TemperatureControl.Command_ARRY[READ_RANGE0] = 0x0A00;			// READ range channel 0	(0000 101 0 00000000)
    TemperatureControl.Command_ARRY[MANUAL_CH0] = 0xC000; 			// Manual Channel n Select (MAN_Ch_0) (1100 0000 00000000)
    TemperatureControl.Command_ARRY[LAST_CONFIG] = 0x0000; 			// continue with last config (0000 0000 00000000)
    TemperatureControl.Command_ARRY[DUMMY_WRITE] = 0x5555;            // Dummy write command while reading the data
    TemperatureControl.Command_ARRY[INPUT_RANGE1] = 0x0D05;			// WRITE Channel 1 Input Range. I need range 0b0110(0000 1101 00000110) 05h address + \RD/WR = 1 + range 
    TemperatureControl.Command_ARRY[READ_RANGE1] = 0x0B00;			// READ range channel 1	(0000 110 0 00000000)
    TemperatureControl.Command_ARRY[MANUAL_CH1] = 0xC400; 			// Manual Channel n Select (MAN_Ch_1) (1100 0100 00000000)
    
}
   
/**
 * @brief This function is called from schedular with interval time
 *          This function reads the actual ADC count from external ADC 
 * @param Nothing
 * @return Nothing
 */
void TemperatureControl_Handler(void)
{
    uint16_t dummyRead = 0;
    uint16_t highData,lowData;
    uint16_t highData1,lowData1;
    
    switch(TemperatureControl.ADC_Status)
    {
        case TEMP_ADC_STATE_IDLE : 
            SS1OUT_SetLow();                                    // set CS Low to start transmission
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[PROG_RST]);          //Set programming register
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);       // Read 16 bits data
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);       // read remaining 16 bits data
            SS1OUT_SetHigh();                                   // set CS high to end transmission
            Nop();
            SS1OUT_SetLow();                                    // set CS Low to start transmission
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[FEATURE_SEL]);       // Select the features of the ADC
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            SS1OUT_SetHigh();                                   // set CS high to end transmission
            Nop();
            SS1OUT_SetLow();                                    // set CS Low to start transmission
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[INPUT_RANGE0]);      // turn ON the channel 1 of ADC
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            SS1OUT_SetHigh();                                   // set CS high to end transmission
            Nop();
            SS1OUT_SetLow();                                    // set CS Low to start transmission
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[INPUT_RANGE1]);      // turn ON the channel 2 of ADC
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            SS1OUT_SetHigh();                                   // set CS high to end transmission
            TemperatureControl.ADC_Status = TEMP_ADC_STATE_READ;
        break;
        
        case TEMP_ADC_STATE_READ : 
            
            SS1OUT_SetLow();                                    // set CS Low to start transmission
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[MANUAL_CH0]);        // start conversion for the channel 1 of ADC
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            SS1OUT_SetHigh();                                   // set CS high to end 
            Nop();
            SS1OUT_SetLow();                                    // set CS Low to start transmission
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[MANUAL_CH1]);        // read the channel 1 of ADC
            highData = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            lowData = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            SS1OUT_SetHigh();                                   // set CS high to end transmission
            Nop();
            SS1OUT_SetLow();                                    // set CS Low to start transmission
            dummyRead = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[MANUAL_CH0]);        // read the channel 2 of ADC
            highData1 = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            lowData1 = SPI1_Exchange16bit(TemperatureControl.Command_ARRY[DUMMY_WRITE]);
            SS1OUT_SetHigh();                                   // set CS high to end transmission
            

            // Arrange data
            TemperatureControl.ADC_Count = (uint32_t) highData << 16;
            TemperatureControl.ADC_Count = TemperatureControl.ADC_Count |  lowData;
            TemperatureControl.ADC_Count = TemperatureControl.ADC_Count >> 14;                  // to use all the 18 bits received
            TemperatureControl.Temp_Count = TemperatureControl.ADC_Count & 0x3FFFF;
            
            TemperatureControl.ADC_Count = (uint32_t) highData1 << 16;
            TemperatureControl.ADC_Count = TemperatureControl.ADC_Count |  lowData1;
            TemperatureControl.ADC_Count = TemperatureControl.ADC_Count >> 14;                  // to use all the 18 bits received
            TemperatureControl.Press_Count = TemperatureControl.ADC_Count & 0x0003FFFF;

            TemperatureControl.ADC_Status = TEMP_ADC_STATE_END;
                    
        break;
    
        case TEMP_ADC_STATE_END : 
            TemperatureControl.Temp_Buffer[TemperatureControl.Buffer_Counter] = TemperatureControl.Temp_Count;
            TemperatureControl.Press_Buffer[TemperatureControl.Buffer_Counter] = TemperatureControl.Press_Count;
            
            TemperatureControl.Buffer_Counter++;
            if(TemperatureControl.Buffer_Counter >= MAX_BUFFSIZE)
            {
                TemperatureControl.Buffer_Counter = 0;
                TemperatureControl.ADC_Count = 0;
                TemperatureControl.Press_Count = 0;
                TemperatureControl.Flags.Buffer_Ready = true;
            }
            if(TemperatureControl.Flags.Buffer_Ready)
            {
                uint8_t temp;
                TemperatureControl.Flags.Buffer_Ready = false;
                TemperatureControl.Temp_Count = 0;
                TemperatureControl.Press_Count = 0;
                for(temp = 0; temp < MAX_BUFFSIZE; temp++)
                {
                    TemperatureControl.Temp_Count = TemperatureControl.Temp_Count + TemperatureControl.Temp_Buffer[temp];
                    TemperatureControl.Press_Count = TemperatureControl.Press_Count + TemperatureControl.Press_Buffer[temp];
                }
                TemperatureControl.Temp_Value = TemperatureControl.Temp_Count / MAX_BUFFSIZE;
                TemperatureControl.Press_Value = TemperatureControl.Press_Count / MAX_BUFFSIZE;
            }
            TemperatureControl.ADC_Status = TEMP_ADC_STATE_READ;

        break;
        
        default : 
            TemperatureControl.ADC_Status = TEMP_ADC_STATE_IDLE;
        break;
    }

}

uint32_t TemperatureControl_GetTempADC(void)
{
    return (TemperatureControl.Temp_Value);
}

uint32_t TemperatureControl_GetPressADC(void)
{
    return (TemperatureControl.Press_Value);
}

bool TemperatureControl_GetErrorFlag(void)
{
    return (TemperatureControl.Flags.TECError);
}

