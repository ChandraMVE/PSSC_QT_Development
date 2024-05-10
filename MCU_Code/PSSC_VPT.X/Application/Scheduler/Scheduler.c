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

#include "Scheduler.h"

/**
 * @brief   This function is used to add the task to the scheduler. This function will
            receive the pointer of the function which have the task to be executed and the
            time to execute the task. The function pointer and the time interval are
            stored to the task array and the number of tasks are increased. If it unable
            to add the task, this function will return -1.
            This method should be called using scheduler.AddTask() method.
 * @param Taskptr       A pointer to the task instance which is added for scheduling 
 * @param initialDelayW Initial delay required for the task to execute
 * @param TimeW         The time duaration for the Added task
 * @return (0 == success)  (-1== failure)
 */

int32_t Scheduler_add_task(void (*Taskptr)(void), uint16_t initialDelayW, uint16_t TimeW)
{
  if ( scheduler.noOfTasks < SCHEDULER_MAX_TASKS) {
    // Store the task in the scheduler
    scheduler.scheduledTasks[scheduler.noOfTasks].counterW = initialDelayW;
    scheduler.scheduledTasks[scheduler.noOfTasks].scheduledTimeW = (TimeW - 1);
    scheduler.scheduledTasks[scheduler.noOfTasks].Taskptr = Taskptr;

    // Increment the No.of tasks listed in the scheduler
    scheduler.noOfTasks++;

    // Return Success
    return 0;
  }

  // Return Error
  return -1;
}

/**
 * @brief   Main Monitors the interruptFLG in Scheduler_STYP continuously. Whenever it
            found that bit as '1' i.e 1 ms tick occurs, it will call the Scheduler.run()
            to execute the scheduled tasks. Scheduler have task pointer and the counter to
            execute the task when it expires. For each ticks the counter gets decremented,
            and when it reaches zero scheduler executes the task and reload the counter.
            In this way it will execute all the tasks scheduled whenever tick is getting
            triggered.

            This method should be called using scheduler.run() method.
 */
void Scheduler_run(void)
{
  uint8_t Tasks_index = 0;

  for( Tasks_index = 0; Tasks_index < scheduler.noOfTasks; Tasks_index++)
  {
    // If Counter is non zero, decrement it and go to check next task
    if(scheduler.scheduledTasks[Tasks_index].counterW) 
    {
        scheduler.scheduledTasks[Tasks_index].counterW--;
    }
    else
    {
        // When Counter is zero, Execute the task and reload it with backup time
        scheduler.scheduledTasks[Tasks_index].Taskptr();
        scheduler.scheduledTasks[Tasks_index].counterW =              \
        scheduler.scheduledTasks[Tasks_index].scheduledTimeW;
    }            
  }
}
