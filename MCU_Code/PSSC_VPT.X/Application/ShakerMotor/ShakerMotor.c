/**
 ******************************************************************************
 * @file       Shaker Motor Control.c
 * @author     Dnyaneshwar 
 * @date       07 Jan 2021
 * @brief      This is a source file containing PWM to control Shaker Motor for 
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
File name:    ShakerMotor.c
                    
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
       07-01-2021  Initial Write                        Dnyaneshwar Pawar
--------------------------------------------------------------------------------
*/

#include "xc.h"
#include <stdbool.h>
#include "Alarm.h"
#include "ShakerMotor.h"
#include "clock.h"
#include "../mcc_generated_files/pwm.h"
#include "mcc_generated_files/pin_manager.h"
#include "Error.h"

//VALVEMOTOR_STYP ShakerMotor = VALVEMOTOR_DEFAULTS;

static uint16_t SM_Period;
static uint16_t SM_DutyCycle;
static uint16_t SM_DeadtimeLow;
static uint16_t SM_DeadtimeHigh;
static uint8_t  Debounce_Counter;
static uint8_t  Err_Debounce_Counter;
static uint16_t Check_Counter;
static uint16_t SM_TempSpeed;
static uint16_t SM_TempPrevSpeed;
static uint16_t SM_TempSpeedVal;
bool SMFLAG_PulseErrCheck;
bool softStart = false;
static uint8_t  Debounce_CounterFor270;

/**
 * @brief This method Initialises the Shaker motor variables
 * @param Nothing
 * @return Nothing
 */
void ShakerMotor_Initialise(void)
{
    MICRO_STEP1_SetDigitalOutput();
    MICRO_STEP2_SetDigitalOutput();
    SHAKERMTR_EN_SetDigitalOutput();
    POSITION_SHAKER_SetDigitalInput();
    
    MICRO_STEP1_SetLow();
    MICRO_STEP2_SetLow();
    SHAKERMTR_EN_SetHigh();
    
    ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_IDLE;
    SM_Period = 0X1F3F;
    SM_DutyCycle = 0X00;
    SM_DeadtimeLow = 0X05;
    SM_DeadtimeHigh = 0X0A;
    ShakerMotor.Current_Speed = 0;
    ShakerMotor.Set_Speed = 0;
    Debounce_Counter = 0;
    Err_Debounce_Counter = 0;
    Check_Counter = 0;
    SM_TempSpeed = 0;
    SM_TempPrevSpeed = 0;
    SM_TempSpeedVal = 0;
    SMFLAG_PulseErrCheck = false;
    ShakerMotor_Stop();
    Debounce_CounterFor270 = 0;
}
       
/**
 * @brief This function is called from schedular with interval time
 *          This function controls the shaker motor movement 
 *          Soft start is implemented in this function controling the microstep
 * @param Nothing
 * @return Nothing
 */
void ShakerMotor_Handler(void)
{

    switch(ShakerMotor.SMState_Status)
    {
        case SHAKERMOTOR_STATE_IDLE : 
            
            if((ShakerMotor.Flags.SMEn == false) &&         \
                    (Alarm_GetStatus() == false) && (Error_GetFlag() == false))
            {
                ShakerMotor_Stop();
                ShakerMotor.Flags.SMCheck = false;
                ShakerMotor.Current_Speed = 0;
                Err_Debounce_Counter = 0;
            }
            
            if((ShakerMotor.Flags.SMEn == true) &&      \
                    (ShakerMotor.Flags.SMCheck == false) &&        \
                    (Alarm_GetStatus() == false) && (Error_GetFlag() == false))
            {
                SM_Period = 0XD054;
                SM_DutyCycle = 0X682A;
                MICRO_STEP1_SetHigh();
//                MICRO_STEP1_SetLow();
                MICRO_STEP2_SetHigh();
//                MICRO_STEP2_SetLow();
                ShakerMotor.Flags.SMCheck = true;
                ShakerMotor_Drive();
                Check_Counter = 0;
            }
            
            if(((ShakerMotor.Flags.SMEn == true) && (POSITION_SHAKER_GetValue() == false) && \
                    (ShakerMotor.Flags.SMCheck == true) && (Alarm_GetStatus() == false)))
            {
                ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_SOFTSTART;
//                softStart = true;
                /*Debounce_Counter++;
                if(Debounce_Counter >= MAX_DEBOUNCE_COUNT)
                {
                    Debounce_Counter = 0;
                    Check_Counter = 0;
                    MICRO_STEP1_SetLow();
                    MICRO_STEP2_SetLow();
//                    MICRO_STEP1_SetHigh();
//    //                MICRO_STEP1_SetLow();
//                    MICRO_STEP2_SetHigh();
//    //                MICRO_STEP2_SetLow();
                    ShakerMotor.Flags.SMCheck = false;
                    ShakerMotor.Flags.SMEdited = true;
//                    SM_TempSpeed = INIT_SPEED;
                    SM_TempPrevSpeed = 0;
                    SM_Period = 0XD054;
                    SM_DutyCycle = 0X682A;
//                    ShakerMotor_CalculateSpeed(SM_TempSpeed);
                    ShakerMotor_Drive();
                    Err_Debounce_Counter = 0;
                    SMFLAG_PulseErrCheck = false;
                    ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_SOFTSTART;
                    softStart = true;
                }*/
            }
            else
            {
                Debounce_Counter = 0;
            }
            
            if((ShakerMotor.Flags.SMEn == true) && (POSITION_SHAKER_GetValue() == true) && \
                    (ShakerMotor.Flags.SMCheck == true) && (Alarm_GetStatus() == false))
            {
                if(SMFLAG_PulseErrCheck == false)
                {
                    Check_Counter++;
                    if(Check_Counter >= MAX_WAIT_TIME)
                    {
                        Check_Counter = 0;
//                        ShakerMotor_Stop();
                        
                        if(Error_GetCycleRunSts() == true)
                        {
                            Err_Debounce_Counter++;
                            if(Err_Debounce_Counter >= SM_MAX_ERR_COUNT)
                            {
                                Err_Debounce_Counter = 0;
                                ShakerMotor_Stop();
                                ShakerMotor.Flags.SMError = true;
                                Error_Report(SHAKER_MOTOR);
                                Alarm_UpdateError(ShakerMotor.Flags.SMError);
                                ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_ERROR;
                            }
                            else
                            {
                                SMFLAG_PulseErrCheck = true;
                                Error_Report(SHAKER_MOTOR);
                            }
                        }
                        else
                        {
                            ShakerMotor_Stop();
                            ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_STOPPING;
                        }
                    }
                }
            }
            if(Error_GetFlag() == true)
            {
                ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_ERROR;
            }
        break;
        
        case SHAKERMOTOR_STATE_EIGHT_MICROSTEP :
            Debounce_Counter++;
            if(Debounce_Counter >= SPEED_DEBOUNCE_COUNT)
            {
                Debounce_Counter = 0;
                SM_TempSpeed +=  STEP_SPEED;
                ShakerMotor.Current_Speed = SM_TempSpeed / 8;
                ShakerMotor_CalculateSpeed(SM_TempSpeed);
                PWM_PeriodSet(PWM_GENERATOR_8, SM_Period);
                PWM_DutyCycleSet(PWM_GENERATOR_8, SM_DutyCycle);
                PWM_SoftwareUpdateRequest(PWM_GENERATOR_8);
                if(SM_TempSpeed >= ShakerMotor.Set_Speed)
                {
                    SM_TempPrevSpeed = ShakerMotor.Current_Speed;
                    ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_FOUR_MICROSTEP;
                    ShakerMotor_CalculateSpeed(ShakerMotor.Current_Speed);
                    MICRO_STEP1_SetLow();
                    MICRO_STEP2_SetHigh();
                    PWM_PeriodSet(PWM_GENERATOR_8, SM_Period);
                    PWM_DutyCycleSet(PWM_GENERATOR_8, SM_DutyCycle);
                    PWM_SoftwareUpdateRequest(PWM_GENERATOR_8);
                    SM_TempSpeed = 0;
                }
            }
        break;
        
        case SHAKERMOTOR_STATE_FOUR_MICROSTEP :
            Debounce_Counter++;
            if(Debounce_Counter >= SPEED_DEBOUNCE_COUNT)
            {
                Debounce_Counter = 0;
                SM_TempSpeed +=  STEP_SPEED;
                ShakerMotor.Current_Speed = SM_TempPrevSpeed + (SM_TempSpeed / 4);
                SM_TempSpeedVal = (SM_TempPrevSpeed * 4) + SM_TempSpeed;
                ShakerMotor_CalculateSpeed(SM_TempSpeedVal);
                PWM_PeriodSet(PWM_GENERATOR_8, SM_Period);
                PWM_DutyCycleSet(PWM_GENERATOR_8, SM_DutyCycle);
                PWM_SoftwareUpdateRequest(PWM_GENERATOR_8);
                if(SM_TempSpeedVal >= ShakerMotor.Set_Speed)
                {
//                    SM_TempSpeed = ShakerMotor.Set_Speed / 4;
                    ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_TWO_MICROSTEP;
                    ShakerMotor_CalculateSpeed(ShakerMotor.Current_Speed);
                    MICRO_STEP1_SetHigh();
                    MICRO_STEP2_SetLow();
                    PWM_PeriodSet(PWM_GENERATOR_8, SM_Period);
                    PWM_DutyCycleSet(PWM_GENERATOR_8, SM_DutyCycle);
                    PWM_SoftwareUpdateRequest(PWM_GENERATOR_8);
//                    SM_TempPrevSpeed += SM_TempSpeed;
                    SM_TempPrevSpeed = ShakerMotor.Current_Speed;
                    SM_TempSpeed = 0;
                }
            }
        break;
        
        case SHAKERMOTOR_STATE_TWO_MICROSTEP :
            Debounce_Counter++;
            if(Debounce_Counter >= SPEED_DEBOUNCE_COUNT)
            {
                Debounce_Counter = 0;
                SM_TempSpeed +=  STEP_SPEED;
                ShakerMotor.Current_Speed = SM_TempPrevSpeed + (SM_TempSpeed / 2);
                SM_TempSpeedVal = (SM_TempPrevSpeed * 2) + SM_TempSpeed;
                ShakerMotor_CalculateSpeed(SM_TempSpeedVal);
                PWM_PeriodSet(PWM_GENERATOR_8, SM_Period);
                PWM_DutyCycleSet(PWM_GENERATOR_8, SM_DutyCycle);
                PWM_SoftwareUpdateRequest(PWM_GENERATOR_8);
                if(SM_TempSpeedVal >= ShakerMotor.Set_Speed)
                {
                    ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_SOFTSTART;
                    ShakerMotor_CalculateSpeed(ShakerMotor.Current_Speed);
                    MICRO_STEP1_SetLow();
                    MICRO_STEP2_SetLow();
                    PWM_PeriodSet(PWM_GENERATOR_8, SM_Period);
                    PWM_DutyCycleSet(PWM_GENERATOR_8, SM_DutyCycle);
                    PWM_SoftwareUpdateRequest(PWM_GENERATOR_8);
                    SM_TempPrevSpeed = ShakerMotor.Current_Speed;
                    SM_TempSpeed = 0;
                }
            }
        break;
        
        case SHAKERMOTOR_STATE_SOFTSTART :
            softStart = true;
//            ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_RUNNING;
            /*Debounce_Counter++;
//            if(Debounce_Counter >= SPEED_DEBOUNCE_COUNT)
            if(Debounce_Counter >= 3)
            {
                Debounce_Counter = 0;
                SM_TempSpeed += STEP_SPEED;
//                ShakerMotor.Current_Speed = SM_TempPrevSpeed + SM_TempSpeed;
//                ShakerMotor.Current_Speed = ShakerMotor.Set_Speed;
                Debounce_CounterFor270++;
                if(Debounce_CounterFor270 == 1){
                    ShakerMotor.Current_Speed = (ShakerMotor.Set_Speed / 3);
                }else if(Debounce_CounterFor270 == 2){
                    ShakerMotor.Current_Speed = (ShakerMotor.Set_Speed / 2);
                }else if (Debounce_CounterFor270 == 3){
                    ShakerMotor.Current_Speed = ShakerMotor.Set_Speed;
                }
                ShakerMotor_CalculateSpeed(ShakerMotor.Current_Speed);
                PWM_PeriodSet(PWM_GENERATOR_8, SM_Period);
                PWM_DutyCycleSet(PWM_GENERATOR_8, SM_DutyCycle);
                PWM_SoftwareUpdateRequest(PWM_GENERATOR_8);
//                if(ShakerMotor.Current_Speed >= ShakerMotor.Set_Speed)
                if(Debounce_CounterFor270 >= 4)
                {
                    Debounce_CounterFor270 = 0;
                    ShakerMotor.Current_Speed = ShakerMotor.Set_Speed;
                    ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_RUNNING;
                }
            }*/
        break;    
        
        case SHAKERMOTOR_STATE_RUNNING : 
            if(ShakerMotor.Flags.SMEn == false)
            {
                ShakerMotor_Stop();
                ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_STOPPING;
            }
            if(ShakerMotor.Flags.SMError == true)
            {
                ShakerMotor_Stop();
                ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_ERROR;
            }
            
            if(Error_GetFlag() == true)
            {
                ShakerMotor_Stop();
                ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_ERROR;
            }
            if(POSITION_SHAKER_GetValue() == false)
            {
                Check_Counter = 0;
            }
            else
            {
                if(SMFLAG_PulseErrCheck == false)
                {
                    Check_Counter++;
                    if(Check_Counter >= MAX_WAIT_TIME)
                    {
                        Check_Counter = 0;
                        if(Error_GetCycleRunSts() == true)
                        {
                            Err_Debounce_Counter++;
                            if(Err_Debounce_Counter >= SM_MAX_ERR_COUNT)
                            {
                                Err_Debounce_Counter = 0;
                                ShakerMotor.Flags.SMError = true;
                                Error_Report(SHAKER_MOTOR);
                                Alarm_UpdateError(ShakerMotor.Flags.SMError);
                                ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_ERROR;
                            }
                            else
                            {
                                SMFLAG_PulseErrCheck = true;
                                Error_Report(SHAKER_MOTOR);
                            }
                        }
                        else
                        {
                            ShakerMotor_Stop();
                            ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_STOPPING;
                        }
                    }
                }
            }
        break;
    
        case SHAKERMOTOR_STATE_STOPPING : 
                Err_Debounce_Counter = 0;
                ShakerMotor.Flags.SMEn = false;
                ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_IDLE;
                SM_TempPrevSpeed = 0;
                SM_TempSpeed = 0;
                SM_TempSpeedVal = 0;
        break;
        
        case SHAKERMOTOR_STATE_ERROR : 
//            ShakerMotor_Stop();
            ShakerMotor.Flags.SMCheck = false;
            Debounce_Counter = 0;
            if(Error_GetFlag() == false)
            {
                ShakerMotor.Flags.SMError = false;
                ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_STOPPING;
            }
            
        break;
        
        default : 
            PWM_GeneratorDisable(PWM_GENERATOR_8);                      // turn off PWM generator
        break;
    }
}

void ShakerMotor_SoftStartFunction(void){
    if(softStart){
        SM_TempSpeed += STEP_SPEED;
        ShakerMotor.Current_Speed = SM_TempPrevSpeed + SM_TempSpeed;
//        ShakerMotor.Current_Speed = ShakerMotor.Set_Speed;
        ShakerMotor_CalculateSpeed(ShakerMotor.Current_Speed);
        PWM_PeriodSet(PWM_GENERATOR_8, SM_Period);
        PWM_DutyCycleSet(PWM_GENERATOR_8, SM_DutyCycle);
        PWM_SoftwareUpdateRequest(PWM_GENERATOR_8);
        if(ShakerMotor.Current_Speed >= ShakerMotor.Set_Speed)
        {
            ShakerMotor.Current_Speed = ShakerMotor.Set_Speed;
            MICRO_STEP1_SetLow();
            MICRO_STEP2_SetLow();
            ShakerMotor.SMState_Status = SHAKERMOTOR_STATE_RUNNING;
            softStart = false;
        }
    }
}

/**
 * @brief This function starts the PWM output
 * @param Nothing
 * @return Nothing
 */
void ShakerMotor_Drive(void)
{
    PWM_GeneratorDisable(PWM_GENERATOR_8);                          // turn off PWM generator
    PG8IOCONLbits.SWAP = false;                                     // PWMxH output will be connected to PWMxH output pin
    PWM_PeriodSet(PWM_GENERATOR_8, SM_Period);                      // Set Period (n = 3192 => 1 / (n * 100us) = 10 kHz )
    PWM_DutyCycleSet(PWM_GENERATOR_8, SM_DutyCycle);                // Set Duty Cycle (n = 1596 => n / PGxPER = 50 %)
    PWM_DeadTimeLowSet(PWM_GENERATOR_8, SM_DeadtimeLow);            // Set Falling Edge Dead Time (n = 05 => n * 100 us = 500 us)
    PWM_DeadTimeHighSet(PWM_GENERATOR_8, SM_DeadtimeHigh);          // Set Rising Edge Dead Time (n = 10 => n * 100 us = 1000 us)
    SHAKERMTR_EN_SetLow();
    PWM_GeneratorEnable(PWM_GENERATOR_8);                           // turn on PWM generator
}

/**
 * @brief This function is called by som to turn on and set the shaker motor speed 
 * @param enable flag, set speed
 * @return Nothing
 */
void ShakerMotor_UpdateSpeed(bool flagSet, uint16_t wSpeed)
{
    ShakerMotor.Flags.SMEn = flagSet;
    
    if(ShakerMotor.Flags.SMEn == true)
    {
        ShakerMotor.Set_Speed = wSpeed;
//        if((wSpeed >= MIN_SPEED) && (wSpeed <= MAX_SPEED))
//        {
//            ShakerMotor.Set_Speed = wSpeed;
//        }
//        else
//        {
//            ShakerMotor.Set_Speed = DEFAULT_SPEED;
//        }
    }
    else
    {
        ShakerMotor.Set_Speed = 0;
    }
}

bool ShakerMotor_GetStatus(void)
{
    return (ShakerMotor.Flags.SMEn);
}

uint16_t ShakerMotor_GetSpeed(void)
{
    return (ShakerMotor.Current_Speed);
}

void ShakerMotor_Stop(void)
{
    SHAKERMTR_EN_SetHigh();
    PWM_GeneratorDisable(PWM_GENERATOR_8);              // turn off PWM generator
}
/**
 * @brief This function calculates the frequency to be set to achieve the set speed for shaker motor
 * @param speed
 * @return Nothing
 */
void ShakerMotor_CalculateSpeed(uint16_t wSpeed)
{
    uint16_t cycleControl;
    
    cycleControl = (uint16_t) (CLOCK_SystemFrequencyGet() /  (wSpeed / STEP_SIZE)) - 1;
    SM_Period = cycleControl;
    SM_DutyCycle = SM_Period / 2;
}

bool ShakerMotor_GetErrFlag(void)
{
    return (ShakerMotor.Flags.SMError);
}

uint16_t ShakerMotor_GetCounter(void)
{
    return (Check_Counter);
}

bool ShakerMotor_GetPulseErrCheck(void)
{
    return(SMFLAG_PulseErrCheck);
}

void ShakerMotor_SetPulseErrCheck(bool setFlag)
{
    SMFLAG_PulseErrCheck = setFlag;
}

uint16_t ShakerMotor_ErrCounter(void)
{
    return (Err_Debounce_Counter);
}
