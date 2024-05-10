
/**
 ******************************************************************************
 * @file       Events.c
 * @author     Dnyaneshwar 
 * @date       16 Dec 2020
 * @brief      This is a source file containing controls for driving loads of
 *             PSSC VPT 
 ******************************************************************************
 * Redistribution in source and binary forms, with or without modification,
 * are not permitted. Use in source code needs the written approval of the author.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************
 */

/*
================================================================================
File name:    Events.c
                    
Originator:   Dnyaneshwar Pawar

Platform:     dsPIC33CK128MP206
Compiler:     XC16 V1.60
IDE     :     MPLAB X IDE V5.20

Description: 
  


Class Methods:
  
    

Resources:
  None

================================================================================
 History:	
-*-----*-----------*------------------------------------*-----------------------
       16-12-2020  Initial Write                        Dnyaneshwar Pawar
--------------------------------------------------------------------------------
*/


#include "xc.h"
#include <stdbool.h>
#include "Events.h"
#include "mcc_generated_files/pin_manager.h"

/**
 * @brief This function turn ON the Enclosure and TEC fan in Initialization 
 * @param Nothing
 * @return Nothing
 */
void Events_Initialise(void)
{
    FAN_TEC_SetDigitalOutput();
    FAN_ENCL_SetDigitalOutput();

    FAN_TEC_SetHigh();
    FAN_ENCL_SetHigh();

}

void Events_SetTecFan(bool setFlag)
{
    if(setFlag == true)
    {
        FAN_TEC_SetHigh();
    }
    else
    {
        FAN_TEC_SetLow();
    }
}