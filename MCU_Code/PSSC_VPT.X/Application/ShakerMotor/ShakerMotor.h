/* 
 * File:   ShakerMotor.h
 * Author: dnyaneshwar.pawar
 *
 * Created on January 6, 2021, 3:49 PM
 */

#ifndef SHAKERMOTOR_H
#define	SHAKERMOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

// Enums for Shaker Motor State status
typedef enum {
    SHAKERMOTOR_STATE_IDLE = 0,
    SHAKERMOTOR_STATE_EIGHT_MICROSTEP,
    SHAKERMOTOR_STATE_FOUR_MICROSTEP,
    SHAKERMOTOR_STATE_TWO_MICROSTEP,
    SHAKERMOTOR_STATE_SOFTSTART,
    SHAKERMOTOR_STATE_RUNNING,
    SHAKERMOTOR_STATE_STOPPING,       
    SHAKERMOTOR_STATE_ERROR,
}ShakerMotorState_ETYP;

//CLASS OBJECT DEFINITION

typedef struct {

//  Public Variables
struct {
    // To Enable Flag for Shaker Motor 0-OFF 1-ON
    uint8_t SMStatus:1;
    // To Enable Flag for Shaker Motor 0-OFF 1-ON
    uint8_t SMEn:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t SMEdited:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t SMError:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t SMCheck:1;
  } Flags;

// Public Methods
    void (*HandlerFunction)(void);

// Private Variables
    ShakerMotorState_ETYP SMState_Status;

    uint16_t Current_Speed;
    uint16_t Set_Speed;
} SHAKERMOTOR_STYP;


// DEFINE CLASS OBJECT DEFAULTS

#define SHAKERMOTOR_DEFAULTS     {                                  \
                                {0,0,0},                            \
                                &ShakerMotor_Handler,               \
                                SHAKERMOTOR_STATE_IDLE,             \
                                0,                                  \
                                0                                   \
                            }    

#define DEFAULT_SPEED   90
#define MAX_SPEED       210
#define MIN_SPEED       60
//#define INIT_SPEED      30
#define INIT_SPEED      30

//#define STEP_SPEED      20
//#define STEP_SPEED      10
#define STEP_SPEED         3 //1

#define STEP_SIZE 0.15f
#define MAX_DEBOUNCE_COUNT 3
//#define SPEED_DEBOUNCE_COUNT 7
#define SPEED_DEBOUNCE_COUNT 1
#define MAX_WAIT_TIME       200     //150ms * 200 = 30 seconds wait time to detect initial position after shaker motor is turned ON
#define SM_MAX_ERR_COUNT    5

    
void ShakerMotor_Initialise(void);
void ShakerMotor_Handler(void);
void ShakerMotor_Drive(void);
void ShakerMotor_UpdateSpeed(bool flagSet, uint16_t wSpeed);
bool ShakerMotor_GetStatus(void);
uint16_t ShakerMotor_GetSpeed(void);
void ShakerMotor_Stop(void);
void ShakerMotor_CalculateSpeed(uint16_t wSpeed);
bool ShakerMotor_GetErrFlag(void);
uint16_t ShakerMotor_GetCounter(void);
bool ShakerMotor_GetPulseErrCheck(void);
void ShakerMotor_SetPulseErrCheck(bool setFlag);
uint16_t ShakerMotor_ErrCounter(void);
void ShakerMotor_SoftStartFunction(void);
bool ShakerMotor_CheckStops(void);
void ShakerMotor_SetStops(void);
void ShakerMotor_StopFunction(void);

// EXTERN VARIABLES
extern SHAKERMOTOR_STYP ShakerMotor;


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

/*
 * Formula for RPM and Period calculation
 * 
 * RPM = a/360 * fz * 60        or
 * fz = RPM / ( (a/360) * 60)
 * fz = RPM / (0.15)
 * 
 * where:
 * fz = = frequency of pulses 
 * RPM = speed of Stepper Motor in rpm
 * a = 0.9    step angle of motor
 * 
 * 
 */


#ifdef	__cplusplus
}
#endif

#endif	/* SHAKERMOTOR_H */

