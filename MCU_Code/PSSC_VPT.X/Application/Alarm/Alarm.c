/**
 ******************************************************************************
 * @file       Alarm.c
 * @author     Dnyaneshwar 
 * @date       06 Feb 2021
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
File name:    Alarm.c
                    
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
#include "Alarm.h"
#include "../mcc_generated_files/pwm.h"
#include "mcc_generated_files/pin_manager.h"
#include "ShakerMotor.h"
#include "../Error/Error.h"

//ALARM_STYP Alarm = ALARM_DEFAULTS;

static uint16_t Alarm_Period;
static uint16_t Alarm_DutyCycle;
static uint16_t Alarm_DeadtimeLow;
static uint16_t Alarm_DeadtimeHigh;

const uint16_t Alarm_DutyArray[6] = {0x00C7, 0X018F, 0X031F, 0X04AF, 0X063F, 0X076B};
/**
 * @brief This method Initialises the Alarm Control Parameters
 * @param Nothing
 * @return Nothing
 */
void Alarm_Initialise(void)
{
    PWM_GeneratorDisable(PWM_GENERATOR_8);
    Alarm_Period = ALARM_DUTY_PERIOD;
    Alarm_DutyCycle = ALARM_DEFAULT_DUTY_CYCLE;
    Alarm_DeadtimeLow = 0X05;
    Alarm_DeadtimeHigh = 0X0A;
    Alarm.Flags.Alarm_En = false;
    Alarm.Flags.Error_En = false;
}

/**
 * @brief This function is called from schedular with interval time
 *          This function controls the Alarm functioning (constant ON and Pattern ON-OFF) 
 * @param Nothing
 * @return Nothing
 */
void Alarm_Handler(void)
{
    switch(Alarm.Alarm_State)
    {
        case ALARM_STATE_IDLE : 
            if(Alarm.Flags.Alarm_En == true)
            {
                ShakerMotor_UpdateSpeed(0,0);
                Alarm.Current_Level = Alarm.Set_Level;
                Alarm.Alarm_State = ALARM_STATE_RUNNING;
                Alarm.Flags.Alarm_Pattern = false;
                Alarm_DutyCycle = Alarm_DutyArray[Alarm.Current_Level];
                Alarm_Drive();
            }
            if(Alarm.Flags.Error_En == true)
            {
                ShakerMotor_UpdateSpeed(0,0);
                Alarm.Current_Level = Alarm.Set_Level;
                Alarm.Alarm_State = ALARM_STATE_RUNNING;
                Alarm.Pattern_Counter = 0;
                Alarm.Flags.Alarm_Status = true;
                Alarm_DutyCycle = Alarm_DutyArray[Alarm.Current_Level];
                Alarm_Drive();
            }
        break;
        
        case ALARM_STATE_RUNNING :
            Alarm.Alarm_Counter++;
            if(Alarm.Alarm_Counter > MAX_ON_TIME)
            {
                Alarm.Alarm_Counter = 0;
                Alarm.Alarm_State = ALARM_STATE_STOP;
            }
            if(Error_GetFlag() == false)
            {
                Alarm.Flags.Alarm_Status = false;
            }
            if(Alarm.Flags.Alarm_En == true)
            {
                Alarm.Pattern_Counter++;
                if(Alarm.Pattern_Counter > MAX_PATTERN_TIME)
                {
                    Alarm.Pattern_Counter = 0;
                    if(!Alarm.Flags.Alarm_Pattern)
                    {
                        Alarm_Stop();
                        Alarm.Flags.Alarm_Pattern = true;
                    }
                    else
                    {
                        Alarm_Drive();
                        Alarm.Flags.Alarm_Pattern = false;
                    }
                }
                
            }
            if(Alarm.Flags.Error_En == true)
            {
                if(!Alarm.Pattern_Counter)
                {
                    Alarm.Pattern_Counter++;
                    Alarm_Stop();
                }
                else
                {
                    Alarm.Pattern_Counter = 0;
                    Alarm_Drive();
                }
                if(Alarm.Flags.Alarm_Status == false)
                {
                    Alarm.Alarm_State = ALARM_STATE_STOP;
                }
            }
            
        break;
    
        case ALARM_STATE_STOP : 
            Alarm_Stop();
            Alarm.Flags.Alarm_En = false;
            Alarm.Flags.Error_En = false;
            Alarm.Flags.Alarm_Status = false;
            Alarm.Pattern_Counter = 0;
            Alarm.Alarm_Counter = 0;
            Alarm.Alarm_State = ALARM_STATE_IDLE;
        break;
        
        default : 
            PWM_GeneratorDisable(PWM_GENERATOR_8);                      // turn off PWM generator
        break;
    }
}

/**
 * @brief This function generates PWM to drive the alarm 
 * @param Nothing
 * @return Nothing
 */
void Alarm_Drive(void)
{
    PWM_GeneratorDisable(PWM_GENERATOR_8);                          // turn off PWM generator
    PG8IOCONLbits.SWAP = true;                                     // PWMxH output will be connected to PWMxH output pin
    PWM_PeriodSet(PWM_GENERATOR_8, Alarm_Period);                      // Set Period (1kHz )
    PWM_DutyCycleSet(PWM_GENERATOR_8, Alarm_DutyCycle);                // Set Duty Cycle (as per user)
    PWM_DeadTimeLowSet(PWM_GENERATOR_8, Alarm_DeadtimeLow);            // Set Falling Edge Dead Time (n = 05 => n * 100 us = 500 us)
    PWM_DeadTimeHighSet(PWM_GENERATOR_8, Alarm_DeadtimeHigh);          // Set Rising Edge Dead Time (n = 10 => n * 100 us = 1000 us)
    PWM_GeneratorEnable(PWM_GENERATOR_8);                           // turn on PWM generator
}

/**
 * @brief This function is called if SOM module has a error or cycle complete
 * @param Nothing
 * @return Nothing
 */
void Alarm_UpdateAlarm(bool flagSet)
{
    Alarm.Flags.Alarm_En = flagSet;
    Alarm.Flags.Alarm_Status = flagSet;
    Alarm_Period = ALARM_DUTY_PERIOD;
    Alarm_DutyCycle = ALARM_DEFAULT_DUTY_CYCLE;
}

/**
 * @brief This function is called if any error occured in MCU 
 * @param Nothing
 * @return Nothing
 */
void Alarm_UpdateError(bool flagSet)
{
    if(Alarm.Flags.Alarm_Error)
    {
        Alarm.Flags.Error_En = flagSet;
        Alarm.Flags.Alarm_Status = flagSet;
        Alarm_Period = ERROR_DUTY_PERIOD;
        Alarm_DutyCycle = ERROR_DEFAULT_DUTY_CYCLE;
    }
}

/**
 * @brief This function is called ofter ON by SOM to set the volume and alarm ON-OFF function
 * @param Nothing
 * @return Nothing
 */
void Alarm_UpdateVolume(bool flagSet, uint8_t bLevel)
{
    Alarm.Flags.Alarm_Error = flagSet;
    if((bLevel >= MIN_LEVEL) && (bLevel <= MAX_LEVEL))
    {
        Alarm.Set_Level = bLevel;
    }
    else
    {
        Alarm.Set_Level = DEFAULT_LEVEL;
    }
}

bool Alarm_GetStatus(void)
{
    return (Alarm.Flags.Alarm_En);
}

uint16_t Alarm_GetValue(void)
{
    return (Alarm.Current_Level);
}

void Alarm_Stop(void)
{
    PWM_GeneratorDisable(PWM_GENERATOR_8);              // turn off PWM generator
}