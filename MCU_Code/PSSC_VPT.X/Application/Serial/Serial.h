/* 
 * File:   Serial.h
 * Author: dnyaneshwar.pawar
 *
 * Created on 18 December, 2020, 12:23 PM
 */

#ifndef SERIAL_H
#define	SERIAL_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>    

#define ENABLE_SERIAL_COMM
    
// Enums for UART serial debug status
typedef enum {
  SERIAL_STATE_IDLE = 0,
  SERIAL_STATE_WAITING,
  SERIAL_STATE_COMMAND,
}SerialState_ETYP;

typedef enum {
  SERIAL_TEMP_CONTROL = 0,
  SERIAL_TEMP_WAITING,
  SERIAL_VALVE_CONTROL,
  SERIAL_VALVE_WAITING,
  SERIAL_PISTON_CONTROL,
  SERIAL_PISTON_WAITING,
  SERIAL_SHAKER_CONTROL,
  SERIAL_SHAKER_WAITING
}SerialLoad_ETYP;


//CLASS OBJECT DEFINITION

typedef struct {

//  Public Variables
// None

// Public Methods
  void (*HandlerFunction)(void);

// Private Variables
  SerialState_ETYP RxStatus;
  uint8_t RxIndex;
  uint8_t TxARRY[70];
  uint8_t RxARRY[32];
} Serial_STYP;


// DEFINE CLASS OBJECT DEFAULTS

#define SERIAL_DEFAULTS     {                               \
                                &Serial_Handler,            \
                                SERIAL_STATE_IDLE,          \
                                0                           \
                            }

//#define NUMBER_OF_PARAMETERS    6 // Total PID constants

#define MAX_WAITTIME        200
#define TX_TIME             10
#define DIGIT_AFTER_DECIMAL 2
#define MAX_ADC_DIGIT       6
#define MAX_AMB_DIGIT       4
#define MAX_SHAKER_DIGIT    3
#define MAX_TEMP_STRING     12
#define SERIAL_TEMP_TOL     5000

#define MAJOR_SW_VERSION        0
#define MINOR_SW_VERSION        1
#define TEST_SW_VERSION         46


//  CLASS METHOD PROTOTYPES
void Serial_Initialise(void);
void Serial_Handler(void);
void Serial_SendByte(uint8_t bData);
uint8_t Serial_CalCRC(uint8_t *ptr, uint8_t count);


// EXTERN VARIABLES
extern Serial_STYP Serial;



#ifdef	__cplusplus
}
#endif

#endif	/* SERIAL_H */

