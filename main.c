/*
 * File:   main.c
 * Author: malterieck, alex
 *
 * Created on June 2, 2023, 2:32 PM
 */

#define F_CPU 16000000UL
#define BUTTON_PRESS (PIND & (1<<PIND1))
#define ENABLE_BUZZER PORTC |= (1 << PC4)
#define DISABLE_BUZZER PORTC &= ~(1 << PC4)
#define RESET_TIMER1 TCNT1 = 49910
#define RESET_TIMER1_PRESCALER TCCR1B |= (1 << CS12) | (1 << CS10)

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow_counter = 0;

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
    if (BUTTON_PRESS) {
        
        ENABLE_BUZZER;          // Enable the Buzzer
        
        RESET_TIMER1;
        
        RESET_TIMER1_PRESCALER;
        
    }
}

void initializeButton() {
    DDRD &= ~(1 << PD1);        // Set PD1 as input pin (Button)
    PORTD |= (1 << PD1);        // Enable pull-up resistor on PD1
    // Enable PCINT17 interrupt on Port D
    PCICR |= (1 << PCIE2);      // Enable Pin Change Interrupt of PCIE2 (PCINT23..16)
    PCMSK2 |= (1 << PCINT17);   // Enable PCINT17 (PD1) Interrupt in Mask Register
}

void initializeBuzzer() {
    DDRC |= (1 << PC4);         // Set Port C Pin 4 (PC4) as output (BUZZER)
}

void initializeTimer1() {
    TIMSK1 |= (1 << TOIE1);     // Enable Timer/Counter1 Overflow Interrupt
    RESET_TIMER1;             // Set initial value of Timer1, creates interrupt every 1s

    sei(); // Enable global interrupts
}

int main() {
    
    // Initialize Functions
    initializeTimer1();
    initializeButton();
    initializeBuzzer();

    while (1) {

    }
}