/* 
 * File:   PistonMotor.h
 * Author: dnyaneshwar.pawar
 *
 * Created on January 4, 2021, 1:42 PM
 */

#ifndef PISTONMOTOR_H
#define	PISTONMOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>    
    
    
// Enums for UART serial debug status
typedef enum {
  PISTONMOTOR_STATE_IDLE = 0,
  PISTONMOTOR_STATE_RUNNING,
  PISTONMOTOR_STATE_STOP,
  PISTONMOTOR_STATE_ERROR,
}PistonMotorState_ETYP;

//CLASS OBJECT DEFINITION

typedef struct {

//  Public Variables
struct {
    // To Motor Flag for Piston Motor 0-OFF 1-ON
    uint8_t PMStatus:1;
    // To Enable Flag for Piston Motor 0-OFF 1-ON
    uint8_t EnPM:1;
    // To Save Editing Piston Motor in Idle condition 0-Edit 1-dont turn motor to bring it to 0
    uint8_t EditedPM:1;
    // To Error Flag for Piston Motor 0-OFF 1-ON
    uint8_t ErrorPM:1;
    // Edit Flag for Piston Motor position change in running condition 0-OFF 1-ON
    uint8_t EditedSet:1;
    // Check Flag for Piston Motor initial position check in run/stop condition 0-OFF 1-ON
    uint8_t PMCheck:1;
    // Check Flag for Piston Motor initial position check in run/stop condition 0-OFF 1-ON
    uint8_t ErrorRun:1;
  } Flags;

// Public Methods
    void (*HandlerFunction)(void);

// Private Variables
    PistonMotorState_ETYP PMState_Status;

    float Current_Position;
    float Set_Position;
} PISTONMOTOR_STYP;


// DEFINE CLASS OBJECT DEFAULTS

#define PISTONMOTOR_DEFAULTS     {                                  \
                                {0,0,0,0,0,0,0},                    \
                                &PistonMotor_Handler,               \
                                PISTONMOTOR_STATE_IDLE,             \
                                0.0,                                \
                                0.0                                 \
                            }    
    
#define CONVERSION_CONSTANT         6671                // 16 Lines(32Pulses), Two Pulse Counter(Encoder A,B), 14 gear motor 1 ml = 7.5489 rev of screw
                                                // (((16*2)*2)*14)*7.5489
//#define PM_MAX_POSITION             5.25f
#define PM_MAX_POSITION             35023
#define CURRENT_LIMIT_COUNT         1000
#define PISTON_DUTY_PERIOD          0X1F3F              // 1KHz frequency
#define PISTON_DEFAULT_DUTY_CYCLE   0X15DF              // 70% duty cycle value for 1KHz frequency
#define PISTON_DEFAULT_DUTY_CYCLE_1 0XF9F              // 50% duty cycle value for 1KHz frequency
#define PISTON_DYNAMIC_DUTY_CYCLE   0X95F              // 30% duty cycle value for 1KHz frequency
#define MAX_DEBOUNCE_COUNT          3
#define MAX_PM_WAIT_TIME            600     //50ms * 600 = 30 seconds wait time to detect initial position after shaker motor is turned ON


void PistonMotor_Initialise(void);
void PistonMotor_Handler(void);
void PistonMotor_Up(void);
void PistonMotor_Down(void);
void PistonMotor_UpdatePostion(bool flagSet, float f_position);
float PistonMotor_GetPostion(void);
float PistonMotor_GetSetPostion(void);
bool PistonMotor_GetStatus(void);
void PistonMotor_Stop(void);
void PistonMotor_CheckError(void);
void PistonMotor_HesLedStatus(void);
void PistonMotor_ChangedPosition(void);
void PistonMotor_RunningState(void);
void PistonMotor_SetDutyCycle(void);


// EXTERN VARIABLES
extern PISTONMOTOR_STYP PistonMotor;


/*
 * Formula for PWM Period
 * 
 * PGxPER = ((ACLK * 8 * Desired PWM Period) / PWM Input Clock Prescaler Divider) - 8
 * 
 * ACLK = (REFCLK * M1) / N
 * 
 * where:
 * REFCLK = = FRC = 8 MHz
 * M1 = 1   Auxiliary PLL Disabled
 * N = 1    Postscaler ratio selected by the Auxiliary Clock Control register
 * 
 * PWM Input Clock Prescaler Divider = 1:2   Postscaler ratio selected by the PCLKDIV<2:0>
 * Desired PWM Period = 1 / Desired PWM Switching Frequency
 * Desired PWM Switching Frequency  = 10 kHz
 * 
 * ACLK = (8MHz * 1) / 1    = 8MHz
 * Desired PWM Period = 1 / 10kHz   = 100 us
 * PGxPER   = ((8MHz * 8 * 100 us) / 2) - 8
 *          = 3192      Decimal
 *          = 0XC78     Hex
 *          = 0X635     Hex
 *          = 1596      Decimal
 * 
 */


#ifdef	__cplusplus
}
#endif

#endif	/* PISTONMOTOR_H */

