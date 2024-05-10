/* 
 * File:   main.h
 * Author: dnyaneshwar.pawar
 *
 * Created on 16 December, 2020, 5:12 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "mcc_generated_files/watchdog.h"
#include "mcc_generated_files/tmr1.h"

#ifdef	__cplusplus
extern "C" {
#endif

// MACROS USED FOR WATCHDOG
// To start the watchdog
#define START_WATCHDOG()                    WATCHDOG_TimerSoftwareEnable()


// To reset the watchdog
#define RESET_WATCHDOG()                    WATCHDOG_TimerClear()
  


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

