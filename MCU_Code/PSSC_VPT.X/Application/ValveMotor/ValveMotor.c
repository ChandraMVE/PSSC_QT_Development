/**
 ******************************************************************************
 * @file       Valve Motor Control.c
 * @author     Dnyaneshwar 
 * @date       30 Dec 2020
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
File name:    ValveMotor.c
                    
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
       23-12-2019  Initial Write                        Dnyaneshwar Pawar
--------------------------------------------------------------------------------
*/

#include "xc.h"
#include <stdbool.h>
#include "TECControl.h"
#include "ValveMotor.h"
#include "../mcc_generated_files/pwm.h"
#include "mcc_generated_files/pin_manager.h"
#include "Error.h"
#include "Alarm.h"
#include "TemperatureControl.h"

//VALVEMOTOR_STYP ValveMotor = VALVEMOTOR_DEFAULTS;

static uint16_t VM_Period;
static uint16_t VM_DutyCycle;
static uint16_t VM_DeadtimeLow;
static uint16_t VM_DeadtimeHigh;
static uint16_t Debounce_Counter;
static uint16_t PowerOn_Counter;
static uint16_t Position_DebounceCounter;

/**
 * @brief This method Initialises the Valve motor variables
 * @param Nothing
 * @return Nothing
 */
void ValveMotor_Initialise(void)
{
    
    VALVEMTR_EN_SetDigitalOutput();
    VALVE_POS1_SetDigitalInput();
    VALVE_POS2_SetDigitalInput();

    PWM_GeneratorDisable(PWM_GENERATOR_3);
    ValveMotor.VMState_Status = VALVEMOTOR_STATE_INITIAL;
    VM_Period = VALVE_DUTY_PERIOD;
    VM_DutyCycle = VALVE_DEFAULT_DUTY_CYCLE;
    VM_DeadtimeLow = 0X05;
    VM_DeadtimeHigh = 0X0A;
    ValveMotor.Current_Position = VALVE_POSITION_UNID;
    ValveMotor.Set_Position = VALVE_POSITION_UNID;
    ValveMotor.Flags.VMCheck = false;
    ValveMotor.Flags.VMError = false;
    Debounce_Counter = 0;
    PowerOn_Counter = 0;
    Position_DebounceCounter = 0;
    
}
        
/**
 * @brief This function is called from schedular with interval time
 *          This function controls the valve motor movement 
 * @param Nothing
 * @return Nothing
 */
void ValveMotor_Handler(void)
{
//    ValveMotor.Current_Position = ValveMotor_CheckPostion();
    ValveMotor_CheckPostion();
    
    switch(ValveMotor.VMState_Status)
    {
        // after power on if motor is not at outlet position move motor to outlet position
        case VALVEMOTOR_STATE_INITIAL:
            PowerOn_Counter++;
            if(PowerOn_Counter >= MAX_VALVE_COUNT)
            {
                PowerOn_Counter = MAX_VALVE_COUNT;
                if((ValveMotor.Current_Position == VALVE_POSITION_OUTLET))/* &&       \
                        (ValveMotor.Flags.VMError == false) && (ValveMotor.Flags.VMCheck == false))*/
                {
                    Position_DebounceCounter = 0;
                    ValveMotor.Flags.VMCheck = false;
                    ValveMotor_Stop();
                    if(Error_GetFlag() == false)
                    {
                        ValveMotor.VMState_Status = VALVEMOTOR_STATE_IDLE;
                    }
                }
                else if((ValveMotor.Current_Position != VALVE_POSITION_OUTLET) &&            \
                        (Error_GetFlag() == false) && (ValveMotor.Flags.VMCheck == false))
                {
                    if(ValveMotor.Set_Position == VALVE_POSITION_OUTLET)
                    {
                        Position_DebounceCounter = 0;
                        ValveMotor.Flags.VMCheck = true;
                        ValveMotor_AntiClockwise();
                        ValveMotor.Flags.VMStatus = false;   
                    }
                }
                else if((ValveMotor.Current_Position != VALVE_POSITION_OUTLET) &&            \
                        (Error_GetFlag() == false) && (ValveMotor.Flags.VMCheck == true))
                {
                    Position_DebounceCounter++;
                    if(Position_DebounceCounter >= MAX_POSITION_DETECTION_TIME)
                    {
                        Position_DebounceCounter = 0;
                        ValveMotor_Stop();
                        if(Error_GetCycleRunSts() == true)
                        {
                            ValveMotor.Flags.VMError = true;
                            Error_Report(VALVE_MOTOR);
                            Alarm_UpdateError(ValveMotor.Flags.VMError);
                            ValveMotor.VMState_Status = VALVEMOTOR_STATE_ERROR;
                        }
                        else
                        {
                            ValveMotor.VMState_Status = VALVEMOTOR_STATE_IDLE;
                        }
                    }   
                }
                //Error flag is true by some error, stop the motor
                else
                {
                    Position_DebounceCounter = 0;
                    if((Error_GetFlag() == true) && (TemperatureControl_GetTempADC() < VM_MIN_TEMP_COUNT_MOTOR)    \
                            && (ValveMotor.Current_Position != VALVE_POSITION_OUTLET))
                    {
                        if(Error_PressureOverLoadVariable() == true){
                            
                        }else{
                            ValveMotor_AntiClockwise();
                            ValveMotor.Flags.VMStatus = false;
                        }
                    }
                    else
                    {
                        ValveMotor_Stop();
                    }

                }
            }
            
        break;
        case VALVEMOTOR_STATE_IDLE : 
            if((ValveMotor.Flags.VMEn == true) &&                                   \
                    (ValveMotor.Set_Position != ValveMotor.Current_Position) &&     \
                    (ValveMotor.Flags.VMError == false))
            {
                if(ValveMotor.Set_Position == VALVE_POSITION_INLET)
                {
                    ValveMotor_AntiClockwise();
                    ValveMotor.Flags.VMStatus = false;
                }
                else if(ValveMotor.Set_Position == VALVE_POSITION_OFF)
                {
                    if(ValveMotor.Current_Position == VALVE_POSITION_INLET)
                    {
                        ValveMotor_Clockwise();
                        ValveMotor.Flags.VMStatus = true;
                    }
                    else if(ValveMotor.Current_Position == VALVE_POSITION_OUTLET)
                    {
                        ValveMotor_AntiClockwise();
                        ValveMotor.Flags.VMStatus = false;
                    }
                }
                else if(ValveMotor.Set_Position == VALVE_POSITION_OUTLET)
                {
                    ValveMotor_Clockwise();
                    ValveMotor.Flags.VMStatus = true;
                }
                else
                {
                    ValveMotor.Flags.VMEn = false;
                }
                Position_DebounceCounter = 0;
                ValveMotor.Flags.VMCheck = false;
                ValveMotor.Flags.VMEdited = true;
                ValveMotor.VMState_Status = VALVEMOTOR_STATE_RUNNING;
            }
            if((ValveMotor.Current_Position == VALVE_POSITION_UNID) &&                              \
                (ValveMotor.Flags.VMCheck == false) && (ValveMotor.Flags.VMEdited == false) &&      \
                (ValveMotor.Flags.VMError == false))
            {
                ValveMotor.Flags.VMEdited = true;
                ValveMotor.Flags.VMCheck = true;
                ValveMotor_AntiClockwise();
                ValveMotor.Flags.VMStatus = false; 
                Position_DebounceCounter = 0;
            }
            // Stop motor if any valid position is detected
            else if(((ValveMotor.Current_Position == VALVE_POSITION_OUTLET) ||  \
                    (ValveMotor.Current_Position == VALVE_POSITION_INLET) ||   \
                    (ValveMotor.Current_Position == VALVE_POSITION_OFF)) &&  \
                (ValveMotor.Flags.VMCheck == true) && (ValveMotor.Flags.VMEdited == true)   \
                    && (ValveMotor.Flags.VMEn == false))
            {
                ValveMotor.Flags.VMEdited = false;
                ValveMotor_Stop();
            }
//            else
//            {
//                Position_DebounceCounter++;
//                if(Position_DebounceCounter >= MAX_POSITION_DETECTION_TIME)
//                {
//                    Position_DebounceCounter = 0;
//                    ValveMotor_Stop();
//                    if(Error_GetCycleRunSts() == true)
//                    {
//                        ValveMotor.Flags.VMError = true;
//                        Error_Report(VALVE_MOTOR);
//                        Alarm_UpdateError(ValveMotor.Flags.VMError);
//                        ValveMotor.VMState_Status = VALVEMOTOR_STATE_ERROR;
//                    }
//                }
//            }
            if(Error_GetFlag() == true)
            {
                if(Error_PressureOverLoadVariable() == true){
//                    if(Error_PressurePistonVariable() == true){
//                        ValveMotor_UpdatePostion(true, VALVE_POSITION_OUTLET);
//                    }
                }else{
                    ValveMotor_Stop();
                    ValveMotor.VMState_Status = VALVEMOTOR_STATE_ERROR;
                }
            }
        break;
        
        case VALVEMOTOR_STATE_RUNNING : 
            if(ValveMotor.Flags.VMEn)
            {
                if(ValveMotor.Set_Position == ValveMotor.Current_Position)
                {
                    ValveMotor.Flags.VMEdited = false;
                    ValveMotor.Flags.VMCheck = true;
                    ValveMotor_Stop();
                    ValveMotor.VMState_Status = VALVEMOTOR_STATE_STOP;
                }
            }
            else
            {
                ValveMotor.VMState_Status = VALVEMOTOR_STATE_STOP;
            }
//            if(ValveMotor.Current_Position == VALVE_POSITION_UNID)
//            {
            //If Cycle is running @GUI then only enable the error logging
            
            Position_DebounceCounter++;
            if(Position_DebounceCounter >= MAX_POSITION_DETECTION_TIME)
            {
                Position_DebounceCounter = 0;
                ValveMotor_Stop();
                if(Error_GetCycleRunSts() == true)
                {
                    ValveMotor.Flags.VMError = true;
                    Error_Report(VALVE_SWITCH);
                    Alarm_UpdateError(ValveMotor.Flags.VMError);
                    ValveMotor.VMState_Status = VALVEMOTOR_STATE_ERROR;
                }
                else
                {
                    ValveMotor.VMState_Status = VALVEMOTOR_STATE_STOP;
                }
            }
//            }
            if(Error_GetFlag() == true)
            {
                if(Error_PressureOverLoadVariable() == true){
                    
                }else{
                    ValveMotor_Stop();
                    ValveMotor.VMState_Status = VALVEMOTOR_STATE_ERROR;
                }
            }
        break;
        
        case VALVEMOTOR_STATE_STOP : 
            if(ValveMotor.Current_Position == VALVE_POSITION_UNID)
            {
                ValveMotor.Flags.VMCheck = false;
            }
            ValveMotor.Flags.VMEn = false;
            ValveMotor_Stop();
            ValveMotor.VMState_Status = VALVEMOTOR_STATE_IDLE;
        break;
        
        case VALVEMOTOR_STATE_ERROR : 
            ValveMotor.Flags.VMEn = false;
            ValveMotor.Flags.VMEdited = false;
            ValveMotor_Stop();
            Position_DebounceCounter = 0;
            ValveMotor.Set_Position = VALVE_POSITION_OUTLET;
            ValveMotor.Flags.VMError = false;
            if(Error_GetCycleRunSts() == false)
            {
                if(Error_GetFlag() == false)
                {
                    ValveMotor.Flags.VMError = false;
                    ValveMotor.VMState_Status = VALVEMOTOR_STATE_INITIAL;
                }
                else if(ValveMotor.Flags.VMError == false)
                {
                    ValveMotor.VMState_Status = VALVEMOTOR_STATE_INITIAL;
                }
                ValveMotor.Flags.VMCheck = false;
            }
            else
            {
                if((Error_GetFlag() == false))
                {
                    ValveMotor.VMState_Status = VALVEMOTOR_STATE_IDLE;
                }
                ValveMotor.Flags.VMCheck = true;
            }
        break;
        
        default : 
            PWM_GeneratorDisable(PWM_GENERATOR_3);                      // turn off PWM generator
        break;
    }
}

/**
 * @brief This function sets pwm to move motor in clockwise direction 
 * @param Nothing
 * @return Nothing
 */
void ValveMotor_Clockwise(void)
{
    PWM_GeneratorDisable(PWM_GENERATOR_3);                              // turn on PWM generator
    PG3IOCONLbits.SWAP = false;                                         // PWMxH output will be connected to PWMxH output pin
    PWM_PeriodSet(PWM_GENERATOR_3, VM_Period);                          // Set Period (n = 6392 => 1 / (n * 10 us) = 10 kHz )
    PWM_DutyCycleSet(PWM_GENERATOR_3, VM_DutyCycle);                    // Set Duty Cycle (n = 3196 => n / PGxPER = 50 %)
    PWM_DeadTimeLowSet(PWM_GENERATOR_3, VM_DeadtimeLow);                // Set Falling Edge Dead Time (n = 05 => n * 10 us = 50 us)
    PWM_DeadTimeHighSet(PWM_GENERATOR_3, VM_DeadtimeHigh);              // Set Rising Edge Dead Time (n = 10 => n * 10 us = 100 us)
    VALVEMTR_EN_SetHigh();
    PWM_GeneratorEnable(PWM_GENERATOR_3);                               // turn on PWM generator
}

/**
 * @brief This function sets pwm to move motor in anti-clockwise direction 
 * @param Nothing
 * @return Nothing
 */
void ValveMotor_AntiClockwise(void)
{
    //Previously we were rotating valve motor in both the directions
    //but now Todd suggested to rotate in single direction
    /*PWM_GeneratorDisable(PWM_GENERATOR_3);                              // turn off PWM generator
    PG3IOCONLbits.SWAP = false;                                         // PWMxH output will be connected to PWMxH output pin
    PWM_PeriodSet(PWM_GENERATOR_3, VM_Period);                          // Set Period (n = 6392 => 1 / (n * 10 us) = 10 kHz )
    PWM_DutyCycleSet(PWM_GENERATOR_3, VM_DutyCycle);                    // Set Duty Cycle (n = 3196 => n / PGxPER = 50 %)
    PWM_DeadTimeLowSet(PWM_GENERATOR_3, VM_DeadtimeLow);                // Set Falling Edge Dead Time (n = 05 => n * 10 us = 50 us)
    PWM_DeadTimeHighSet(PWM_GENERATOR_3, VM_DeadtimeHigh);              // Set Rising Edge Dead Time (n = 10 => n * 10 us = 100 us)
    VALVEMTR_EN_SetHigh();
    PWM_GeneratorEnable(PWM_GENERATOR_3);*/                               // turn on PWM generator
    
    //previously motor used to rotate in both direction and below code is for anticlock wise direction
    // above is exact replica of clockwise as client wants to make motor bi-idirectional
    PWM_GeneratorDisable(PWM_GENERATOR_3);                              // turn off PWM generator
    PG3IOCONLbits.SWAP = true;                                          // PWMxH output will be connected to PWMxL output pin
    PWM_PeriodSet(PWM_GENERATOR_3, VM_Period);                  // Set Period (n = 6392 => 1 / (n * 10 us) = 10 kHz )
    PWM_DutyCycleSet(PWM_GENERATOR_3, VM_DutyCycle);           // Set Duty Cycle (n = 3196 => n / PGxPER = 50 %)
    PWM_DeadTimeLowSet(PWM_GENERATOR_3, VM_DeadtimeLow);       // Set Falling Edge Dead Time (n = 05 => n * 10 us = 50 us)
    PWM_DeadTimeHighSet(PWM_GENERATOR_3, VM_DeadtimeHigh);     // Set Rising Edge Dead Time (n = 10 => n * 10 us = 100 us)
    VALVEMTR_EN_SetHigh();
    PWM_GeneratorEnable(PWM_GENERATOR_3);                               // turn on PWM generator    
}

/**
 * @brief This function is called by som to set the valve motor position 
 * @param Nothing
 * @return Nothing
 */
void ValveMotor_UpdatePostion(bool flagSet, uint8_t bPosition)
{
    ValveMotor.Flags.VMEn = flagSet;
    
    switch(bPosition)
    {
        case VALVE_POSITION_OFF :
            ValveMotor.Set_Position = VALVE_POSITION_OFF;
        break;

        case VALVE_POSITION_INLET :
            ValveMotor.Set_Position = VALVE_POSITION_INLET;
        break;

        case VALVE_POSITION_OUTLET :
            ValveMotor.Set_Position = VALVE_POSITION_OUTLET;
        break;

        default : 
            ValveMotor.Set_Position = VALVE_POSITION_OUTLET;
        break;
    }
}

/**
 * @brief This function is called to check the limit switch status of the valve motor
 * @param Nothing
 * @return Nothing
 */
void ValveMotor_CheckPostion(void)
{
    ValveMotorPosition_ETYP tempPosition;
#if (VM_BOARD_VERSION == ALPHA_VERSION)
    if((VALVE_POS1_GetValue() == true) && (VALVE_POS2_GetValue() == true))
    {
        tempPosition = VALVE_POSITION_OFF;
    }
    else if((VALVE_POS1_GetValue() == true) && (VALVE_POS2_GetValue() == false))
    {
        tempPosition = VALVE_POSITION_OUTLET;
    }
    else if((VALVE_POS1_GetValue() == false) && (VALVE_POS2_GetValue() == true))
    {
        tempPosition = VALVE_POSITION_INLET;
    }
    else if((VALVE_POS1_GetValue() == false) && (VALVE_POS2_GetValue() == false))
    {
        tempPosition = VALVE_POSITION_UNID;
    }
#else 
    if((VALVE_POS3_GetValue() == true) && (VALVE_POS2_GetValue() == true))
    {
        tempPosition = VALVE_POSITION_OFF;
    }
    else if((VALVE_POS3_GetValue() == true) && (VALVE_POS2_GetValue() == false))
    {
        tempPosition = VALVE_POSITION_OUTLET;
    }
    else if((VALVE_POS3_GetValue() == false) && (VALVE_POS2_GetValue() == true))
    {
        tempPosition = VALVE_POSITION_INLET;
    }
    else if((VALVE_POS3_GetValue() == false) && (VALVE_POS2_GetValue() == false))
    {
        tempPosition = VALVE_POSITION_UNID;
    }
#endif    
    
    if(ValveMotor.Current_Position != tempPosition)
    {
        Debounce_Counter++;
        if(Debounce_Counter >= MAX_VALVE_COUNT)
        {
            Debounce_Counter = 0;
            ValveMotor.Current_Position = tempPosition;
        }
    }
    else
    {
        Debounce_Counter = 0;
    }
    
}

uint8_t ValveMotor_GetPostion(void)
{
    return(ValveMotor.Current_Position);
}

uint8_t ValveMotor_GetSetPostion(void)
{
    return(ValveMotor.Set_Position);
}

bool ValveMotor_GetStatus(void)
{
    return(ValveMotor.Flags.VMEn);
}

uint8_t ValveMotor_GetState(void)
{
    return(ValveMotor.VMState_Status);
}

void ValveMotor_Stop(void)
{
    ValveMotor.Flags.VMEn = false;
//    SHAKERMTR_EN_SetLow();
    PWM_GeneratorDisable(PWM_GENERATOR_3);              // turn off PWM generator
}