/* 
 * File:   Error.h
 * Author: dnyaneshwar.pawar
 *
 * Created on 17 March, 2021, 8:20 PM
 */

#ifndef ERROR_H
#define	ERROR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>

#define MAX_ERROR_BUFFER        5

// Enums for errors
typedef enum {
    NO_ERROR = 0,
    PISTON_MOTOR,
    PISTON_ENCODER,
    PRESSURE_LIMIT,
    AMBIENT_LIMIT,
    TEC_FAILURE,
    VALVE_MOTOR,
    VALVE_SWITCH,
    PRESSURE_SENS_FAIL,
    SHAKER_MOTOR,
    PISTON_INITIAL,
    SHAKER_INITIAL        
}Errors_ETYP;

typedef union {
    struct {
        uint16_t TIMEOUT:1;
        uint16_t NOTUSE:6;
        uint16_t ShkrMtr:1;
        uint16_t PressSns:1;
        uint16_t ValSwt:1;
        uint16_t ValMtr:1;
        uint16_t TECMdl:1;
        uint16_t AmbLmt:1;
        uint16_t PressLmt:1;
        uint16_t PistEnc:1;
        uint16_t PistMtr:1;
    }bitFlags;       
    uint16_t FaultCodes;
}Faults_UTYP;

//CLASS OBJECT DEFINITION
typedef struct { 

//  Public Variables
  struct {
    // 1-Enable 0-Disable
    uint8_t Enable : 1;
  }Flags;
  uint8_t Count;
  uint8_t LogARRY[5];

// Public Methods


//  Private Variables

} Error_STYP;

// DEFINE CLASS OBJECT DEFAULTS
#define ERROR_DEFAULTS  {                                   \
                                    {0},                    \
                                    0,                      \
                                    {0,0,0,0,0},            \
                        }

#define NO_FAULTS                   0

//  CLASS METHOD PROTOTYPES
void Error_Initialise(void);
void Error_Report(Errors_ETYP errorId);
void Error_Clear(Errors_ETYP errorId);
bool Error_GetFlag(void);
void Error_SetFlag(bool flagSet);
uint8_t Error_GetCount(void);
uint16_t Error_GetFaultCount(void);
void Error_UpdateStatus(bool flagSet, uint16_t ecode);
void ErrorDebug_UpdateStatus(bool flagSet, uint16_t ecode);
bool Error_GetCycleRunSts(void);
void Error_SetCycleRunSts(bool flagSet);
void Error_PressureOverLoad(void);
void Error_PressureOverLoadVariableReset(void);
bool Error_PressureOverLoadVariable(void);
void Error_PressurePiston(void);
bool Error_PressurePistonVariable(void);

// EXTERN VARIABLES
extern Error_STYP Error;



#ifdef	__cplusplus
}
#endif

#endif	/* ERROR_H */

