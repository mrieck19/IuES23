/*
 * File:   main.c
 * Author: malterieck
 *
 * Created on June 2, 2023, 2:32 PM
 */


#define F_CPU 16000000UL
#define BUTTON_PRESS (! (PIND & (1<<PIND1)))


#include <avr/io.h>
#include <avr/interrupt.h>

// Interrupt Service Routine for Timer/Counter1 Overflow
ISR(TIMER1_OVF_vect) {
    // Disable the LED on Port C4
    PORTC &= ~(1 << PC4);
   
  
}

void init(void){
    // Set Port C Pin 4 (PC4) as output (BUZZER)
    DDRC |= (1 << PC4);
    
    DDRD &= ~(1 << PD1);  // Set PB7 as input pin (Button)
    PORTD |= (1 << PD1);  // Enable pull-up resistor on PB7
  
    TCCR1A = 0;  
    // Set Timer/Counter Control Register A (TCCR1A) and Timer/Counter Control Register B (TCCR1B)
    // to configure the timer
    TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024

    // Enable Timer/Counter1 Overflow Interrupt
    TIMSK1 |= (1 << TOIE1);

    // Set initial value of Timer/Counter1
    TCNT1 = 0;
    
    // Enable global interrupts
    sei();
}

int main() {
    // Initialize the ports
    init();

    while (1) {
        // Check if the button on PC1 is pressed
        if (BUTTON_PRESS) {
            // Enable the LED on PC4
            PORTC |= (1 << PC4);

            // Reset the Timer/Counter1
            TCNT1 = 0;
        }
    }
}