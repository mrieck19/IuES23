/*
 * File:   main.c
 * Author: malterieck, alex
 *
 * Created on June 2, 2023, 2:32 PM
 */

#define BUTTON_PRESS (PIND & (1<<PIND1))




#include <avr/io.h>

void initializeButton() {
    DDRD &= ~(1 << PD1);        // Set PD1 as input pin (Button)
    PORTD |= (1 << PD1);        // Enable pull-up resistor on PD1
    // Enable PCINT17 interrupt on Port D
    PCICR |= (1 << PCIE2);      // Enable Pin Change Interrupt of PCIE2 (PCINT23..16)
    PCMSK2 |= (1 << PCINT17);   // Enable PCINT17 (PD1) Interrupt in Mask Register
}



