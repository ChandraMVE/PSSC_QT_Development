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
File name:    Scheduler.h
                    
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

  int32_t Scheduler_add_task(void (*Taskptr)(void), uint32_t TimeW);
    To add the task and time interval into the scheduler 

Resources:
  None

================================================================================
 History:	
-*-----*-----------*------------------------------------*-----------------------
       10-12-2019  Initial Write                        Dnyaneshwar Pawar
--------------------------------------------------------------------------------
*/

#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_


#include <stdint.h>

#define SCHEDULER_MAX_TASKS         10 // Maximum tasks can be scheduled.

/**
 * @brief This structure is Used for scheduling mechanism
 */
typedef struct {  

//  Public Variables
  struct {
    // INPUT:Set by Timer ISR every 1 ms to let main() know to call Scheduler.run()
    uint8_t interruptFLG:1;
  } flags;
  // OUTPUT: No of tasks scheduled in the scheduler
  uint8_t noOfTasks;
  struct {
    // INPUT: The counter which will be down counted after each ticks
    uint16_t counterW;
    // INPUT: Time interval to execute the task
    uint16_t scheduledTimeW;
    // INPUT: The pointer of the function which have to be executed
    void (* Taskptr)(void);
    
  }scheduledTasks[SCHEDULER_MAX_TASKS];

// Public Methods
  void (* run)(void);
  int32_t (* AddTask)(void (*Taskptr)(void), uint16_t initialDelayW, uint16_t TimeW);
} Scheduler_STYP;


//  CLASS METHOD PROTOTYPES
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
void Scheduler_run(void);

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
int32_t Scheduler_add_task(void (*Taskptr)(void), uint16_t initialDelayW, uint16_t TimeW);


// DEFINE CLASS OBJECT DEFAULTS
#define SCHEDULER_DEFAULTS {        \
  .run      = &Scheduler_run,       \
  .AddTask  = &Scheduler_add_task   \
}

// OTHER DEFINITIONS

//Scheduler tasks interval time in milliseconds
#define ADC_READ_INTERVAL               25/**< ADC read interval.*/
#define PISTON_MOTOR_INTERVAL           50/**< Piston Motor interval.*/
#define VALVE_MOTOR_INTERVAL            100/**< Valve Motor interval.*/
#define SHAKER_MOTOR_INTERVAL           150/**< Shaker Motor interval.*/
#define TEC_CONTROL_INTERVAL            250/**< Valve Motor interval.*/
#define SERIAL_INTERVAL                 5/**< UART Serial communication interval.*/
#define TEMPERATURE_CONTROL_INTERVAL    25/**< ADS8694 read interval.*/
#define PISTON_ENCODER_INTERVAL         50/**< The interval to check Pulses of Piston Encoder Interval.*/
#define ALARM_INTERVAL                  500/**< The interval to check Alarm working Interval.*/
#define SERIAL_DEBUG_INTERVAL           5/**< UART2 Serial debug interval.*/

//Scheduler tasks initial interval time in milliseconds to avoid tasks triggered on same time
#define ADC_READ_INITIAL_DELAY              100/**< ADC task initial delay.*/
#define PISTON_MOTOR_INITIAL_DELAY          500/**< Piston PWM task initial delay.*/
#define VALVE_MOTOR_INITIAL_DELAY           30/**< Valve PWM task initial delay.*/
#define SHAKER_MOTOR_INITIAL_DELAY          150/**< Shaker PWM task initial delay.*/
#define TEC_CONTROL_INITIAL_DELAY           1000/**< Valve PWM task initial delay.*/
#define SERIAL_INITIAL_DELAY                80/**< UART task initial delay.*/
#define TEMPERATURE_CONTROL_INITIAL_DELAY   200/**< ADS8694 calling initial delay.*/
#define PISTON_ENCODER_INITIAL_DELAY        500/**< Piston Encoder initial delay.*/
#define ALARM_INITIAL_DELAY                 250/**< Alarm Control initial delay.*/
#define SERIAL_DEBUG_INITIAL_DELAY          82/**< UART2 task initial delay.*/

// EXTERN VARIABLES
extern Scheduler_STYP scheduler;/**< The structure instance to the scheduler.*/


#endif /*_SCHEDULER_H_*/

