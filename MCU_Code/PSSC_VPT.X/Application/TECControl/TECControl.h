/* 
 * File:   TECControl.h
 * Author: dnyaneshwar.pawar
 *
 * Created on January 6, 2021, 2:35 PM
 */

#ifndef TECCONTROL_H
#define	TECCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#ifndef TEC_PID_DIFF
    #define TEC_PID_DIFF DISABLE
#endif
    
// Enums for Valve Motor State status
typedef enum {
    TEC_STATE_IDLE = 0,
    TEC_TEMP_STATE_RUNNING,
    TEC_PRESS_STATE_RUNNING,
    TEC_STATE_STOP,
    TEC_STATE_ERROR,
}TECControlState_ETYP;

typedef struct {

// Private Variables
    uint32_t Pwm_DutyAdjust;
    int32_t Current_Err;
    int32_t Deriv_Err;
    int32_t Previous_Err;
    int32_t Err_Integration;
    int32_t Last_Err_Integration;
    
    float Proportion_Term;
    float Integral_Term;
    float Deriv_Term;
    float Kp_Term;
    float Ki_Term;
    float Kd_Term;
    float Deriv_Limit;
    float Integral_Limit;

} PIDCONTROL_STYP;

//CLASS OBJECT DEFINITION

typedef struct {

//  Public Variables
struct {
    // To Enable Flag for TEC Motor 0-Heating 1-Cooling
    uint8_t TECStatus:1;
    // To Enable Flag for TEC Control 0-OFF 1-ON
    uint8_t TECEn:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t TECEdited:1;
    // To control temp/pressure value  of the chamber 0 - temp value / 1 - press value
    uint8_t TECControl:1;
    // To check temp value needs to be heated or cooled single time 0-heating, 1-cooling
    uint8_t TECCheck:1;
    // To check temp value needs to be heated or cooled single time 0-heating, 1-cooling
    uint8_t TECDisable:1;
    // To check temp value needs to be heated or cooled single time 0-heating, 1-cooling
    uint8_t TECLowVal:1;
    
  } Flags;
  
  struct {
    // To display temperature Error if anything misbehaves
    uint8_t TECTemp:1;
    // To display pressure Error if anything misbehaves
    uint8_t TECPress:1;
    // To display temperature Error if anything misbehaves
    uint8_t TECAmb:1; 
    // To check Error even after the flag is reset by SOM if anything misbehaves
    uint8_t ErrCheck:1;
  } ErrorFlags;

// Public Methods
    void (*HandlerFunction)(void);

// Private Variables
    TECControlState_ETYP TECState_Status;
    uint16_t AmbTemp_Value;
    uint32_t Current_Value;
    uint32_t TempCurrent_Value;
    uint32_t PressCurrent_Value;
    uint32_t Set_Value;
} TECCONTROL_STYP;


// DEFINE CLASS OBJECT DEFAULTS

#define TECCONTROL_DEFAULTS     {                                   \
                                {0,0,0,0,0,0,0},                    \
                                {0,0,0,0},                            \
                                &TECControl_Handler,                \
                                TEC_STATE_IDLE,                     \
                                0,                                  \
                                0,                                  \
                                0,                                  \
                                0,                                  \
                                0                                   \
                            }    
    
#define ENABLE                          true
#define DISABLE                         false
#define TEMP_TOLERENCE_COUNT            142             //0.1 degree tolerance
#define MAX_TEMP_TOLERENCE_COUNT        710             //1.0 degree tolerance
#define MAX_FIRING_ANGLE                10000.0f        // 100.00% duty cycle
#define MAXOVER_TIME                    12              // 3sec
//#define CHECK_SET_COUNT             97519           // 55 degree count to change the Kp,Ki,Kd parameters
#define CHECK_TEMP_SET_COUNT_AMB        64000           // below 31 degree count to change the Kp,Ki,Kd parameters
#define CHECK_TEMP_SET_COUNT40          78000           // below 41 degree count to change the Kp,Ki,Kd parameters
#define CHECK_TEMP_SET_COUNT_HI         107000          // above 61 degree count to change the Kp,Ki,Kd parameters
#define CHECK_TEMP_SET_COUNT_LO         43000           // below 17 degree count to change the Kp,Ki,Kd parameters
#define CHECK_TEMP_SET_COUNT80          135000          // above 81 degree count to change the Kp,Ki,Kd parameters
#define CHECK_TEMP_SET_COUNT90          149000          // above 91 degree count to change the Kp,Ki,Kd parameters

#define CHECK_PRESS_SET_COUNT           50752          // 200 kpa count to change the Kp,Ki,Kd parameters 25k for 100kpa, 38k for 150kpa
#define MAX_PRESS_LIMIT_COUNT           51000          // 200kPa count to change the Kp,Ki,Kd parameters
#define MAX_TEMP_LIMIT_COUNT            181000         // 110 degree count to detect max temperature of piston block
//#define MAX_AMBIENT_TEMP_COUNT          1115           // 75 deg amb temp (75*6.25) + 424 = 892mv ref 3.3V and 12 bit internal adc will give 1115 counts for 75 deg C
                                                       // all above data is received from data sheets
#define MAX_AMBIENT_TEMP_COUNT          1030           // 65 deg amb temp (65*6.25) + 424 = 830mv ref 3.3V and 12 bit internal adc will give 1030 counts for 65 deg C

#define DEAFULT_TEMP_COUNT20            46810
#define HEAT_COOL_TEMP_COUNT            51000
#define TECCONTROL_DUTY_PERIOD          0X1F3F              // 1KHz frequency
//#define TECCONTROL_DUTY_PERIOD          0XF9F              //0X7CF --> 4KHz frequency           0XF9F --> 2kHz frequency
#define TECCONTROL_DEFAULT_DUTY_CYCLE   0X031F              // 10% duty cycle value for 1KHz frequency
//#define TECCONTROL_halfDutyPeriod       0X0F9F              // 50% duty cycle value for 1KHz frequency

#define MAX_ERR_DEBOUNCE        5

void TECControl_Initialise(void);
void TECControl_Handler(void);
void TECControl_Heating(void);
void TECControl_Cooling(void);
void TECControl_UpdateTemp(bool flagSet, bool flagControl, uint32_t dutyValue);
void TECControl_Stop(void);
uint32_t TECControl_GetValue(void);
void TECControl_SetDefaultVal(uint32_t tempVal);
uint16_t TECControl_GetControl(void);
float TECControl_GetState(void);
float TECControl_GetPTerm(void);
float TECControl_GetITerm(void);
float TECControl_GetDTerm(void);
bool TECControl_GetStatus(void);
void PIDControl_Initialise(void);
void PIDControl_Calculation(void);
void PIDControl_ReverseCalculation(void);
void TECControl_SetTempDiff(int32_t tempVal);


// EXTERN VARIABLES
extern TECCONTROL_STYP TECControl;

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

#endif	/* TECCONTROL_H */

