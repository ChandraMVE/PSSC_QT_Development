/* 
 * File:   PistonEncoder.h
 * Author: dnyaneshwar.pawar
 *
 * Created on January 22, 2021, 11:15 AM
 */

#ifndef PISTONENCODER_H
#define	PISTONENCODER_H

#ifdef	__cplusplus
extern "C" {
#endif


// Enums for UART serial debug status
typedef enum {
  PISTONENCODER_STATE_IDLE = 0,
  PISTONENCODER_STATE_RUNNING,
  PISTONENCODER_STATE_STOP,
  PISTONENCODER_STATE_ERROR,
}PistonEncoderState_ETYP;

//CLASS OBJECT DEFINITION

typedef struct {

//  Public Variables
struct {
    // The Enable Flag for Piston Encoder for start of reading 0-OFF 1-ON
    uint8_t EnPE:1;
    // To check pulses count are received properly 0-No 1-Yes
    uint8_t EditedPE:1;
    // To turn OFF the display while flashing 0-OFF 1-ON
    uint8_t ErrorPE:1;
    //
    uint8_t InitialPosition:1;
  } Flags;

// Public Methods
    void (*HandlerFunction)(void);

// Private Variables
    PistonEncoderState_ETYP PEState_Status;
    uint16_t Pulse_Count;

} PISTONENCODER_STYP;

// DEFINE CLASS OBJECT DEFAULTS

#define PISTONENCODER_DEFAULTS     {                                \
                                {0,0,0,0},                            \
                                &PistonEncoder_Handler,             \
                                PISTONENCODER_STATE_IDLE,           \
                                0                                   \
                            }    
    
#define MAX_INITIAL_PERIOD      800     // 50ms * 800 = 40 secs   
#define MIN_ENCODER_PULSES      500     // 1 rev for each encoder = 448
#define MAX_PULSE_TIME          400     // 50ms*200 = 10 secs

void PistonEncoder_Initialise(void);
void PistonEncoder_Handler(void);
void PistonEncoder_StartRead(void);
void PistonEncoder_StopRead(void);
void PistonEncoder_ISRFunctionA(void);
void PistonEncoder_ISRFunctionB(void);
uint32_t PistonEncoder_GetCountA(void);
uint32_t PistonEncoder_GetCountB(void);
void PistonEncoder_CheckInitialPosition(void);
bool PistonEncoder_GetInitialPosition(void);
void PistonEncoder_SetEnableFlag(bool flagSet);
bool PistonEncoder_GetEnableFlag(void);
void PistonEncoder_SetErrorFlag(bool flagSet);
bool PistonEncoder_GetErrorFlag(void);
uint16_t PistonEncoder_GetCounter(void);
void PistonEncoder_ClearCountFirstCount(void);
int PistonEncoder_FirstEncoder(void);
void PistonEncoder_ExpectedCount(bool directionFlag,uint32_t);
bool ReturnPistonMotor_StopFlag();
void SetPistonMotor_StopFlag(bool flagSet);
bool PistonMotor_InitialiseToZero(void);
void PistonMotor_SetInitialisedToZero(bool zeroPositionFlag);
bool PistonMotor_UpOrDown(void);

// EXTERN VARIABLES
extern PISTONENCODER_STYP PistonEncoder;


#ifdef	__cplusplus
}
#endif

#endif	/* PISTONENCODER_H */

