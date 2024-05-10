/* 
 * File:   Timers.h
 * Author: dnyaneshwar.pawar
 *
 * Created on 16 December, 2020, 8:18 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

#ifdef	__cplusplus
extern "C" {
#endif



    
inline void Timers_Initialise(void);
void Timers_ISRFunction(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMERS_H */

