/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.166.0
        Device            :  dsPIC33CK128MP206
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.41
        MPLAB 	          :  MPLAB X v5.30
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
#include <stdio.h>
#include "pin_manager.h"

/**
 Section: Driver Interface Function Definitions
*/
void PIN_MANAGER_Initialize (void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;
    LATC = 0x0000;
    LATD = 0x0000;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x0007;
    TRISB = 0x337D;
    TRISC = 0x09B1;
    TRISD = 0x9F8F;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDA = 0x0000;
    CNPDB = 0x0000;
    CNPDC = 0x0000;
    CNPDD = 0x0000;
    CNPUA = 0x0000;
    CNPUB = 0x0000;
    CNPUC = 0x0000;
    CNPUD = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    ODCC = 0x0000;
    ODCD = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x0007;
    ANSELB = 0x0019;
    ANSELC = 0x0000;
    ANSELD = 0x0C00;
    
    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_RPCON(0x0000); // unlock PPS

    RPOR23bits.RP78R = 0x0001;    //RD14->UART1:U1TX
    RPINR6bits.ICM4R = 0x0042;    //RD2->SCCP4:ICM4
    RPOR19bits.RP70R = 0x0005;    //RD6->SPI1:SDO1
    RPINR20bits.SDI1R = 0x0047;    //RD7->SPI1:SDI1
    RPINR18bits.U1RXR = 0x004F;    //RD15->UART1:U1RX
    RPINR19bits.U2RXR = 0x0043;    //RD3->UART2:U2RX
    RPINR5bits.ICM3R = 0x002D;    //RB13->SCCP3:ICM3
    RPOR20bits.RP72R = 0x0006;    //RD8->SPI1:SCK1OUT
    RPINR20bits.SCK1R = 0x0048;    //RD8->SPI1:SCK1OUT
    RPOR18bits.RP68R = 0x0003;    //RD4->UART2:U2TX

    __builtin_write_RPCON(0x0800); // lock PPS
}

