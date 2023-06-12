/* 
 * File:   timer1.h
 * Author: malterieck
 *
 * Created on June 11, 2023, 3:50 PM
 */

#ifndef TIMER1_H
#define	TIMER1_H

#define RESET_TIMER1 TCNT1 = 49910
#define RESET_TIMER1_PRESCALER TCCR1B |= (1 << CS12) | (1 << CS10)

extern void initializeTimer1();



#endif	/* TIMER1_H */

