/*
 * File:   main.c
 * Author: malterieck, alex
 *
 * Created on June 2, 2023, 2:32 PM
 */

#include <avr/io.h>
#include <avr/interrupt.h>

void initializeButton() {
    DDRB &= ~(1 << PB1);        // Set PB1 as input pin (Button)
    PORTB |= (1 << PB1);        // Enable pull-up resistor on PB1
    // Enable PCINT17 interrupt on Port B
    PCICR |= (1 << PCIE0);      // Enable Pin Change Interrupt of PCIE0 (PCINT7..0)
    PCMSK0 |= (1 << PCINT1);    // Enable PCINT17 (PD1) Interrupt in Mask Register
}



