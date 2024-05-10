/* 
 * File:   Events.h
 * Author: dnyaneshwar.pawar
 *
 * Created on 16 December, 2020, 8:12 PM
 */

#ifndef EVENTS_H
#define	EVENTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
void Events_Initialise(void);
void Events_SetTecFan(bool setFlag);

#ifdef	__cplusplus
}
#endif

#endif	/* EVENTS_H */

