/**
 ******************************************************************************
 * @file       Piston Encoder Reading
 * @author     Dnyaneshwar 
 * @date       22 Jan 2021
 * @brief      This is a source file containing Input Capture Interrupt to read
 *             Piston Motor movement for PSSC VPT 
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
File name:    PistonEncoder.c
                    
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
       22-01-2021  Initial Write                        Dnyaneshwar Pawar
--------------------------------------------------------------------------------
*/

#include "xc.h"
#include <stdbool.h>
#include "PistonEncoder.h"
#include "../mcc_generated_files/sccp3_capture.h"
#include "../mcc_generated_files/sccp4_capture.h"
#include "mcc_generated_files/pin_manager.h"
#include "PistonMotor.h"
#include "Error.h"
#include "Alarm.h"

//PISTONMOTOR_STYP PistonMotor = PISTONMOTOR_DEFAULTS;

static uint16_t Debounce_Counter;
static uint16_t Pulses_Counter;

static uint32_t Pulse_CountA;
static uint32_t Pulse_CountB;

uint32_t firstEncoder = 0;
uint32_t Encoder_Count = 0;
bool PistonMotor_StopFlag = 0;
bool PistonMotorUp = false;
bool PistonMotorDown = false;
bool ZeroPosition = false;
/**
 * @brief This method Initializes the Encoder Parameters
 * @param dutyCycle
 * @return Nothing
 */
void PistonEncoder_Initialise(void)
{
    Pulse_CountA = 0;
    Pulse_CountB = 0;
    Debounce_Counter = 0;
    Pulses_Counter = 0;
    
    POSITION_PISTON_SetDigitalInput();  
}
 
/**
 * @brief This function is called from schedular with interval time
 *          This function reads the encoder pulses in interrupt 
 * @param Nothing
 * @return Nothing
 */
void PistonEncoder_Handler(void)
{
    switch(PistonEncoder.PEState_Status)
    {
        case PISTONENCODER_STATE_IDLE :
            PistonEncoder_CheckInitialPosition();
            if((PistonEncoder.Flags.EnPE == true) && (PistonEncoder.Flags.ErrorPE == false))
            {
                PistonEncoder_StartRead();
                Pulse_CountA = 0;
                Pulse_CountB = 0;
                Pulses_Counter = 0;
                PistonEncoder.PEState_Status = PISTONENCODER_STATE_RUNNING;
            }
        break;
        
        case PISTONENCODER_STATE_RUNNING : 
            if(PistonEncoder.Flags.EnPE == false)
            {
//                PistonEncoder_StopRead();
                PistonEncoder.PEState_Status = PISTONENCODER_STATE_STOP;
            }
            if(PistonEncoder.Flags.EnPE == true)
            {
//                if((Pulse_CountA < MIN_ENCODER_PULSES) || (Pulse_CountB < MIN_ENCODER_PULSES))
//                {
//                    Pulses_Counter++;
//                    if(Pulses_Counter >= MAX_PULSE_TIME)
//                    {
//                        Pulses_Counter = 0;
//                        PistonEncoder_StopRead();
//                        PistonEncoder.Flags.ErrorPE = true;
//                        PistonEncoder.PEState_Status = PISTONENCODER_STATE_ERROR;
//                        Error_Report(PISTON_ENCODER);
//                        Alarm_UpdateError(PistonEncoder.Flags.ErrorPE);
//                    }
//                }
            }
            if((Pulse_CountA < MIN_ENCODER_PULSES) || (Pulse_CountB < MIN_ENCODER_PULSES))
            {
                if(Error_GetCycleRunSts() == true)
                {
                    Pulses_Counter++;
                    if(Pulses_Counter >= MAX_PULSE_TIME)
                    {
                        Pulses_Counter = 0;
//                        PistonEncoder_StopRead();
                        PistonEncoder.Flags.ErrorPE = true;
                        PistonEncoder.PEState_Status = PISTONENCODER_STATE_ERROR;
                        Error_Report(PISTON_ENCODER);
                        Alarm_UpdateError(PistonEncoder.Flags.ErrorPE);
                    }
                }
            }
            
            if(Error_GetFlag() == true)
            {
//                PistonEncoder_StopRead();
                PistonEncoder.PEState_Status = PISTONENCODER_STATE_ERROR;
            }
        break;
        
        case PISTONENCODER_STATE_STOP : 
//                PistonEncoder_StopRead();
                PistonEncoder.Flags.EnPE = 0;
                PistonEncoder.PEState_Status = PISTONENCODER_STATE_IDLE;
        break;
        
        case PISTONENCODER_STATE_ERROR : 
//            PistonEncoder_StopRead();
            if(Error_GetFlag() == false)
            {
                PistonEncoder.Flags.ErrorPE = false;
                PistonEncoder.PEState_Status = PISTONENCODER_STATE_STOP;
            }
        break;
        
        default : 
            PistonEncoder.PEState_Status = PISTONENCODER_STATE_IDLE;
        break;
    }
}

/*
================================================================================
Method name:  Start Reading Encoder Pulses Function

 * @brief   This function is used to start reading the input capture pulses.
 * @param None 
 * @param 
 * @return None

================================================================================
*/

void PistonEncoder_StartRead(void)
{
  // SCCP to start the read
    SCCP3_CAPTURE_Start();
    SCCP4_CAPTURE_Start();
//    LED_3_SetLow();
}

/**
 * @brief   This function is used to stop reading the input capture pulses.
 * @param None 
 * @param 
 * @return None
 */

void PistonEncoder_StopRead(void)
{
  // SCCP to stop the read
//    LED_3_SetHigh();
    SCCP3_CAPTURE_Stop();
    SCCP4_CAPTURE_Stop();
}

/*
================================================================================
Method name:  Input Capture ISR Function

Description: 
  To handle the Edge interrupt of encoder Pulses. In this interrupt service
  routine it will make counter increment.


================================================================================

*/

void PistonEncoder_ISRFunctionA(void)
{
  // Set the interrupt flag to execute the scheduler
//    Pulse_CountA ++;
    Pulse_CountA ++;
    if(firstEncoder == 0)
    {
        firstEncoder = 1;
    }
    if(PistonMotorUp && Encoder_Count<=Pulse_CountA){
        PistonMotor_StopFlag = 1;
    }
    else if(PistonMotorDown && Encoder_Count<=Pulse_CountA)
    {
        if(ZeroPosition){
            if(POSITION_PISTON_GetValue() == false){
                PistonMotor_StopFlag = 1;
            }
        }
        else 
        {
            PistonMotor_StopFlag = 1;
        }
    }
  
}

void PistonEncoder_ISRFunctionB(void)
{
  // Set the interrupt flag to execute the scheduler
//        Pulse_CountB ++;
        Pulse_CountA ++;
        if(firstEncoder == 0)
        {
            firstEncoder = 2;
        }
        if(PistonMotorUp && Encoder_Count<=Pulse_CountA){
            PistonMotor_StopFlag = 1;
        }
        else if(PistonMotorDown && Encoder_Count<=Pulse_CountA)
        {
            if(ZeroPosition){
                if(POSITION_PISTON_GetValue() == false){
                    PistonMotor_StopFlag = 1;
                }
            }
            else 
            {
                PistonMotor_StopFlag = 1;
            }
        }
//    }
  
}

bool ReturnPistonMotor_StopFlag(void)
{
    return PistonMotor_StopFlag;
}

void SetPistonMotor_StopFlag(bool flagSet)
{
    PistonMotor_StopFlag = flagSet;
    PistonMotorUp = false;
    PistonMotorDown = false;
    Pulse_CountA = 0;
    firstEncoder = 0;
    PistonEncoder_StartRead();
}

bool PistonMotor_InitialiseToZero()
{
    return ZeroPosition;
}

void PistonMotor_SetInitialisedToZero(bool zeroPositionFlag)
{
    ZeroPosition = zeroPositionFlag;
}
/*
================================================================================
Method name:  Send Pulse value Function

Description: 
  To send the Edge interrupt of encoder Pulses. In this function the number of
  pulses will be returned.


================================================================================

*/

void PistonEncoder_ExpectedCount(bool directionFlag,uint32_t count)
{
    if(count > 35023)
    {
        PistonMotor_StopFlag = 1;
    }
    else
    {
        Encoder_Count = count;
    }
    if(directionFlag)
    {
        PistonMotorUp = true;
        PistonMotorDown = false;
    }
    else
    {
        PistonMotorDown = true;
        PistonMotorUp = false;
    }
}

uint32_t PistonEncoder_GetCountA(void)
{
  // return the Encoder A pulses count
    return(Pulse_CountA); 
}

void PistonEncoder_SetCountA(void){
    Pulse_CountA = 0;
}

bool PistonMotor_UpOrDown(void)
{
    if(PistonMotorUp)
    {
        return true;
    }
    else
    {
        return false;
    }
}

uint32_t PistonEncoder_GetCountB(void)
{
  // return the Encoder A pulses count
    return(Pulse_CountB);
  
}

void PistonEncoder_ClearCountFirstCount(void)
{
    firstEncoder = 0;
}

int PistonEncoder_FirstEncoder(void)
{
    return firstEncoder;
}

/**
 * @brief This function not used but created for future use in pistion encoder for initializing condition 
 * @param Nothing
 * @return Nothing
 */
void PistonEncoder_CheckInitialPosition(void)
{
    if(POSITION_PISTON_GetValue() == true)
    {
        if(PistonMotor_GetSetPostion() != 0.0f)
        {
            Debounce_Counter++;
            if(Debounce_Counter > MAX_INITIAL_PERIOD)
            {
                Debounce_Counter = 0;
//                PistonEncoder.Flags.InitialPosition = false;
//                PistonEncoder.Flags.ErrorPE = true;
//                PistonEncoder.PEState_Status = PISTONENCODER_STATE_ERROR;
//                Error_Report(PISTON_ENCODER);
//                Alarm_UpdateError(PistonEncoder.Flags.ErrorPE);
            }            
        }
    }
    else
    {
        Debounce_Counter = 0;
        PistonEncoder.Flags.InitialPosition = true;
    }
}

bool PistonEncoder_GetInitialPosition(void)
{
    return(PistonEncoder.Flags.InitialPosition);
}

void PistonEncoder_SetEnableFlag(bool flagSet)
{
    PistonEncoder.Flags.EnPE = flagSet;
}

bool PistonEncoder_GetEnableFlag(void)
{
    return(PistonEncoder.Flags.EnPE);
}

void PistonEncoder_SetErrorFlag(bool flagSet)
{
    PistonEncoder.Flags.ErrorPE = flagSet;
}

bool PistonEncoder_GetErrorFlag(void)
{
    return(PistonEncoder.Flags.ErrorPE);
}

uint16_t PistonEncoder_GetCounter(void)
{
    return(Pulses_Counter);
}