/* 
 * File:   Alarm.h
 * Author: dnyaneshwar.pawar
 *
 * Created on February 6, 2021, 4:48 PM
 */

#ifndef ALARM_H
#define	ALARM_H

#ifdef	__cplusplus
extern "C" {
#endif

// Enums for Shaker Motor State status
typedef enum {
  ALARM_STATE_IDLE = 0,
  ALARM_STATE_RUNNING,
  ALARM_STATE_STOP       
}AlarmState_ETYP;

//CLASS OBJECT DEFINITION

typedef struct {

//  Public Variables
struct {
    // To Enable Flag for Shaker Motor 0-OFF 1-ON
    uint8_t Alarm_Status:1;
    // To Enable Flag for Shaker Motor 0-OFF 1-ON
    uint8_t Alarm_En:1;
    // To Enable Flag for Shaker Motor 0-OFF 1-ON
    uint8_t Error_En:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t Alarm_Edited:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t Alarm_Error:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t Alarm_Pattern:1;
  } Flags;

// Public Methods
    void (*HandlerFunction)(void);

// Private Variables
    AlarmState_ETYP Alarm_State;

    uint8_t Current_Level;
    uint8_t Set_Level;
    uint8_t Alarm_Counter;
    uint8_t Pattern_Counter;
} ALARM_STYP;

// DEFINE CLASS OBJECT DEFAULTS

#define ALARM_DEFAULTS     {                                        \
                                {0,0,0,0,0,0},                      \
                                &Alarm_Handler,                     \
                                ALARM_STATE_IDLE,                   \
                                0,                                  \
                                0,                                  \
                                0,                                  \
                                0                                   \
                            }    

#define DEFAULT_LEVEL 2
#define MAX_LEVEL 5
#define MIN_LEVEL 0 
#define MAX_ON_TIME         20          // 500ms Handler time * 20 = 10 secs ON time
#define MAX_PATTERN_TIME    4           // 500ms * 4 = 2Sec ON/OFF time
#define ALARM_DUTY_PERIOD          0X07CF              // 1KHz frequency
#define ALARM_DEFAULT_DUTY_CYCLE   0X03E7              // 10% duty cycle value for 1KHz frequency
    
void Alarm_Initialise(void);
void Alarm_Handler(void);
void Alarm_Drive(void);
void Alarm_UpdateAlarm(bool flagSet);
void Alarm_UpdateError(bool flagSet);
void Alarm_UpdateVolume(bool flagSet, uint8_t bLevel);
bool Alarm_GetStatus(void);
uint16_t Alarm_GetValue(void);
void Alarm_Stop(void);

// EXTERN VARIABLES
extern ALARM_STYP Alarm;


#ifdef	__cplusplus
}
#endif

#endif	/* ALARM_H */

