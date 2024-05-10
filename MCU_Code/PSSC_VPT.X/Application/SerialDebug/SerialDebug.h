/* 
 * File:   SerialDebug.h
 * Author: dnyaneshwar.pawar
 *
 * Created on March 24, 2021, 4:20 PM
 */

#ifndef SERIALDEBUG_H
#define	SERIALDEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>    

#define ENABLE_SERIALDEBUG_COMM
    
// Enums for UART serial debug status
typedef enum {
  SERIALDEBUG_STATE_IDLE = 0,
  SERIALDEBUG_STATE_WAITING,
  SERIALDEBUG_STATE_COMMAND,
}SerialDebugState_ETYP;


//CLASS OBJECT DEFINITION

typedef struct {

//  Public Variables
// None

// Public Methods
  void (*HandlerFunction)(void);

// Private Variables
  SerialDebugState_ETYP RxStatus;
  uint8_t RxIndex;
  uint8_t TxARRY[256];
  uint8_t RxARRY[32];
} SerialDebug_STYP;

typedef enum {
  DEBUG_TEMP_CONTROL = 0,
  DEBUG_TEMP_WAITING,
  DEBUG_VALVE_CONTROL,
  DEBUG_VALVE_WAITING,
  DEBUG_PISTON_CONTROL,
  DEBUG_PISTON_WAITING
}DebugLoad_ETYP;


// DEFINE CLASS OBJECT DEFAULTS

#define SERIALDEBUG_DEFAULTS     {                               \
                                &SerialDebug_Handler,            \
                                SERIALDEBUG_STATE_IDLE,          \
                                0                                \
                            }

//#define NUMBER_OF_PARAMETERS    6 // Total PID constants

#define MAX_WAITTIME            200
#define TX_TIME                 10
#define DIGIT_AFTER_DECIMAL     2
#define MAX_ADC_DIGIT           6
#define MAX_AMB_DIGIT           4
#define MAX_SHAKER_DIGIT        3
#define MAX_DEBUG_TEMP_STRING   12


//  CLASS METHOD PROTOTYPES
void SerialDebug_Initialise(void);
void SerialDebug_Handler(void);
void SerialDebug_SendByte(uint8_t bData);
uint8_t SerialDebug_CalCRC(uint8_t *ptr, uint8_t count);
uint8_t SerialDebug_CRCArrayFill(const char * string, uint8_t i, uint8_t k);
void SerialDebug_PrintDebugString(const char * string, uint8_t len );
void SerialDebug_PrintACK(uint8_t tempAck);

// EXTERN VARIABLES
extern SerialDebug_STYP SerialDebug;




#ifdef	__cplusplus
}
#endif

#endif	/* SERIALDEBUGDEBUG_H */

