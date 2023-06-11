/*
 * File:   main.c
 * Author: malterieck, alex
 *
 * Created on June 2, 2023, 2:32 PM
 */

#define F_CPU 16000000UL
#define RESET_TIMER1 TCNT1 = 49910
#define RESET_TIMER1_PRESCALER TCCR1B |= (1 << CS12) | (1 << CS10)

#include <avr/io.h>



void initializeTimer1() {
    TIMSK1 |= (1 << TOIE1);     // Enable Timer/Counter1 Overflow Interrupt
    RESET_TIMER1;             // Set initial value of Timer1, creates interrupt every 1s


}

