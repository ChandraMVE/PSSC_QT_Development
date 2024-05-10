/**
 ******************************************************************************
 * @file       Error.c
 * @author     Dnyaneshwar 
 * @date       17 Mar 2021
 * @brief      This is a source file containing Errors for 
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
File name:    Error.c
                    
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
       17-03-2021  Initial Write                        Dnyaneshwar Pawar
--------------------------------------------------------------------------------
*/

#include "xc.h"
#include <stdbool.h>
#include "Error.h"
#include "../ShakerMotor/ShakerMotor.h"


static bool ErrorFlag_CycleRun;

Faults_UTYP Faults; 
        
/**
 * @brief This function initializes Error Variables
 * @param Nothing
 * @return Nothing
 */
void Error_Initialise(void)
{
    ErrorFlag_CycleRun = false;
    Error.Count = 0;
    Faults.FaultCodes = 0;
}

/**
 * @brief This function is called to add error into the errors list 
 * @param Nothing
 * @return Nothing
 */
void Error_Report(Errors_ETYP errorId)
{
//    uint8_t errorIndex = 0;

    if ( Error.Count < MAX_ERROR_BUFFER) 
    {
//        for (errorIndex = 0; errorIndex < Error.Count; errorIndex++) 
//        {
//            if(Error.LogARRY[errorIndex] == errorId) 
//            {
//                return;
//            }
//        }

        Error.LogARRY[Error.Count] = errorId;
        if((ShakerMotor_GetPulseErrCheck() == false) || (errorId != SHAKER_MOTOR))
        {
            Error.Count++;
        }
    }
    
    if(errorId > 1)
    {
        Faults.FaultCodes = Faults.FaultCodes | 1 << (errorId - 1);
    }
    else
    {
        Faults.FaultCodes = Faults.FaultCodes | errorId;
    }
    
    if ( Error.Count != NO_FAULTS)
    {
        // Set the error flag
        Error.Flags.Enable = true;
    }
}

/**
 * @brief This function is called to clear the error from the error list 
 * @param Nothing
 * @return Nothing
 */
void Error_Clear(Errors_ETYP errorId)
{
    uint8_t errorIndex = 0;

    if ((Error.Count != NO_FAULTS) && \
            (Error.Count < MAX_ERROR_BUFFER)) 
    {
        if ( Error.Flags.Enable == true) 
        {
            for ( errorIndex = 0; errorIndex < Error.Count; errorIndex++) 
            {
                if (Error.LogARRY[errorIndex] == errorId) 
                {
                    break;
                }
            }

            if ( errorIndex < Error.Count) 
            {
                Error.Count--;

                for ( ; errorIndex < Error.Count; errorIndex++) 
                {
                    Error.LogARRY[errorIndex] = Error.LogARRY[(errorIndex+1)];
                }
            }
            
            if(errorId > 1)
            {
                Faults.FaultCodes = Faults.FaultCodes & ~(1 << (errorId - 1));
            }
            else
            {
                Faults.FaultCodes = Faults.FaultCodes & ~(errorId);
            }

//            if ( Error.Count == NO_FAULTS)
//            {
//                // Clear the error flag
//                Error.Flags.Enable = false;
//            }
        }
        /*else
        {
            if(Error.Count != NO_FAULTS)
            {
                for ( errorIndex = 0; errorIndex < Error.Count; errorIndex++) 
                {
                    if (Error.LogARRY[errorIndex] == errorId) 
                    {
                        break;
                    }
                }

                if ( errorIndex < Error.Count) 
                {
                    Error.Count--;

                    for ( ; errorIndex < Error.Count; errorIndex++) 
                    {
                        Error.LogARRY[errorIndex] = Error.LogARRY[(errorIndex+1)];
                    }
                }
                if(errorId > 1)
                {
                    Faults.FaultCodes = Faults.FaultCodes & ~(1 << (errorId - 1));
                }
                else
                {
                    Faults.FaultCodes = Faults.FaultCodes & ~(errorId);
                }
            }
        }*/
    }
    else
    {
        Error.Flags.Enable = false;
//        Error.Count = NO_FAULTS;
    }
}

bool Error_GetFlag(void)
{
    return(Error.Flags.Enable);
}

void Error_SetFlag(bool flagSet)
{
    Error.Flags.Enable = flagSet;
    if(Error.Flags.Enable != true)
    {
        Error.Count = NO_FAULTS;
    }
}

uint8_t Error_GetCount(void)
{
    return(Error.Count);
}

/**
 * @brief This function is called by SOM to add or remove any error detected by SOM 
 * @param Nothing
 * @return Nothing
 */
void Error_UpdateStatus(bool flagSet, uint16_t ecode)
{
    if(flagSet)
    {
        Error.Flags.Enable = true;
        Faults.FaultCodes = Faults.FaultCodes | ecode;
    }
    else
    {
        if(!ecode)
        {
            Error.Flags.Enable = false;
            Faults.FaultCodes = 0;
            Error.Count = 0;
            ShakerMotor_SetPulseErrCheck(false);
        }
        else
        {
            Faults.FaultCodes = Faults.FaultCodes & ~(ecode);
        }
    }
}

uint16_t Error_GetFaultCount(void)
{
    return(Faults.FaultCodes);
}

/**
 * @brief This function is called from MCU debug window to add/clear any error
 * @param Nothing
 * @return Nothing
 */
void ErrorDebug_UpdateStatus(bool flagSet, uint16_t ecode)
{
    uint16_t tempChar;
//    uint16_t i = 1;
//    uint8_t pos = 1;
    
    tempChar = ecode;
    if(flagSet)
    {
        Error.Flags.Enable = true;
        Faults.FaultCodes = Faults.FaultCodes | tempChar;
        /*tempChar = ecode;
        // Iterate through bits of n till we find a set bit
        // i&n will be non-zero only when 'i' and 'n' have a set bit
        // at same position
        while (!(i & tempChar)) 
        {
            // Unset current bit and set the next bit in 'i'
            i = i << 1;
            // increment position
            ++pos;
        }
        Error_Report(pos);*/
    }
    else
    {
        Faults.FaultCodes = Faults.FaultCodes & ~(tempChar);
        if(!Faults.FaultCodes)
        {
            Error.Flags.Enable = true;
        }
//        Faults.FaultCodes = Faults.FaultCodes & ~(tempChar);
        /*tempChar = ecode;
        // Iterate through bits of n till we find a set bit
        // i&n will be non-zero only when 'i' and 'n' have a set bit
        // at same position
        while (!(i & tempChar)) 
        {
            // Unset current bit and set the next bit in 'i'
            i = i << 1;
            // increment position
            ++pos;
        }
        Error_Clear(pos);*/
    }
    
}

bool Error_GetCycleRunSts(void)
{
    return(ErrorFlag_CycleRun);
}

void Error_SetCycleRunSts(bool flagSet)
{
    ErrorFlag_CycleRun = flagSet;
}