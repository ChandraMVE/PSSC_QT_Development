/**
 ******************************************************************************
 * @file       Scheduler.c
 * @author1    Dnyaneshwar Pawar
 * @date       10 Dec 2020
 * @brief      This is a source file which contains scheduling algorithm for
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
File name:    Scheduler.c
                    
Originator:   Dnyaneshwar Pawar

Platform:     dsPIC33CK128MP206
Compiler:     XC16 V1.35
IDE     :     MPLAB X IDE V5.20

Description: 
  This is a supervisory object called from Main() when 1ms interrupt sets a flag
  to run the scheduler.   It calls all the time based functions and handles all
  fault and events generated in class level objects.

  Whenever interrupt occurs it will down count the counter for each task and
  when it expired, scheduler execute the task and reloads the counter.

Class Methods:
  void Scheduler_run(void);
    Execute the tasks scheduled whenever timer interrupt occurs

  int32_t Scheduler_add_task(void (*Taskptr)(void), uint16_t initialDelayW,
  uint16_t TimeW);
    To add the task in the scheduler 

Resources:
  None

================================================================================
 History:	
-*-----*-----------*------------------------------------*-----------------------
       10-12-2019  Initial Write                        Dnyaneshwar Pawar
--------------------------------------------------------------------------------
*/

//#include "main.h"
#include "mcc_generated_files/tmr1.h"
#include "Timers.h"
#include "Scheduler.h"

/**
 * @brief   This function is used to initialise the Timers.
 * @param None 
 * @param 
 * @return None
 */

void Timers_Initialise(void)
{
  // Timer to schedule the tasks
  TMR1_SetInterruptHandler(&Timers_ISRFunction);
  TMR1_Start();

}

/*
================================================================================
Method name:  TimersISRFunction

Description: 
  To handle the Timer interrupt. In this interrupt service
  routine it will make interrupt flag as high.


================================================================================

*/

void Timers_ISRFunction(void)
{
  // Set the interrupt flag to execute the scheduler
  scheduler.flags.interruptFLG = 1;
  
}
