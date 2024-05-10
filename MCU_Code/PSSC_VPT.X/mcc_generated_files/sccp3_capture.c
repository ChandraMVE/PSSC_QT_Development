/**
  SCCP3 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    sccp3.c

  @Summary
    This is the generated driver implementation file for the SCCP3 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for SCCP3. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.166.0
        Device            :  dsPIC33CK128MP206
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.41
        MPLAB             :  MPLAB X v5.30
*/

/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "sccp3_capture.h"
#include "PistonEncoder.h"


void SCCP3_CAPTURE_Initialize(void)
{
    // CCPON enabled; MOD Edge Detect; CCSEL enabled; CCPSIDL disabled; TMR32 16 Bit; CCPSLP disabled; TMRPS 1:1; CLKSEL FOSC/2; TMRSYNC disabled; 
    CCP3CON1L = (0x8010 & 0x7FFF); //Disabling CCPON bit
    //RTRGEN disabled; ALTSYNC disabled; ONESHOT disabled; TRIGEN disabled; IOPS Each IC Event; SYNC None; OPSRC Timer Interrupt Event; 
    CCP3CON1H = 0x00;
    //ASDGM disabled; SSDG disabled; ASDG 0; PWMRSEN disabled; 
    CCP3CON2L = 0x00;
    //ICGSM Level-Sensitive mode; ICSEL IC3; AUXOUT Disabled; OCAEN disabled; OENSYNC disabled; 
    CCP3CON2H = 0x00;
    //OETRIG disabled; OSCNT None; POLACE disabled; PSSACE Tri-state; 
    CCP3CON3H = 0x00;
    //ICDIS disabled; SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; TRIG disabled; ICGARM disabled; TRCLR disabled; 
    CCP3STATL = 0x00;
    //TMR 0; 
    CCP3TMRL = 0x00;
    //TMR 0; 
    CCP3TMRH = 0x00;
    //PR 0; 
    CCP3PRL = 0x00;
    //PR 0; 
    CCP3PRH = 0x00;
    //CMP 0; 
    CCP3RAL = 0x00;
    //CMP 0; 
    CCP3RBL = 0x00;
    //BUF 0; 
    CCP3BUFL = 0x00;
    //BUF 0; 
    CCP3BUFH = 0x00;

    CCP3CON1Lbits.CCPON = 0x1; //Enabling CCP

    // Clearing IF flag before enabling the interrupt.
    IFS2bits.CCP3IF = 0;
    // Enabling SCCP3 interrupt.
    IEC2bits.CCP3IE = 1;

    // Clearing IF flag before enabling the interrupt.
    IFS2bits.CCT3IF = 0;
    // Enabling SCCP3 interrupt.
    IEC2bits.CCT3IE = 1;
}

void SCCP3_CAPTURE_Start( void )
{
    /* Start the Timer */
    CCP3CON1Lbits.CCPON = true;
}

void SCCP3_CAPTURE_Stop( void )
{
    /* Stop the Timer */
    CCP3CON1Lbits.CCPON = false;
}

void __attribute__ ((weak)) SCCP3_CAPTURE_CallBack(void)
{
    // Add your custom callback code here
    PistonEncoder_ISRFunctionA();
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _CCP3Interrupt ( void )
{
    /* Check if the Timer Interrupt/Status is set */
    if(IFS2bits.CCP3IF)
    {
		// SCCP3 CAPTURE callback function 
		SCCP3_CAPTURE_CallBack();
        
        IFS2bits.CCP3IF = 0;
    }
}

void __attribute__ ((weak)) SCCP3_CAPTURE_TimerCallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _CCT3Interrupt ( void )
{
    if(IFS2bits.CCT3IF)
    {
		// SCCP3 CAPTURE Timer callback function 
		SCCP3_CAPTURE_TimerCallBack();

        IFS2bits.CCT3IF = 0;
    }
}

uint16_t SCCP3_CAPTURE_Data16Read( void )
{
    /* Return the captured timer data */
    return(CCP3BUFL);

}


bool SCCP3_CAPTURE_HasBufferOverflowed( void )
{
    return( CCP3STATLbits.ICOV );
}

bool SCCP3_CAPTURE_IsBufferEmpty( void )
{
    return( ! CCP3STATLbits.ICBNE );
}

void SCCP3_CAPTURE_OverflowFlagReset( void )
{
    CCP3STATLbits.ICOV = 0;
}
/**
 End of File
*/