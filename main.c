/*
 * File:   main.c
 * Author: malterieck
 *
 * Created on June 2, 2023, 2:32 PM
 */


#define F_CPU 16000000UL
#define BUTTON_PRESS (! (PIND & (1<<PIND1)))
#define ENABLE_BUZZER PORTC |= (1 << PC4)
#define DISABLE_BUZZER PORTC &= ~(1 << PC4)


#include <avr/io.h>
#include <avr/interrupt.h>

// Interrupt Service Routine for Timer/Counter1 Overflow
ISR(TIMER1_OVF_vect) {
    // Disable the LED on Port C4
    DISABLE_BUZZER;
    
    //Global Interrupt disable
    cli();
}

void initializeButton(){
    DDRD &= ~(1 << PD1);  // Set PB7 as input pin (Button)
    PORTD |= (1 << PD1);  // Enable pull-up resistor on PB7
}

void initializeBuzzer(){
    DDRC |= (1 << PC4);  // Set Port C Pin 4 (PC4) as output (BUZZER)
}



void initializeTimer1(){
    // Set Timer/Counter Control Register A (TCCR1B) and Timer/Counter Control Register B (TCCR1B)
    // to configure the timer
    TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024

    // Enable Timer/Counter1 Overflow Interrupt
    TIMSK1 |= (1 << TOIE1);

    // Set initial value of Timer/Counter1
    TCNT1 = 0;
    
    
}

void resetTimer1(){
     // Reset the Timer/Counter1
            TCNT1 = 0;
     // Enable global interrupts
            sei();       
}

int main() {
    // Initialize the ports
    initializeTimer1();
    initializeButton();
    initializeBuzzer();

    while (1) {
        // Check if the button on PC1 is pressed
        if (BUTTON_PRESS) {
            // Enable the LED on PC4
            ENABLE_BUZZER;
           
            resetTimer1();
        }
    }
}