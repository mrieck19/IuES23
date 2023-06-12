/* 
 * File:   buzzer.h
 * Author: malterieck
 *
 * Created on June 11, 2023, 3:42 PM
 */

#ifndef BUZZER_H
#define	BUZZER_H

#define ENABLE_BUZZER PORTC |= (1 << PC4)
#define DISABLE_BUZZER PORTC &= ~(1 << PC4)


extern void initializeBuzzer();

#endif


