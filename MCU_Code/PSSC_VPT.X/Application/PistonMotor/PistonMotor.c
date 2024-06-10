/**
 ******************************************************************************
 * @file       Piston Motor Control.c
 * @author     Dnyaneshwar 
 * @date       23 Dec 2020
 * @brief      This is a source file containing PWM to control Piston Motor for 
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
File name:    PistonMotor.c
                    
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
       23-12-2020  Initial Write                        Dnyaneshwar Pawar
--------------------------------------------------------------------------------
*/

#include "xc.h"
#include <stdbool.h>
#include "PistonMotor.h"
#include "../mcc_generated_files/sccp3_capture.h"
#include "../mcc_generated_files/pwm.h"
#include "mcc_generated_files/pin_manager.h"
#include "PistonEncoder.h"
#include "ADCRead.h"
#include "Error.h"
#include "Alarm.h"
#include "ValveMotor.h"

//PISTONMOTOR_STYP PistonMotor = PISTONMOTOR_DEFAULTS;

static uint16_t PM_Period;
static uint16_t PM_DutyCycle;
static uint16_t PM_DeadtimeLow;
static uint16_t PM_DeadtimeHigh;
static uint32_t Total_Pulses;
static uint32_t Dynamic_Total_Pulses;
static uint16_t PMDebounce_Counter;
static uint16_t PMErr_Counter;

static float Previous_Position;

uint32_t A_Pulses = 0;
uint32_t A = 0;
uint32_t DownCount3By4 = 0;
uint32_t DownCount = 0;
uint32_t UpCount3By4 = 0;
uint32_t UpCount = 0;

/**
 * @brief This function initializes the piston motor parameters 
 * @param Nothing
 * @return Nothing
 */
void PistonMotor_Initialise(void)
{
    PISTON_HES_LED_SetDigitalOutput();
    PISTONMTR_EN_SetDigitalOutput();
    POSITION_PISTON_SetDigitalInput();
    PISTONMTR_EN_SetLow();
    PISTON_HES_LED_SetHigh();
    Total_Pulses = 0;
    Dynamic_Total_Pulses = 0;
    Previous_Position = 0.0;
    PWM_GeneratorDisable(PWM_GENERATOR_1);
    PM_Period = PISTON_DUTY_PERIOD;
    PM_DutyCycle = PISTON_DEFAULT_DUTY_CYCLE;
    PM_DeadtimeLow = 0X05;
    PM_DeadtimeHigh = 0X0A;
    PistonMotor.Current_Position = 1.0;
    PistonMotor.Set_Position = 1.0;
    PistonMotor.Flags.EnPM = false;
    PistonMotor.Flags.EditedPM = false;
    PistonMotor.Flags.EditedSet = false;
    PistonMotor.Flags.ErrorRun = false;
    PMDebounce_Counter = 0;
    PMErr_Counter = 0;
//    PistonEncoder_ClearCountOfAB_1();
    PistonEncoder_ClearCountFirstCount();
}
 
/**
 * @brief This function is called from schedular with interval time
 *          This function controls the Piston motor movement 
 * @param Nothing
 * @return Nothing
 */
void PistonMotor_Handler(void)
{
    PistonMotor_HesLedStatus();
    PistonMotor_CheckError();
    PistonMotor_ChangedPosition();
    switch(PistonMotor.PMState_Status)
    {
        case PISTONMOTOR_STATE_IDLE : 
            if(((PistonMotor.Flags.EnPM == true) || (PistonMotor.Flags.EditedSet == true)) \
                    && (PistonMotor.Flags.ErrorPM == false) && (PistonMotor.Flags.ErrorRun == false))
            {
                PistonEncoder_SetEnableFlag(true);
                //if piston motor set position is greater than current position move motor upside
                if((PistonMotor.Set_Position / CONVERSION_CONSTANT) > (PistonMotor.Current_Position / CONVERSION_CONSTANT))
                {
                    PistonMotor.Flags.EnPM = true;
                    PM_DutyCycle = PISTON_DEFAULT_DUTY_CYCLE;
                    PistonEncoder_ExpectedCount(true, (PistonMotor.Set_Position - PistonMotor.Current_Position));
                    UpCount = (PistonMotor.Set_Position - PistonMotor.Current_Position);
                    if(PistonMotor.Set_Position == (0.25*CONVERSION_CONSTANT))
                    {
                        PM_DutyCycle = PISTON_DYNAMIC_DUTY_CYCLE;
                    }
                    PistonMotor_Up();
                    PistonMotor.Flags.PMStatus = true;
                }
                //if piston motor set position is smaller than current position move motor downside
                else if((PistonMotor.Set_Position / CONVERSION_CONSTANT) < (PistonMotor.Current_Position / CONVERSION_CONSTANT))
                {
                    PistonMotor.Flags.EnPM = true;
                    PM_DutyCycle = PISTON_DEFAULT_DUTY_CYCLE;
                    if(PistonMotor.Set_Position == 0.0f)
                    {
                        PistonEncoder_ExpectedCount(false, PistonMotor.Current_Position);
                        DownCount = PistonMotor.Current_Position;
                    }
                    else
                    {
                        PistonEncoder_ExpectedCount(false, PistonMotor.Current_Position - PistonMotor.Set_Position);
                        DownCount = PistonMotor.Current_Position - PistonMotor.Set_Position;
                    }
                    PistonMotor_Down();
                    PistonMotor.Flags.PMStatus = false;
                }
                else
                {
                    PistonMotor.Flags.EnPM = false;
                }
                PMDebounce_Counter = 0;
                PistonMotor.Flags.EditedPM = true;
                PistonMotor.Flags.EditedSet = false;
                PistonMotor.PMState_Status = PISTONMOTOR_STATE_RUNNING;
            }
            //when piston motor reaches at bottom after power on turn off the motor only if motor is on
            if(((PistonMotor.Flags.EnPM == false) && (POSITION_PISTON_GetValue() == false) &&    \
                    (PistonMotor.Flags.EditedPM == false) && (PistonMotor.Flags.PMCheck == true)) || \
                    (Error_GetFlag() == true))
            {
                if(Error_GetFlag() == false)
                {
                    PistonMotor.Current_Position = 0.0f;
                }
                PistonMotor.Flags.PMCheck = false;
                Previous_Position = 0.0f;
                PistonMotor_Stop();
            }
            //if piston motor is not at bottom position after power on turn on the motor
            if((PistonMotor.Flags.EnPM == false) && (POSITION_PISTON_GetValue() == true)        \
                    && (PistonMotor.Flags.EditedPM == false) && (PistonMotor.Flags.PMCheck == false) && \
                    (PistonMotor.Flags.ErrorRun == false) && (Error_GetFlag() == false))
            {
                if(PistonMotor.Set_Position == 0.0f)
                {
                    PistonMotor.Flags.PMCheck = true;
                    PM_DutyCycle = PISTON_DEFAULT_DUTY_CYCLE;
                    PistonMotor_SetInitialisedToZero(true);
                    PistonMotor_Down();
                    PMDebounce_Counter = 0;
                }
            }
            
            if((PistonMotor.Flags.EnPM == false) && (POSITION_PISTON_GetValue() == true) &&    \
                    (PistonMotor.Flags.EditedPM == false) && (PistonMotor.Flags.PMCheck == true))
            {
                PMDebounce_Counter++;
                if(PMDebounce_Counter >= MAX_PM_WAIT_TIME)
                {
                    PMDebounce_Counter = 0;
                    PistonMotor_Stop();
                    if((Error_GetCycleRunSts() == true) && (PistonMotor.Flags.ErrorRun == false))
                    {
                        PistonMotor.Flags.ErrorPM = true;
                        PistonMotor.Flags.ErrorRun = true;
                        PistonMotor.PMState_Status = PISTONMOTOR_STATE_ERROR;
                        Error_Report(PISTON_MOTOR);
                        Alarm_UpdateError(PistonMotor.Flags.ErrorPM);
                    }
                }
            }
            
            if( (POSITION_PISTON_GetValue() == false) &&    \
                    (PistonMotor.Flags.EditedPM == false) && (PistonMotor.Flags.PMCheck == false))
            {
                PistonMotor.Flags.ErrorRun = false;
                PistonMotor_Stop();
                PistonMotor.Current_Position = 0.0f;
                Previous_Position = 0.0f;
            }
            
            if(Error_GetFlag() == true)
            {
                PistonMotor_Stop();
                PistonMotor.PMState_Status = PISTONMOTOR_STATE_ERROR;
            }
            
        break;
        
        case PISTONMOTOR_STATE_RUNNING : 
            if(PistonMotor.Flags.EnPM == true)
            {
                Total_Pulses = PistonEncoder_GetCountA() + PistonEncoder_GetCountB();
//                PistonMotor.Current_Position = (float) Total_Pulses / CONVERSION_CONSTANT;
                PistonMotor.Current_Position = (float) Total_Pulses;
                if(PistonMotor.Flags.PMStatus == true)
                {
                    UpCount3By4  = ((UpCount/2) + (UpCount/3));
                    if(Total_Pulses >= (UpCount3By4))
                    {
                        PM_DutyCycle = PISTON_DEFAULT_DUTY_CYCLE_1;
                        PWM_DutyCycleSet(PWM_GENERATOR_1, PM_DutyCycle);
                        PWM_SoftwareUpdateRequest(PWM_GENERATOR_1);
                    }
                    PistonMotor.Current_Position = PistonMotor.Current_Position + Previous_Position;
//                    if(PistonMotor.Set_Position <= PistonMotor.Current_Position)
//                    {
//                        if(PistonMotor.Set_Position == 0.0f)
//                        {
//                            if((POSITION_PISTON_GetValue() == false) && (PistonMotor.Current_Position <= 0.0f))
//                            {
//                                PMDebounce_Counter++;
//                                if(PMDebounce_Counter >= MAX_DEBOUNCE_COUNT)
//                                {
//                                    PMDebounce_Counter = 0;
//                                    PistonMotor_Stop();
//                                    PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
//                                    PistonMotor.Current_Position = PistonMotor.Set_Position;
//                                }
////                                PistonMotor_Stop();
////                                PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
////                                PistonMotor.Current_Position = PistonMotor.Set_Position;
//                            }
//                            else
//                            {
//                                PMDebounce_Counter = 0;
//                            }
//                        }
//                        else
//                        {
//                            PistonMotor_Stop();
//                            PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
//                            PistonMotor.Current_Position = PistonMotor.Set_Position;
//                        }
//                    }
                }
                else
                {
                    DownCount3By4  = ((DownCount/2) + (DownCount/3));
                    if(Total_Pulses >= (DownCount3By4))
                    {
                        PM_DutyCycle = PISTON_DEFAULT_DUTY_CYCLE_1;
                        PWM_DutyCycleSet(PWM_GENERATOR_1, PM_DutyCycle);
                        PWM_SoftwareUpdateRequest(PWM_GENERATOR_1);
                    }
                    PistonMotor.Current_Position = Previous_Position - PistonMotor.Current_Position;
//                    if(PistonMotor.Set_Position >= PistonMotor.Current_Position)
//                    {
//                        if(!PistonMotor.Set_Position)
//                        {
//                            if((POSITION_PISTON_GetValue() == false) && (PistonMotor.Current_Position <= 0.0f))
//                            {
//                                PMDebounce_Counter++;
//                                if(PMDebounce_Counter >= MAX_DEBOUNCE_COUNT)
//                                {
//                                    PMDebounce_Counter = 0;
//                                    PistonMotor_Stop();
//                                    PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
//                                    PistonMotor.Current_Position = PistonMotor.Set_Position;
//                                }
////                                PistonMotor_Stop();
////                                PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
////                                PistonMotor.Current_Position = PistonMotor.Set_Position;
//                            }
//                            else
//                            {
//                                PMDebounce_Counter = 0;
//                            }
//                        }
//                        else
//                        {
//                            PistonMotor_Stop();
//                            PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
//                            PistonMotor.Current_Position = PistonMotor.Set_Position;
//                        }
//                    }
//                    else
//                    {
//                        PMDebounce_Counter = 0;
//                    }
                }
                if(PistonMotor.Current_Position > PM_MAX_POSITION)
                {
                    PistonMotor_Stop();
                    PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
                }
                
                PMErr_Counter++;
                if(PMErr_Counter >= MAX_PM_WAIT_TIME)
                {
                    PMErr_Counter = 0;
                    PistonMotor_Stop();
                    if(Error_GetCycleRunSts() == true)
                    {
                        PistonMotor.Flags.ErrorPM = true;
                        PistonMotor.Flags.ErrorRun = true;
                        PistonMotor.PMState_Status = PISTONMOTOR_STATE_ERROR;
                        Error_Report(PISTON_MOTOR);
                        Alarm_UpdateError(PistonMotor.Flags.ErrorPM);
                    }
                    else
                    {
                        PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
                    }
                }
            }
            else
            {
                PistonMotor_Stop();
                PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
            }
            
            if(PistonEncoder_GetErrorFlag() == true)
            {
                PistonMotor_Stop();
//                PistonMotor.Flags.ErrorPM = true;
//                Error_Report(PISTON_ENCODER);
//                Alarm_UpdateError(PistonMotor.Flags.ErrorPM);
                PistonMotor.PMState_Status = PISTONMOTOR_STATE_ERROR;
            }
            
            if(PistonMotor.Flags.EditedSet == true)
            {
                PistonMotor_Stop();
                PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
            }
            if(PistonMotor.Flags.ErrorPM == true)
            {
                PistonMotor_Stop();
                PistonMotor.PMState_Status = PISTONMOTOR_STATE_ERROR;
            }
            if(Error_GetFlag() == true)
            {
                PistonMotor_Stop();
                PistonMotor.PMState_Status = PISTONMOTOR_STATE_ERROR;
            }
        break;
        
        case PISTONMOTOR_STATE_STOP : 
            PistonMotor.Flags.EnPM = false;
            PistonMotor.Flags.PMCheck = false;
            PMDebounce_Counter = 0;
            PMErr_Counter = 0;
            Previous_Position = PistonMotor.Current_Position;
            PistonMotor.PMState_Status = PISTONMOTOR_STATE_IDLE;
        break;
        
        case PISTONMOTOR_STATE_ERROR : 
            PistonMotor.Flags.EnPM = false;
            PistonMotor.Flags.EditedSet = false;
            PistonMotor.Flags.EditedPM = false;
            PistonMotor_Stop();
            PistonMotor.Set_Position = 0.0f;
            if(Error_GetFlag() == false)
            {
                if(VALVE_POSITION_OUTLET == ValveMotor_GetPostion())
                {
                    PistonMotor.Flags.ErrorPM = false;
                    PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
                }
            }
        break;
        
        default : 
            PWM_GeneratorDisable(PWM_GENERATOR_1);              // turn off PWM generator
        break;
    }
}

/**
 * @brief This function is called from schedular with interval time
 *          This function controls the Piston motor movement upwards 
 * @param Nothing
 * @return Nothing
 */
void PistonMotor_Up(void)
{
    PWM_GeneratorDisable(PWM_GENERATOR_1);                              // turn on PWM generator
    PG1IOCONLbits.SWAP = false;                                         // PWMxH output will be connected to PWMxH output pin
    PWM_PeriodSet(PWM_GENERATOR_1, PM_Period);                 // Set Period (n = 6392 => 1 / (n * 10 us) = 10 kHz )
    PWM_DutyCycleSet(PWM_GENERATOR_1, PM_DutyCycle);          // Set Duty Cycle (n = 3196 => n / PGxPER = 50 %)
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, PM_DeadtimeLow);       // Set Falling Edge Dead Time (n = 05 => n * 10 us = 50 us)
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, PM_DeadtimeHigh);     // Set Rising Edge Dead Time (n = 10 => n * 10 us = 100 us)
    PISTONMTR_EN_SetHigh();
    PWM_GeneratorEnable(PWM_GENERATOR_1);                               // turn on PWM generator
}

/**
 * @brief This function is called from schedular with interval time
 *          This function controls the Piston motor movement downwards 
 * @param Nothing
 * @return Nothing
 */
void PistonMotor_Down(void)
{
    PWM_GeneratorDisable(PWM_GENERATOR_1);              // turn off PWM generator
    PG1IOCONLbits.SWAP = true;                          // PWMxH output will be connected to PWMxL output pin
    PWM_PeriodSet(PWM_GENERATOR_1, PM_Period);             // Set Period (n = 6392 => 1 / (n * 10 us) = 10 kHz )
    PWM_DutyCycleSet(PWM_GENERATOR_1, PM_DutyCycle);          // Set Duty Cycle (n = 3196 => n / PGxPER = 50 %)
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, PM_DeadtimeLow);          // Set Falling Edge Dead Time (n = 05 => n * 10 us = 50 us)
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, PM_DeadtimeHigh);         // Set Rising Edge Dead Time (n = 10 => n * 10 us = 100 us)
    PISTONMTR_EN_SetHigh();
    PWM_GeneratorEnable(PWM_GENERATOR_1);               // turn on PWM generator    
}

void PistonMotor_Stop(void)
{
    PistonMotor.Flags.EnPM = false;
    PISTONMTR_EN_SetLow();
    PWM_GeneratorDisable(PWM_GENERATOR_1);              // turn off PWM generator
    PistonEncoder_SetEnableFlag(false);
}

/**
 * @brief This function is called by som to move piston to desired position 
 * @param Nothing
 * @return Nothing
 */
void PistonMotor_UpdatePostion(bool flagSet, float fPosition)
{
    PistonMotor.Flags.EnPM = flagSet;
    PistonMotor.Flags.EditedSet = flagSet;
    PistonMotor.Set_Position = fPosition * CONVERSION_CONSTANT;
}

void PistonMotor_SetDutyCycle(void)
{
    PM_DutyCycle = PISTON_DYNAMIC_DUTY_CYCLE;
}

float PistonMotor_GetPostion(void)
{
//    return(PistonMotor.Set_Position);
    return ((PistonMotor.Current_Position)/CONVERSION_CONSTANT);
}

float PistonMotor_GetSetPostion(void)
{
    return((PistonMotor.Set_Position)/CONVERSION_CONSTANT);
//    return(PistonMotor.Current_Position);
}

bool PistonMotor_GetStatus(void)
{
//    return(PistonMotor.Flags.EnPM);
//    return(PistonMotor.Current_Position);
    return(POSITION_PISTON_GetValue());
}
void PistonMotor_CheckError(void)
{
    if(ADCRead_GetPistFb() > CURRENT_LIMIT_COUNT)
    {
        PistonMotor.Flags.ErrorPM = true;
    }
    else
    {
        PistonMotor.Flags.ErrorPM = false;
    }
}

/**
 * @brief This function indicates the piston bottom through on board LED
 * @param Nothing
 * @return Nothing
 */
void PistonMotor_HesLedStatus(void)
{
    if(POSITION_PISTON_GetValue() == false)
    {
        PISTON_HES_LED_SetLow();
    }
    else
    {
        PISTON_HES_LED_SetHigh();
    }
}

void PistonMotor_ChangedPosition(void)
{
    if((!(PistonEncoder_GetCountA() == 0)) && (PistonMotor.Flags.EnPM == false))
    {
        if(PistonEncoder_FirstEncoder() == 1)
        {
            PistonMotor.Flags.EnPM = true;
            PistonMotor_SetDutyCycle();
            PistonEncoder_ExpectedCount(true, (PistonEncoder_GetCountA()));
            PistonMotor_Up();
            PistonMotor.Flags.PMStatus = true;
        }
        else if(PistonEncoder_FirstEncoder() == 2)
        {
            PistonMotor.Flags.EnPM = true;
            PistonMotor_SetDutyCycle();
            PistonEncoder_ExpectedCount(false, (PistonEncoder_GetCountA()));
            PistonMotor_Down();
            PistonMotor.Flags.PMStatus = false;
        }
    }
}

void PistonMotor_RunningState(void){
    if(ReturnPistonMotor_StopFlag() && !(PistonMotor_InitialiseToZero()))
    {
        if(!PistonMotor_UpOrDown())
        {
            if(PistonMotor.Set_Position == 0.0f)
            {
                if(POSITION_PISTON_GetValue() == false)
                {
                    A_Pulses = PistonEncoder_GetCountA();
                    PistonMotor_Stop();
                    PistonEncoder_StopRead();
                    PistonMotor.Flags.EnPM = false;
                    for(int i=0;i<10;i++){
                        A++;
                    }
                    A = 0;
                    SetPistonMotor_StopFlag(false);
                    PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
                    PistonMotor.Current_Position = PistonMotor.Set_Position;
//                    PistonEncoder_StopRead();
                }
            }
            else
            {
                A_Pulses = PistonEncoder_GetCountA();
                PistonMotor_Stop();
                PistonEncoder_StopRead();
                PistonMotor.Flags.EnPM = false;
                for(int i=0;i<10;i++){
                    A++;
                }
                A = 0;
                SetPistonMotor_StopFlag(false);
                PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
                PistonMotor.Current_Position = PistonMotor.Set_Position;
//                PistonEncoder_StopRead();
            }
        }
        else
        {
            A_Pulses = PistonEncoder_GetCountA();
            PistonMotor_Stop();
            PistonEncoder_StopRead();
            PistonMotor.Flags.EnPM = false;
            for(int i=0;i<10;i++){
                A++;
            }
            A = 0;
            SetPistonMotor_StopFlag(false);
            PistonMotor.PMState_Status = PISTONMOTOR_STATE_STOP;
            PistonMotor.Current_Position = PistonMotor.Set_Position;
//            PistonEncoder_StopRead();
        }
    }

}