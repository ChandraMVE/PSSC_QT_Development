/* 
 * File:   ADCRead.h
 * Author: dnyaneshwar.pawar
 *
 * Created on February 10, 2021, 7:23 PM
 */

#ifndef ADCREAD_H
#define	ADCREAD_H

#ifdef	__cplusplus
extern "C" {
#endif

// Enums for ADC conversion status
typedef enum {
  ADC_CONV_START = 0,
  ADC_CONV_SAMPLING_START,
  ADC_CONV_SAMPLING_END,
  ADC_CONV_READ_DATA
}ADCState_ETYP;

typedef enum {
    AMB_TEMP = 0,
    SPARE,
    ADC_PIST_MTR_C_FB,
    ADC_VAL_MTR_C_FB,
}ADC1Channel_ETYP;

#define TOTAL_ADC_CHANNELS      4
#define MAX_BUFFSIZE            10

//CLASS OBJECT DEFINITION
typedef struct {
//  Public Variables
    struct {
      uint8_t PistMtr_En:1;
      uint8_t ValMtr_En:1;
      uint8_t AmbTemp_En:1;
      uint8_t Buffer_Ready:1;
      uint8_t Power_DataReady:1;
    }Flags;
    uint16_t ADCResultARRY[TOTAL_ADC_CHANNELS];
//  Public Methods
    void (*HandlerFunction)(void);          // The read function used periodically

//  Private Variables
    ADCState_ETYP ADCStatus;                // ADC Conversion status
} ADCRead_STYP;


// DEFINE CLASS OBJECT DEFAULTS

#define ADC_READ_DEFAULTS {                                 \
                            {0,0,0,0,0},                      \
                            {0,0,0,0},                      \
                            &ADCRead_Handler,               \
                            ADC_CONV_START                  \
                          }


// OTHER DEFINITIONS

// ADC Array index 
//#define AMB_TEMP                0
//#define SPARE                   1
//#define ADC_PIST_MTR_C_FB       2
//#define ADC_VAL_MTR_C_FB        3

//  CLASS METHOD PROTOTYPES
void ADCRead_Initialise(void);
void ADCRead_Handler(void);
void ADCRead_AverageFilter(uint16_t *arryPTR, uint16_t rawData);
uint16_t ADCRead_GetPistFb(void);
uint16_t ADCRead_GetValFb(void);
uint16_t ADCRead_GetAmbTemp(void);


// EXTERN VARIABLES
extern ADCRead_STYP ADCRead;


#ifdef	__cplusplus
}
#endif

#endif	/* ADCREAD_H */

