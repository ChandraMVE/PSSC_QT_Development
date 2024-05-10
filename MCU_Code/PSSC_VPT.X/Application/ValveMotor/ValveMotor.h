/* 
 * File:   ValveMotor.h
 * Author: dnyaneshwar.pawar
 *
 * Created on 5 January, 2021, 6:44 PM
 */

#ifndef VALVEMOTOR_H
#define	VALVEMOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#ifndef VM_BOARD_VERSION
    #define VM_BOARD_VERSION BETA_VERSION
#endif

// Enums for Valve Motor State status
typedef enum 
{
    VALVEMOTOR_STATE_INITIAL = 0,
    VALVEMOTOR_STATE_IDLE,
    VALVEMOTOR_STATE_RUNNING,
    VALVEMOTOR_STATE_STOP,
    VALVEMOTOR_STATE_ERROR,
}ValveMotorState_ETYP;

typedef enum 
{
    VALVE_POSITION_OFF = 0,
    VALVE_POSITION_INLET,
    VALVE_POSITION_OUTLET,
    VALVE_POSITION_UNID
}ValveMotorPosition_ETYP;

//CLASS OBJECT DEFINITION

typedef struct {

//  Public Variables
struct {
    // To Enable Flag for Piston Motor 0-OFF 1-ON
    uint8_t VMStatus:1;
    // To Enable Flag for Piston Motor 0-OFF 1-ON
    uint8_t VMEn:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t VMEdited:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t VMError:1;
    // To check initial position of the  0-OFF 1-ON
    uint8_t VMCheck:1;
  } Flags;

// Public Methods
    void (*HandlerFunction)(void);

// Private Variables
    ValveMotorState_ETYP VMState_Status;

    ValveMotorPosition_ETYP Current_Position;
    ValveMotorPosition_ETYP Set_Position;
} VALVEMOTOR_STYP;


// DEFINE CLASS OBJECT DEFAULTS

#define VALVEMOTOR_DEFAULTS     {                                   \
                                {0,0,0,0,0},                        \
                                &ValveMotor_Handler,                \
                                VALVEMOTOR_STATE_INITIAL,           \
                                VALVE_POSITION_UNID,                \
                                VALVE_POSITION_OFF                  \
                            }    
    
#define MAX_VALVE_COUNT     4  
#define ALPHA_VERSION       0
#define BETA_VERSION        1
#define VALVE_DUTY_PERIOD               0X1F3F              // 1KHz frequency
#define VALVE_DUTY_PERCENTAGE           0x14                //40% duty cycle                        //0x0A                // 20% duty cycle
#define VALVE_DEFAULT_DUTY_CYCLE        ((VALVE_DUTY_PERIOD / 100) * VALVE_DUTY_PERCENTAGE)              // duty cycle value for 1KHz frequency
#define MAX_POSITION_DETECTION_TIME     300                 // 100ms * 300 = 30 seconds
#define VM_MIN_TEMP_COUNT_MOTOR         (uint32_t)64000               // 25 deg count

void ValveMotor_Initialise(void);
void ValveMotor_Handler(void);
void ValveMotor_Clockwise(void);
void ValveMotor_AntiClockwise(void);
void ValveMotor_UpdatePostion(bool flagSet, uint8_t bPosition);
void ValveMotor_CheckPostion(void);
uint8_t ValveMotor_GetPostion(void);
uint8_t ValveMotor_GetSetPostion(void);
bool ValveMotor_GetStatus(void);
uint8_t ValveMotor_GetState(void);
void ValveMotor_Stop(void);

// EXTERN VARIABLES
extern VALVEMOTOR_STYP ValveMotor;

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

#endif	/* VALVEMOTOR_H */

