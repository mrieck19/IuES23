/*
 * File:   main.c
 * Author: malterieck, alex
 *
 * Created on June 2, 2023, 2:32 PM
 */

#define F_CPU 16000000UL

//#define BUTTON_PRESS (PIND & (1<<PIND1))
/*
#define ENABLE_BUZZER PORTC |= (1 << PC4)
#define DISABLE_BUZZER PORTC &= ~(1 << PC4)
#define RESET_TIMER1 TCNT1 = 49910
#define RESET_TIMER1_PRESCALER TCCR1B |= (1 << CS12) | (1 << CS10)
*/
#include <avr/io.h>
#include <avr/interrupt.h>

#include "dht11.h"
#include "timer1.h"
#include "buzzer1.h"
#include "button.h"

volatile uint8_t overflow_counter = 0;

int main() {
    
    // Initialize Functions
    initializeTimer1();
    initializeButton();
    initializeBuzzer();
    sei();
    
    
    while (1) {

    }
}

// Interrupt Service Routine for Timer/Counter1 Overflow
ISR(TIMER1_OVF_vect) {

    // Increment overflow counter
    overflow_counter++;
    
    // If 5 seconds (interrupts)
    if (overflow_counter >= 5){
        DISABLE_BUZZER;         // Disable the LED on Port C4
    
        TCCR1B &= ~(1 << CS12) & ~(1 << CS10); // Clear prescaler
        
        overflow_counter = 0;   // Reset overflow counter
    }
    
    RESET_TIMER1; 
}

// Interrupt Service Routine for PCINT17 (PD1)
ISR(PCINT2_vect) {
    // Check if the button on PD1 is pressed
    if (BUTTON_PRESS){
        
        ENABLE_BUZZER;          // Enable the Buzzer
        
        RESET_TIMER1;
        
        RESET_TIMER1_PRESCALER;
        
    }
}

