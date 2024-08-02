/**
 ******************************************************************************
 * @file       TEC Control.c
 * @author     Dnyaneshwar 
 * @date       04 Jan 2021
 * @brief      This is a source file containing PWM to control TEC Module for 
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
File name:    TECControl.c
                    
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
#include "../mcc_generated_files/pwm.h"
#include "mcc_generated_files/pin_manager.h"
#include "TemperatureControl.h"
#include "ADCRead.h"
#include "Error.h"
#include "Events.h"
#include "Alarm.h"


static uint16_t TEC_Period;
static uint16_t TEC_DutyCycle;
static uint16_t TEC_DeadtimeLow;
static uint16_t TEC_DeadtimeHigh;
static uint16_t TEC_OverCounter;
static int32_t DiffVal;
static uint32_t Temp_DefaultVal;
static uint8_t TEC_ErrDebounce;
static uint16_t TECCounter;
bool TempUpdated = false;

static float fPower = 0.0f;

static PIDCONTROL_STYP PidControl;
/**
 * @brief This method Initialises the TEC control variables
 * @param Nothing
 * @return Nothing
 */
void TECControl_Initialise(void)
{

    PWM_GeneratorDisable(PWM_GENERATOR_6);
    TECControl.TECState_Status = TEC_STATE_IDLE;
    TEC_Period = TECCONTROL_DUTY_PERIOD;
    TEC_DutyCycle = TECCONTROL_DEFAULT_DUTY_CYCLE;
    TEC_DeadtimeLow = 0X05;
    TEC_DeadtimeHigh = 0X0A;
    TEC_OverCounter = 0;
    TECControl.TempCurrent_Value = 0;
    TECControl.AmbTemp_Value = 0;
    DiffVal = 0;
    Temp_DefaultVal = 0;
    TECControl.Set_Value = DEAFULT_TEMP_COUNT20;       // 20 degree default adc count (914.268*51.2)(ADC I/P voltage * (262144/5120))
    TECControl.Flags.TECDisable = true;
    PIDControl_Initialise();
}
  
/**
 * @brief This function is called from schedular with interval time
 *          This function controls the TEC module and sets PID parameters
 * @param Nothing
 * @return Nothing
 */
void TECControl_Handler(void)
{
#if (TEC_PID_DIFF == ENABLE)
    TECControl.TempCurrent_Value = TemperatureControl_GetTempADC() - DiffVal;
#else
    TECControl.TempCurrent_Value = TemperatureControl_GetTempADC();
#endif
    TECControl.PressCurrent_Value = TemperatureControl_GetPressADC();
    TECControl.AmbTemp_Value = ADCRead_GetAmbTemp();
    
    //If Cycle is running then only enable the error logging and no error present
    if((Error_GetFlag() == false) && (Error_GetCycleRunSts() == true))
    {
        if(TECControl.AmbTemp_Value > MAX_AMBIENT_TEMP_COUNT)
        {
            TEC_ErrDebounce++;
            if(TEC_ErrDebounce >= MAX_ERR_DEBOUNCE)
            {
                TEC_ErrDebounce = 0;
                TECControl.ErrorFlags.TECAmb = true;
                TECControl.TECState_Status = TEC_STATE_ERROR;
                TECControl_Stop();
                Error_Report(AMBIENT_LIMIT);
                Alarm_UpdateError(TECControl.ErrorFlags.TECAmb);
            }
        }
        if(TECControl.PressCurrent_Value > MAX_PRESS_LIMIT_COUNT)
        {
            TEC_ErrDebounce++;
            if(TEC_ErrDebounce >= MAX_ERR_DEBOUNCE)
            {
                TEC_ErrDebounce = 0;
                TECControl.ErrorFlags.TECPress = true;
                TECControl.TECState_Status = TEC_STATE_ERROR;
                TECControl_Stop();
                Error_Report(PRESSURE_LIMIT);
                Alarm_UpdateError(TECControl.ErrorFlags.TECPress);
            }
        }
        if(TECControl.TempCurrent_Value > MAX_TEMP_LIMIT_COUNT)
        {
            TEC_ErrDebounce++;
            if(TEC_ErrDebounce >= MAX_ERR_DEBOUNCE)
            {
                TEC_ErrDebounce = 0;
                TECControl.ErrorFlags.TECTemp = true;
                TECControl.TECState_Status = TEC_STATE_ERROR;
                TECControl_Stop();
                Error_Report(TEC_FAILURE);
                Alarm_UpdateError(TECControl.ErrorFlags.TECTemp);
            }
        }
    }
    
    switch(TECControl.TECState_Status)
    {
        case TEC_STATE_IDLE : 
            if(TECControl.Flags.TECEn == true)
            {
                TECControl.Flags.TECEdited = false;
                TEC_OverCounter = 0;
                TECControl.Flags.TECLowVal = false;
                
                //For temperature Control
                if(TECControl.Flags.TECControl == false)
                {
//                    TECControl.TECState_Status = TEC_TEMP_STATE_RUNNING;
                    //For heating the chamber
                    if(TECControl.Set_Value > HEAT_COOL_TEMP_COUNT)
                    {
                        if(TECControl.Set_Value > TECControl.TempCurrent_Value)
                        {
                            // range of temperature from 22 to 31
                            if(TECControl.Set_Value < CHECK_TEMP_SET_COUNT_AMB)
                            {
                                PidControl.Kp_Term = 0.55f;
                                PidControl.Ki_Term = 0.025f;
                                PidControl.Kd_Term = 14.5f;
                                TECControl.Flags.TECLowVal = true;
                            }
                            // range of temperature below 42
                            else if(TECControl.Set_Value < CHECK_TEMP_SET_COUNT40)
                            {
                                PidControl.Kp_Term =  2.445f;          //2.445f;beta    //1.945f;alpha
                                PidControl.Ki_Term =  0.070f;          //0.070f;        //0.055f;
                                PidControl.Kd_Term =  27.55f;          //28.55f;        //27.55f;
                                Events_SetTecFan(false);
                            }
                            // range of temperatuer below 62
                            else if(TECControl.Set_Value < CHECK_TEMP_SET_COUNT_HI)
                            {
                                PidControl.Kp_Term = 6.15f;
                                PidControl.Ki_Term = 0.175f;
                                PidControl.Kd_Term = 50.5f;
                                Events_SetTecFan(false);
                            }
                            // range of temperature below 82
                            else if(TECControl.Set_Value < CHECK_TEMP_SET_COUNT80)
                            {
                                PidControl.Kp_Term = 8.85f;
                                PidControl.Ki_Term = 0.345f;
                                PidControl.Kd_Term = 84.5f;
                                Events_SetTecFan(false);
//                                PidControl.Kp_Term = 10.85f;
//                                PidControl.Ki_Term = 0.325f;
//                                PidControl.Kd_Term = 125.5f;
                            }
                            // range of temperature below 92
                            else if(TECControl.Set_Value < CHECK_TEMP_SET_COUNT90)
                            {
                                PidControl.Kp_Term = 9.95f;
                                PidControl.Ki_Term = 0.445f;
                                PidControl.Kd_Term = 95.5f;
                                Events_SetTecFan(false);
//                                PidControl.Kp_Term = 9.75f;
//                                PidControl.Ki_Term = 0.415f;
//                                PidControl.Kd_Term = 85.5f;
                            }
                            else
                            {
                                PidControl.Kp_Term = 11.95f;
                                PidControl.Ki_Term = 0.465f;
                                PidControl.Kd_Term = 155.5f;
                                Events_SetTecFan(false);
                            }
//                            TEC_DutyCycle = 0X018F;
                            if(TempUpdated){
                                TempUpdated = false;
                                TEC_DutyCycle = 0X018F;
                            } else{
                                if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                                {
                                    TECCounter++;
                                    if(TECCounter >= 10){
                                        TEC_DutyCycle += 0X018F;
                                        TECCounter = 0;
//                                        PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
//                                        PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                                    }
                                }else{
                                    TEC_DutyCycle = TECCONTROL_halfDutyPeriod;
                                }
                            }
                            TECControl_Heating();
                            TECControl.Flags.TECStatus = true;
                            TECControl.TECState_Status = TEC_TEMP_STATE_RUNNING;
                        }
                        else
                        {
                            if(TempUpdated){
                                TempUpdated = false;
                                TEC_DutyCycle = 0X018F;
                            } else{
                                if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                                {
                                    TECCounter++;
                                    if(TECCounter >= 10){
                                        TEC_DutyCycle += 0X018F;
                                        TECCounter = 0;
//                                        PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
//                                        PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                                    }
                                }else{
                                    TEC_DutyCycle = TECCONTROL_halfDutyPeriod;
                                }
                            }
//                            TEC_DutyCycle = 0X018F; //0X0C7F;
                            TECControl_Cooling();
                        }
                    }
                    //For cooling the chamber
                    else if(TECControl.Set_Value < HEAT_COOL_TEMP_COUNT)
                    {
                        if(TECControl.Set_Value < TECControl.TempCurrent_Value)
                        {
                            // range above 17
                            if(TECControl.Set_Value > CHECK_TEMP_SET_COUNT_LO)
                            {
                                PidControl.Kp_Term = 12.85f;
                                PidControl.Ki_Term = 0.215f;
                                PidControl.Kd_Term = 80.5f;
                            }
                            // range below 17
                            else
                            {
                                PidControl.Kp_Term = 15.85f;
                                PidControl.Ki_Term = 0.345f;
                                PidControl.Kd_Term = 100.5f;
                            }
                            TEC_DutyCycle = 0X018F;
                            Events_SetTecFan(true);
                            if(TempUpdated){
                                TempUpdated = false;
                                TEC_DutyCycle = 0X018F;
                            } else{
                                if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                                {
                                    TECCounter++;
                                    if(TECCounter >= 10){
                                        TEC_DutyCycle += 0X018F;
                                        TECCounter = 0;
//                                        PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
//                                        PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                                    }
                                }else{
                                    TEC_DutyCycle = TECCONTROL_halfDutyPeriod;
                                }
                            }
                            TECControl_Cooling();
                            TECControl.Flags.TECStatus = false;
                            TECControl.TECState_Status = TEC_TEMP_STATE_RUNNING;
                        }
                        else
                        {
//                            TEC_DutyCycle = 0X0C7F;
                            if(TempUpdated){
                                TempUpdated = false;
                                TEC_DutyCycle = 0X018F;
                            } else{
                                if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                                {
                                    TECCounter++;
                                    if(TECCounter >= 10){
                                        TEC_DutyCycle += 0X018F;
                                        TECCounter = 0;
//                                        PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
//                                        PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                                    }
                                }else{
                                    TEC_DutyCycle = TECCONTROL_halfDutyPeriod;
                                }
                            }
                            TECControl_Heating();
                        }
                    }
                    else
                    {
                        TECControl.Flags.TECStatus = false;
                    }
                }
                //For pressure Control
                else
                {
                    TECControl.TECState_Status = TEC_PRESS_STATE_RUNNING;
                    
                    if(TECControl.Set_Value < CHECK_PRESS_SET_COUNT)
                    {
                        // range of temp below 40
                        if(TECControl.TempCurrent_Value < CHECK_TEMP_SET_COUNT40)
                        {
                            PidControl.Kp_Term = 3.75f;
                            PidControl.Ki_Term = 0.065f;
                            PidControl.Kd_Term = 4.25f;
                        }
                        // range of temp below 60
                        else if(TECControl.TempCurrent_Value < CHECK_TEMP_SET_COUNT_HI)
                        {
                            PidControl.Kp_Term = 6.25f;
                            PidControl.Ki_Term = 0.135f;
                            PidControl.Kd_Term = 25.25f;
                        }
                        // range of temp below 80
                        else if(TECControl.TempCurrent_Value < CHECK_TEMP_SET_COUNT80)
                        {
                            PidControl.Kp_Term = 3.75f;
                            PidControl.Ki_Term = 0.065f;
                            PidControl.Kd_Term = 4.25f;
                        }
                        else
                        {
                            PidControl.Kp_Term = 3.75f;
                            PidControl.Ki_Term = 0.065f;
                            PidControl.Kd_Term = 4.25f;
                        }
                    }
                    else
                    {
                        PidControl.Kp_Term = 6.25f;
                        PidControl.Ki_Term = 0.125f;
                        PidControl.Kd_Term = 15.5f;
                    }
                    TECControl_Heating();
                    TECControl.Flags.TECStatus = true;
                }
            }
            else
            {
                TECControl.Current_Value = TECControl.TempCurrent_Value;
            }
            
            if((TECControl.Set_Value > (TECControl.TempCurrent_Value + TEMP_TOLERENCE_COUNT)) &&        \
                    (TECControl.Flags.TECCheck == true) && (TECControl.Flags.TECEn == false) &&         \
                    (TECControl.Flags.TECStatus == true) && (TECControl.Flags.TECDisable == false))
            {
                TEC_DutyCycle = 0X018F;
            }
            else if((TECControl.Set_Value < (TECControl.TempCurrent_Value - TEMP_TOLERENCE_COUNT)) &&   \
                    (TECControl.Flags.TECCheck == true) && (TECControl.Flags.TECEn == false) &&         \
                    (TECControl.Flags.TECStatus == false) && (TECControl.Flags.TECDisable == false))
            {
//                TEC_DutyCycle = 0X0C7F;
                if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                {
                    TECCounter++;
                    if(TECCounter >= 10){
                        TEC_DutyCycle += 0X018F;
                        TECCounter = 0;
                        PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
                        PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                    }
                }else{
                    TEC_DutyCycle = TECCONTROL_halfDutyPeriod;
                }
            }
            else if ((TECControl.Flags.TECCheck == true) && (TECControl.Flags.TECEn == false) &&        \
                    (Error_GetFlag() == false))
            {
                TECControl.Flags.TECCheck = false;
                TECControl_Stop();
            }
            // idle condition piston block temp will be set to 20 degree
            if((TECControl.Flags.TECCheck == false) && (TECControl.Flags.TECDisable == false) \
                    && (TECControl.ErrorFlags.TECTemp == false) && (TECControl.Flags.TECEn == false))
            {
//                TEC_DutyCycle = 0X018F;
                if(TECControl.Set_Value > (TECControl.TempCurrent_Value + (MAX_TEMP_TOLERENCE_COUNT * 2)))
                {
                    TEC_DutyCycle = 0X018F;
                    TECControl_Heating();
                    TECControl.Flags.TECStatus = true;
                    TECControl.Flags.TECCheck = true;
//                    TECControl.Set_Value = 67250;
                }
                else if(TECControl.Set_Value < (TECControl.TempCurrent_Value - (MAX_TEMP_TOLERENCE_COUNT * 2)))
                {
                    TEC_DutyCycle = 0X018F; //0X0F9F;//0X18FF;
                    Events_SetTecFan(true);
                    TECControl_Cooling();
                    TECControl.Flags.TECStatus = false;
                    TECControl.Flags.TECCheck = true;
//                    TECControl.Set_Value = 67200;
                } 
            }
        break;
        
        case TEC_TEMP_STATE_RUNNING : 
            if(TECControl.Flags.TECEn == true)
            {
                if(TECControl.Flags.TECStatus == true)
                {
                    TECControl.Current_Value = TECControl.TempCurrent_Value;
                    if(TECControl.Flags.TECLowVal)
                    {
                        TEC_OverCounter++;
                        if((TECControl.Set_Value < TECControl.Current_Value) && (TEC_OverCounter > MAXOVER_TIME))
                        {
                            TEC_OverCounter = 0;
                            //TECControl_Stop();
//                            TEC_DutyCycle = 0X018F;
                            if(TempUpdated){
                                TempUpdated = false;
                                TEC_DutyCycle = 0X018F;
                            } else{
                                if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                                {
                                    TECCounter++;
                                    if(TECCounter >= 10){
                                        TEC_DutyCycle += 0X018F;
                                        TECCounter = 0;
//                                        PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
//                                        PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                                    }
                                }else{
                                    TEC_DutyCycle = TECCONTROL_halfDutyPeriod;
                                }
                            }
                            TECControl_Cooling();
                        }
                        else if((TECControl.Set_Value > TECControl.Current_Value) && (TEC_OverCounter > MAXOVER_TIME))
                        {
                            TEC_OverCounter = 0;
                            //TECControl_Stop();
                            if(TempUpdated){
                                TempUpdated = false;
                                TEC_DutyCycle = 0X018F;
                            } else{
                                if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                                {
                                    TECCounter++;
                                    if(TECCounter >= 10){
                                        TEC_DutyCycle += 0X018F;
                                        TECCounter = 0;
//                                        PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
//                                        PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                                    }
                                }else{
                                    TEC_DutyCycle = TECCONTROL_halfDutyPeriod;
                                }
                            }
                            TECControl_Heating();
                        }
                        
                        if(TECControl.Set_Value > TECControl.Current_Value)
                        {
                            if( TECControl.TempCurrent_Value > (TECControl.Set_Value - (MAX_TEMP_TOLERENCE_COUNT * 2)))
                            {
                                PIDControl_Calculation();
                            }else{
                                if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                                {
                                    TECCounter++;
                                    if(TECCounter >= 10){
                                        TEC_DutyCycle += 0X018F;
                                        TECCounter = 0;
                                        PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
                                        PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                                    }
                                }else{
                                    PIDControl_Calculation();
                                }
                            }
                        }
                    }
                    else
                    {
                        if( TECControl.TempCurrent_Value > (TECControl.Set_Value - (MAX_TEMP_TOLERENCE_COUNT * 2)))
                        {
                            PIDControl_Calculation();
                        }else{
                            if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                            {
                                TECCounter++;
                                if(TECCounter >= 10){
                                    TEC_DutyCycle += 0X018F;
                                    TECCounter = 0;
                                    PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
                                    PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                                }
                            }else{
                                PIDControl_Calculation();
                            }
                        }
                    }
                }
                else
                {
                    TECControl.Current_Value = TECControl.TempCurrent_Value;
                    if( TECControl.TempCurrent_Value < (TECControl.Set_Value + (MAX_TEMP_TOLERENCE_COUNT * 2)))
                    {
                        PIDControl_ReverseCalculation();
                    }else{
                        if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                        {
                            TECCounter++;
                            if(TECCounter >= 10){
                                TEC_DutyCycle += 0X018F;
                                TECCounter = 0;
                                PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
                                PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                            }
                        }else{
                            PIDControl_ReverseCalculation();
                        }
                    }
                }
            }
            else
            {
                TECControl_Stop();
                TECControl.TECState_Status = TEC_STATE_STOP;
            }
            if(TECControl.Flags.TECEdited)
            {
                TECControl_Stop();
                TECControl.TECState_Status = TEC_STATE_STOP; 
            }
            if(Error_GetFlag() == true)
            {
                TECControl.TECState_Status = TEC_STATE_ERROR;
                TECControl_Stop();
            }
        break;
        
        case TEC_PRESS_STATE_RUNNING : 
            if(TECControl.Flags.TECEn == true)
            {
                if(TECControl.Flags.TECStatus == true)
                {
                    TECControl.Current_Value = TECControl.PressCurrent_Value;
                    if(TECControl.TempCurrent_Value < CHECK_TEMP_SET_COUNT40)
                    {
                        PidControl.Kp_Term = 3.75f;
                        PidControl.Ki_Term = 0.065f;
                        PidControl.Kd_Term = 4.25f;
                    }
                    else if(TECControl.TempCurrent_Value < CHECK_TEMP_SET_COUNT_HI)
                    {
                        PidControl.Kp_Term = 13.45f;
                        PidControl.Ki_Term = 0.210f;
                        PidControl.Kd_Term = 25.85f;
                    }
                    else if(TECControl.TempCurrent_Value < CHECK_TEMP_SET_COUNT80)
                    {
                        PidControl.Kp_Term = 18.25;     //17.75f;
                        PidControl.Ki_Term = 0.365f;    //0.345f;
                        PidControl.Kd_Term = 55.25;     //53.25f;
                    }
                    else
                    {
                        PidControl.Kp_Term = 3.75f;
                        PidControl.Ki_Term = 0.065f;
                        PidControl.Kd_Term = 4.25f;
                    }
//                    PIDControl_Calculation();
                    if( TECControl.TempCurrent_Value > (TECControl.Set_Value - (MAX_TEMP_TOLERENCE_COUNT * 2)))
                    {
                        PIDControl_Calculation();
                    }else{
                        if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                        {
                            TECCounter++;
                            if(TECCounter >= 10){
                                TEC_DutyCycle += 0X018F;
                                TECCounter = 0;
                                PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
                                PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                            }
                        }else{
                            PIDControl_Calculation();
                        }
                    }
                }
                else
                {
                    TECControl.Current_Value = TECControl.PressCurrent_Value;
//                    PIDControl_ReverseCalculation();
                    if( TECControl.TempCurrent_Value < (TECControl.Set_Value + (MAX_TEMP_TOLERENCE_COUNT * 2)))
                    {
                        PIDControl_ReverseCalculation();
                    }else{
                        if(TEC_DutyCycle < TECCONTROL_halfDutyPeriod)
                        {
                            TECCounter++;
                            if(TECCounter >= 10){
                                TEC_DutyCycle += 0X018F;
                                TECCounter = 0;
                                PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
                                PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
                            }
                        }else{
                            PIDControl_ReverseCalculation();
                        }
                    }
                }
            }
            else
            {
                TECControl_Stop();
                TECControl.TECState_Status = TEC_STATE_STOP;
            }
            if(TECControl.Flags.TECEdited)
            {
                TECControl_Stop();
                TECControl.TECState_Status = TEC_STATE_STOP; 
            }
            
            if(Error_GetFlag() == true)
            {
                TECControl.TECState_Status = TEC_STATE_ERROR;
                TECControl_Stop();
            }
        break;
        
        case TEC_STATE_STOP : 
            TECControl.Flags.TECLowVal = false;
            TECControl_Stop();
            TECControl.TECState_Status = TEC_STATE_IDLE;
            if(!TECControl.Flags.TECEdited)
            {
                TECControl.Flags.TECEn = false;
                TECControl.Flags.TECCheck = false;
            }
        break;
        
        case TEC_STATE_ERROR : 
            TECControl.Flags.TECEn = false;
            TECControl.Flags.TECCheck = false;
            if(Error_GetFlag() == true)
            {
                if((TemperatureControl_GetErrorFlag() == false) && (TECControl.ErrorFlags.TECTemp == false))
                {
                    TECControl_UpdateTemp(0,0,Temp_DefaultVal);
                    TECControl.TECState_Status = TEC_STATE_STOP;
                }
            }
            else
            {
                TECControl.ErrorFlags.TECTemp = false;
                TECControl.TECState_Status = TEC_STATE_STOP;
            }
        break;
        
        default : 
            TECControl_Stop();                                          // turn off PWM generator
        break;
    }
}
/**
 * @brief This function heats the chamber 
 * @param Nothing
 * @return Nothing
 */

void TECControl_Heating(void)
{
    PWM_GeneratorDisable(PWM_GENERATOR_6);                              // turn on PWM generator
    PG6IOCONLbits.SWAP = false;                                         // PWMxH output will be connected to PWMxH output pin
    PWM_PeriodSet(PWM_GENERATOR_6, TEC_Period);                  // Set Period (n = 6392 => 1 / (n * 10 us) = 10 kHz )
    PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);           // Set Duty Cycle (n = 3196 => n / PGxPER = 50 %)
    PWM_DeadTimeLowSet(PWM_GENERATOR_6, TEC_DeadtimeLow);       // Set Falling Edge Dead Time (n = 05 => n * 10 us = 50 us)
    PWM_DeadTimeHighSet(PWM_GENERATOR_6, TEC_DeadtimeHigh);     // Set Rising Edge Dead Time (n = 10 => n * 10 us = 100 us)
    PWM_GeneratorEnable(PWM_GENERATOR_6);                               // turn on PWM generator
}

/**
 * @brief This function cools the function 
 * @param Nothing
 * @return Nothing
 */
void TECControl_Cooling(void)
{
    PWM_GeneratorDisable(PWM_GENERATOR_6);                              // turn off PWM generator
    PG6IOCONLbits.SWAP = true;                                          // PWMxH output will be connected to PWMxL output pin
    PWM_PeriodSet(PWM_GENERATOR_6, TEC_Period);                  // Set Period (n = 6392 => 1 / (n * 10 us) = 10 kHz )
    PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);           // Set Duty Cycle (n = 3196 => n / PGxPER = 50 %)
    PWM_DeadTimeLowSet(PWM_GENERATOR_6, TEC_DeadtimeLow);       // Set Falling Edge Dead Time (n = 05 => n * 10 us = 50 us)
    PWM_DeadTimeHighSet(PWM_GENERATOR_6, TEC_DeadtimeHigh);     // Set Rising Edge Dead Time (n = 10 => n * 10 us = 100 us)
    PWM_GeneratorEnable(PWM_GENERATOR_6);                               // turn on PWM generator    
}

void TECControl_Stop(void)
{
    PWM_GeneratorDisable(PWM_GENERATOR_6);              // turn off PWM generator
}

/**
 * @brief This function is called by som to set the chamber temperature 
 * @param enable, temperature/pressure reading, value
 * @return Nothing
 */
void TECControl_UpdateTemp(bool flagSet, bool flagControl, uint32_t dutyValue)
{
    TECControl.Flags.TECEn = flagSet;
    TECControl.Flags.TECControl = flagControl;
    if(dutyValue != 0)
    {
        TECControl.Flags.TECDisable = false;
#if (TEC_PID_DIFF == ENABLE)
        if(flagControl == false)
        {
            TECControl.Set_Value = dutyValue - DiffVal;
        }
        else
        {
            TECControl.Set_Value = dutyValue;
        }
#else
        TempUpdated = true;
        TECControl.Set_Value = dutyValue;
#endif
    }
    else
    {
        TECControl.Flags.TECCheck = false;
        TECControl.Flags.TECDisable = true;
        Events_SetTecFan(false);
        TECControl_Stop();    
    }
    if(TECControl.Flags.TECEn == true)
    {
        TECControl.Flags.TECEdited = true;
    }
}

uint32_t TECControl_GetValue(void)
{
    return (TECControl.Set_Value);
}

void TECControl_SetDefaultVal(uint32_t tempVal)
{
    Temp_DefaultVal = tempVal;
}

uint16_t TECControl_GetControl(void)
{
    return (TECControl.TECState_Status);
}

float TECControl_GetState(void)
{
    return(fPower);
}

float TECControl_GetPTerm(void)
{
    return(PidControl.Kp_Term);
}

float TECControl_GetITerm(void)
{
    return(PidControl.Ki_Term);
}

float TECControl_GetDTerm(void)
{
    return(PidControl.Kd_Term);
}

bool TECControl_GetStatus(void)
{
    return (TECControl.Flags.TECDisable);
}
#if (TEC_PID_DIFF == ENABLE)
void TECControl_SetTempDiff(int32_t tempval)
{
    DiffVal = tempval - DEAFULT_TEMP_COUNT20;
}
#endif
/**
 * @brief This function initializes pid parameters 
 * @param Nothing
 * @return Nothing
 */
void PIDControl_Initialise(void)
{
    PidControl.Pwm_DutyAdjust = 0;
    PidControl.Current_Err = 0;
    PidControl.Deriv_Err = 0;
    PidControl.Previous_Err = 0;
    PidControl.Err_Integration = 0;
    PidControl.Last_Err_Integration = 0;
    
    PidControl.Proportion_Term = 0.0;
    PidControl.Integral_Term = 0.0;
    PidControl.Deriv_Term = 0.0;
    PidControl.Kp_Term = 5.25f;
    PidControl.Ki_Term = 0.145f;
    PidControl.Kd_Term = 55.5f;
    PidControl.Deriv_Limit = 0;
    PidControl.Integral_Limit = 10000.0f;
//    PidControl.Ki_Term = 0.0f;
//    PidControl.Kd_Term = 0.0f;
}

/**
 * @brief This function is called to calculate the duty cycle of pwm by using PID constants for heating the chamber
 * @param Nothing
 * @return Nothing
 */
void PIDControl_Calculation(void)
{
    PidControl.Current_Err = (int32_t) TECControl.Set_Value - TECControl.Current_Value;
    PidControl.Integral_Term = PidControl.Integral_Term + PidControl.Current_Err;

    // Limit the integral
    if ( PidControl.Integral_Term > PidControl.Integral_Limit) 
    {
        PidControl.Integral_Term = PidControl.Integral_Limit;
    }
    if ( PidControl.Integral_Term < 0.0f) 
    {
        PidControl.Integral_Term = 0.0f;
    }

    // 'P' Term and 'I' Term
    fPower = (float)(PidControl.Kp_Term * PidControl.Current_Err) + (float)(PidControl.Ki_Term * PidControl.Integral_Term);

    PidControl.Err_Integration = (int32_t)PidControl.Current_Err - PidControl.Previous_Err;
    PidControl.Previous_Err = PidControl.Current_Err;
    // If target temperature is near reduce the power cycle based on output of
    // change of outlet temperature
    if(PidControl.Current_Err < 4000U)                                                                // Temperature difference below 3 degree celsius
    {
        fPower = fPower + (float) (PidControl.Kd_Term * PidControl.Err_Integration);
    }

    // Limit the power
    if ( fPower > MAX_FIRING_ANGLE) 
    {
        fPower = MAX_FIRING_ANGLE;
    }

    // Limit the power
    if ( fPower < 32.0f) 
    {
        fPower = 0x0000;
    }

    PidControl.Pwm_DutyAdjust = (uint32_t) ((TEC_Period * fPower) / MAX_FIRING_ANGLE);
    PG6DC = (uint16_t) PidControl.Pwm_DutyAdjust;
    PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
}

/**
 * @brief This function is called to calculate duty cycle of pwm using pid constants for cooling the chamber 
 * @param Nothing
 * @return Nothing
 */
void PIDControl_ReverseCalculation(void)
{
    PidControl.Current_Err = (int32_t) TECControl.Set_Value - TECControl.Current_Value;
    PidControl.Current_Err = 0 - PidControl.Current_Err;
    PidControl.Integral_Term = PidControl.Integral_Term + PidControl.Current_Err;

    // Limit the integral
    if ( PidControl.Integral_Term > PidControl.Integral_Limit) 
    {
        PidControl.Integral_Term = PidControl.Integral_Limit;
    }
    if ( PidControl.Integral_Term < 0.0f) 
    {
        PidControl.Integral_Term = 0.0f;
    }
 
    // 'P' Term and 'I' Term
    fPower = (float)(PidControl.Kp_Term * PidControl.Current_Err) + (float)(PidControl.Ki_Term * PidControl.Integral_Term);

    PidControl.Err_Integration = (int32_t)PidControl.Current_Err - PidControl.Previous_Err;
    PidControl.Previous_Err = PidControl.Current_Err;
    // If target temperature is near reduce the power cycle based on rate of
    // change of outlet temperature
    if(PidControl.Err_Integration < 1000U)                                                                // Temperature difference below 6 degree celsius
    {
        fPower = fPower + (float) (PidControl.Kd_Term * PidControl.Err_Integration);
    }

    // Limit the power
    if ( fPower > MAX_FIRING_ANGLE) 
    {
        fPower = MAX_FIRING_ANGLE;
    }

    // Limit the power
    if ( fPower < 32.0f) 
    {
        fPower = 0x0020;
    }

    PidControl.Pwm_DutyAdjust = (uint32_t) ((TEC_Period * fPower) / MAX_FIRING_ANGLE);
    PG6DC = (uint16_t) PidControl.Pwm_DutyAdjust;
//    PWM_DutyCycleSet(PWM_GENERATOR_6, TEC_DutyCycle);
    PWM_SoftwareUpdateRequest(PWM_GENERATOR_6);
}

