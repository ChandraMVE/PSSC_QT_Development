/* 
 * File:   TemperatureControl.h
 * Author: dnyaneshwar.pawar
 *
 * Created on 13 January, 2021, 3:26 PM
 */

#ifndef TEMPERATURECONTROL_H
#define	TEMPERATURECONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>    

#define MAX_COMMANDBUFF     10
#define MAX_BUFFSIZE        10

// Enums for ADC operation status
typedef enum {
    TEMP_ADC_STATE_IDLE = 0,
    TEMP_ADC_STATE_READ,
    TEMP_ADC_STATE_END,
    TEMP_ADC_STATE_ERROR        
}TempControlState_ETYP;

// Enums for ADC Command values
typedef enum {
    PROG_RST = 0,
    FEATURE_SEL,
    INPUT_RANGE0,
    READ_RANGE0,
    MANUAL_CH0,
    LAST_CONFIG,
    DUMMY_WRITE,
    INPUT_RANGE1,
    READ_RANGE1,
    MANUAL_CH1
}CommandValues_ETYP;

//CLASS OBJECT DEFINITION

typedef struct {

//  Public Variables
struct {
    // To Enable Flag for TEC Motor 0-Heating 1-Cooling
    uint8_t Buffer_Ready:1;
    // To Enable Flag for TEC Control 0-OFF 1-ON
    uint8_t TECEn:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t TECEdited:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t TECError:1;
    
  } Flags;

// Public Methods
    void (*HandlerFunction)(void);
    
// Private Variables
    TempControlState_ETYP ADC_Status;
    uint8_t Buffer_Counter;
    uint32_t ADC_Count;
    uint32_t Temp_Count;
    uint32_t Press_Count;
    uint32_t Temp_Value;
    uint32_t Press_Value;

    uint16_t Command_ARRY[MAX_COMMANDBUFF];
    uint32_t Temp_Buffer[MAX_BUFFSIZE];
    uint32_t Press_Buffer[MAX_BUFFSIZE];
} TemperatureControl_STYP;


// DEFINE CLASS OBJECT DEFAULTS

#define TEMPERATURECONTROL_DEFAULTS     {                           \
                                {0,0,0,0},                          \
                                &TemperatureControl_Handler,        \
                                TEMP_ADC_STATE_IDLE,                \
                                0,                                  \
                                0,                                  \
                                0,                                  \
                                0,                                  \
                                0,                                  \
                                0                                   \
                            }

//#define NUMBER_OF_PARAMETERS    6 // Total PID constants




//  CLASS METHOD PROTOTYPES
void TemperatureControl_Initialise(void);
void TemperatureControl_Handler(void);
uint32_t TemperatureControl_GetTempADC(void);
uint32_t TemperatureControl_GetPressADC(void);
bool TemperatureControl_GetErrorFlag(void);
void TemperatureControl_UpdateTemp(uint32_t tmp);
void TemperatureControl_TimeIncreament(void);
uint32_t TemperatureControl_GetTime(void);
bool TemperatureControl_TemperatureStable(void);


// EXTERN VARIABLES
extern TemperatureControl_STYP TemperatureControl;



#ifdef	__cplusplus
}
#endif

#endif	/* TEMPERATURECONTROL_H */

