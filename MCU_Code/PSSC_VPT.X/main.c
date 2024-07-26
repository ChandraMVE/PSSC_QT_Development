/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.166.0
        Device            :  dsPIC33CK128MP206
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.41
        MPLAB 	          :  MPLAB X v5.30
*/

/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "main.h"
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "Timers.h"
#include "Scheduler.h"
#include "Events.h"
#include "Serial.h"
#include "PistonMotor.h"
#include "ValveMotor.h"
#include "TECControl.h"
#include "ShakerMotor.h"
#include "TemperatureControl.h"
#include "PistonEncoder.h"
#include "Alarm.h"
#include "ADCRead.h"
#include "SerialDebug.h"
#include "Error.h"

static uint16_t tCounter;
static uint16_t PMCounter;
bool Flag_Complete;
/*
                         Main application
 */

// Objects declaration and Initialization
Scheduler_STYP scheduler = SCHEDULER_DEFAULTS;
Serial_STYP Serial = SERIAL_DEFAULTS;
PISTONMOTOR_STYP PistonMotor = PISTONMOTOR_DEFAULTS;
VALVEMOTOR_STYP ValveMotor = VALVEMOTOR_DEFAULTS;
TECCONTROL_STYP TECControl = TECCONTROL_DEFAULTS;
SHAKERMOTOR_STYP ShakerMotor = SHAKERMOTOR_DEFAULTS;
TemperatureControl_STYP TemperatureControl = TEMPERATURECONTROL_DEFAULTS;
PISTONENCODER_STYP PistonEncoder = PISTONENCODER_DEFAULTS;
ALARM_STYP Alarm = ALARM_DEFAULTS;
ADCRead_STYP ADCRead = ADC_READ_DEFAULTS;
SerialDebug_STYP SerialDebug = SERIALDEBUG_DEFAULTS;
Error_STYP Error = ERROR_DEFAULTS;

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    // Start watchdog timer
    START_WATCHDOG();
    
    Timers_Initialise();
    Events_Initialise();
    PistonMotor_Initialise();
    ValveMotor_Initialise();
    TECControl_Initialise();
    ShakerMotor_Initialise();
    TemperatureControl_Initialise();
    PistonEncoder_Initialise();
    Alarm_Initialise();
    ADCRead_Initialise();
    SerialDebug_Initialise();
    scheduler.AddTask(Serial.HandlerFunction, SERIAL_INITIAL_DELAY, SERIAL_INTERVAL);
    scheduler.AddTask(PistonMotor.HandlerFunction, PISTON_MOTOR_INITIAL_DELAY, PISTON_MOTOR_INTERVAL);
    scheduler.AddTask(ValveMotor.HandlerFunction, VALVE_MOTOR_INITIAL_DELAY, VALVE_MOTOR_INTERVAL);
    scheduler.AddTask(ShakerMotor.HandlerFunction, SHAKER_MOTOR_INITIAL_DELAY, SHAKER_MOTOR_INTERVAL);
    scheduler.AddTask(TemperatureControl.HandlerFunction, TEMPERATURE_CONTROL_INITIAL_DELAY, TEMPERATURE_CONTROL_INTERVAL);
    scheduler.AddTask(TECControl.HandlerFunction, TEC_CONTROL_INITIAL_DELAY, TEC_CONTROL_INTERVAL);
    scheduler.AddTask(PistonEncoder.HandlerFunction, PISTON_ENCODER_INITIAL_DELAY, PISTON_ENCODER_INTERVAL);
    scheduler.AddTask(ADCRead.HandlerFunction, ADC_READ_INITIAL_DELAY, ADC_READ_INTERVAL);
    scheduler.AddTask(Alarm.HandlerFunction, ALARM_INITIAL_DELAY, ALARM_INTERVAL);
    
    #ifdef ENABLE_SERIALDEBUG_COMM
    scheduler.AddTask(SerialDebug.HandlerFunction, SERIAL_DEBUG_INITIAL_DELAY, SERIAL_DEBUG_INTERVAL);
    #endif
    
    LED_2_SetDigitalOutput();
    LED_2_SetLow();
//    LED_3_SetHigh();
    tCounter = 0;
    Flag_Complete = 0;
    PMCounter = 0;
    
    while (1)
    {
//        PistonMotor_ChangedPosition();
        // Add your application code
        PistonMotor_RunningState();
        if(PistonMotor_MotorStopped()){
            if(PistonMotor_PMDelay_Counter() == true){
                PistonMotor_ChangedPosition();
            }
        }
        if(ShakerMotor_CheckStops()){
            ShakerMotor_StopFunction();
        }
//        ShakerMotor_SoftStartFunction();
        if ( scheduler.flags.interruptFLG) 
        {
            scheduler.flags.interruptFLG = 0;
            scheduler.run();

            if(PistonMotor_MotorStopped()){
                if(PistonMotor_PMDelay_Counter() == false){
//                    SetPistonMotor_StopFlag(false);
                    PMCounter++;
                    if(PMCounter >= 100){
                        PMCounter = 0;
//                        SetPistonMotor_StopFlag(false);
//                        PistonEncoder_SetCountA();
                        PistonMotor_SetPMDelay_Counter();
                    }
                }
            }
            tCounter++;
            if(!Flag_Complete)
            {
                if(tCounter > 2000)
                {
                    Flag_Complete = true;
                    tCounter = 0;
                }
                
            }
            else
            {
                if(tCounter > 50)
                {
                    LED_2_Toggle();
//                    LED_3_Toggle();
                    tCounter = 0;
                }
            }
            // Reset watchdog timer whenever tasks get executed
            RESET_WATCHDOG();
        }

    }
    return 1; 
}
/**
 End of File
*/

