/*
 * File:   main.c
 * Author: malterieck, alex
 *
 * Created on June 2, 2023, 2:32 PM
 */

#define ENABLE_BUZZER PORTC |= (1 << PC4)
#define DISABLE_BUZZER PORTC &= ~(1 << PC4)


#include <avr/io.h>


void initializeBuzzer() {
    DDRC |= (1 << PC4);         // Set Port C Pin 4 (PC4) as output (BUZZER)
}
