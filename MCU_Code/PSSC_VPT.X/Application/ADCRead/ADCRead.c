/**
 ******************************************************************************
 * @file       ADCRead.c
 * @author     Dnyaneshwar 
 * @date       10 Feb 2021
 * @brief      This is a source file containing PWM to control of Alarm for 
 *             PSSC VPT 
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
File name:    ADCRead.c
                    
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
       06-02-2021  Initial Write                        Dnyaneshwar Pawar
--------------------------------------------------------------------------------
*/

#include "xc.h"
#include <stdbool.h>
#include "ADCRead.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/adc1.h"
#include "Error.h"

//ADCRead_STYP ADCRead = ADC_READ_DEFAULTS;
static ADC1Channel_ETYP Channel_Select;

static uint16_t Buffer_Counter;
static uint16_t ADC_Count;
uint16_t ADC_BufferARRY[TOTAL_ADC_CHANNELS][MAX_BUFFSIZE];

/**
 * @brief This function Initializes the Parameter variables of ADC 
 * @param Nothing
 * @return Nothing
 */
void ADCRead_Initialise(void)
{
    Channel_Select = AMB_TEMP;
    ADCRead.ADCStatus = ADC_CONV_START;
    Buffer_Counter = 0;
    
}

/**
 * @brief This function is called from schedular with interval time
 *          This function reads the performs sampling and conversion to ADC count
 * @param Nothing
 * @return Nothing
 */
void ADCRead_Handler(void)
{
  uint16_t tempValue = 0;

  // ADC Conversion state machine
  switch(ADCRead.ADCStatus)
  {
    // Trigger discharge of sample & hold capacitor
    case ADC_CONV_START:
        ADC1_Enable();
//        ADC1_ChannelSelect(Channel_Select);
//        ADC1_SoftwareTriggerEnable();
        ADCRead.ADCStatus = ADC_CONV_SAMPLING_START;
      break;
      

    // Select actual channel & Start sampling
    case ADC_CONV_SAMPLING_START:
        ADC1_ChannelSelect(Channel_Select);
        ADC1_SoftwareTriggerEnable();
        ADCRead.ADCStatus = ADC_CONV_SAMPLING_END;
      break;

    // Stop sampling. After stopped automatically conversion started
    case ADC_CONV_SAMPLING_END:
        ADC1_SoftwareTriggerDisable();
        ADCRead.ADCStatus = ADC_CONV_READ_DATA;
      break;
      
    case ADC_CONV_READ_DATA:
        // Check ADC conversion status
        if ( ADC1_IsConversionComplete(Channel_Select) == true) 
        {
            // Read the register which have the digital data
            tempValue = ADC1_ConversionResultGet(Channel_Select);
            
            ADCRead_AverageFilter(ADC_BufferARRY[Channel_Select], tempValue);

            // Increment the channel index and if converted all channels increment buffer
            Channel_Select++;
            if ( Channel_Select >= TOTAL_ADC_CHANNELS) 
            {
                // Reset the channel number
                Channel_Select = AMB_TEMP;
                Buffer_Counter++;
                if(Buffer_Counter >= MAX_BUFFSIZE)
                {
                    Buffer_Counter = 0;
                    ADCRead.Flags.Buffer_Ready = true;
                    ADCRead.Flags.Power_DataReady = true;
                }
            }
            ADC1_Disable();
            ADCRead.ADCStatus = ADC_CONV_START;
        }
      break;

      default:
      break;
  }
  
}

/**
 * @brief This function is called when the buffer is full and averaging of buffer needs to be done 
 * @param Nothing
 * @return Nothing
 */
void ADCRead_AverageFilter(uint16_t *arryPTR, uint16_t rawData)
{
    uint8_t i,j;
    
    arryPTR = arryPTR + Buffer_Counter;
    *arryPTR = rawData;
    if(ADCRead.Flags.Buffer_Ready == true)
    {
        ADCRead.Flags.Buffer_Ready = false;
        for(i=0; i < TOTAL_ADC_CHANNELS; i++)
        {
            arryPTR = ADC_BufferARRY[i];
            ADC_Count = 0;
            for(j=0; j < MAX_BUFFSIZE; j++)
            {
                ADC_Count = ADC_Count + *arryPTR;
                arryPTR++;
            }
            ADCRead.ADCResultARRY[i] = ADC_Count / MAX_BUFFSIZE;
        }
    }  
}

/**
 * @brief This function returns the Piston Motor Current feedback 
 * @param Nothing
 * @return Nothing
 */
uint16_t ADCRead_GetPistFb(void)
{
    return (ADCRead.ADCResultARRY[ADC_PIST_MTR_C_FB]);
//    return (ADC_BufferARRY[ADC_PIST_MTR_C_FB][0]);
}

/**
 * @brief This function returns the Valve Motor Current feedback 
 * @param Nothing
 * @return Nothing
 */
uint16_t ADCRead_GetValFb(void)
{
    return (ADCRead.ADCResultARRY[ADC_VAL_MTR_C_FB]);
}

/**
 * @brief This function returns the ambient temperature of on board sensor 
 * @param Nothing
 * @return Nothing
 */
uint16_t ADCRead_GetAmbTemp(void)
{
    if(ADCRead.Flags.Power_DataReady == true)
    {
        return (ADCRead.ADCResultARRY[AMB_TEMP]);
    }
    else
    {
        return(500);
    }
}