/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the generated driver implementation file for setting up the
    interrupts using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This source file provides implementations for PIC24 / dsPIC33 / PIC32MM MCUs interrupts.
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
    Section: Includes
*/
#include <xc.h>

/**
    void INTERRUPT_Initialize (void)
*/
void INTERRUPT_Initialize (void)
{
    //    CCPI: CCP4 Capture/Compare Event
    //    Priority: 1
        IPC10bits.CCP4IP = 1;
    //    CCTI: CCP4 Timer Event
    //    Priority: 1
        IPC10bits.CCT4IP = 1;
    //    CCPI: CCP3 Capture/Compare Event
    //    Priority: 1
        IPC8bits.CCP3IP = 1;
    //    CCTI: CCP3 Timer Event
    //    Priority: 1
        IPC9bits.CCT3IP = 1;
    //    UEVTI: UART2 Event
    //    Priority: 1
        IPC47bits.U2EVTIP = 1;
    //    UTXI: UART2 TX
    //    Priority: 1
        IPC7bits.U2TXIP = 1;
    //    UEI: UART2 Error
    //    Priority: 1
        IPC12bits.U2EIP = 1;
    //    URXI: UART2 RX
    //    Priority: 1
        IPC6bits.U2RXIP = 1;
    //    UEVTI: UART1 Event
    //    Priority: 1
        IPC47bits.U1EVTIP = 1;
    //    UTXI: UART1 TX
    //    Priority: 1
        IPC3bits.U1TXIP = 1;
    //    UEI: UART1 Error
    //    Priority: 1
        IPC12bits.U1EIP = 1;
    //    URXI: UART1 RX
    //    Priority: 1
        IPC2bits.U1RXIP = 1;
    //    TI: Timer 1
    //    Priority: 1
        IPC0bits.T1IP = 1;
}
