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
   
    DISABLE_BUZZER;  // Disable the LED on Port C4
    
    TCCR1B &= ~(1 << CS12) & ~(1 << CS10); // Clear prescaler
}

ISR(PCINT2_vect)
{
    // Check if the button on PD1 is pressed
    if (PIND & (1 << PD1)) {
        ENABLE_BUZZER;  // Enable the Buzzer
        resetTimer1();  // Reset the timer/counter1
    }
}

void initializeButton(){
    DDRD &= ~(1 << PD1);  // Set PB7 as input pin (Button)
    PORTD |= (1 << PD1);  // Enable pull-up resistor on PB7
    // Enable PCINT17 interrupt on Port D
    PCICR |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT17);
    sei();
}

/*void initializeButton(){
    DDRD &= ~(1 << PD1);  // Set PB7 as input pin (Button)
    
    PORTD |= (1 << PD1);  // Enable pull-up resistor on PB7
}*/

void initializeBuzzer(){
    DDRC |= (1 << PC4);  // Set Port C Pin 4 (PC4) as output (BUZZER)
}


void initializeTimer1(){
    TIMSK1 |= (1 << TOIE1); // Enable Timer/Counter1 Overflow Interrupt

    TCNT1 = 0; // Set initial value of Timer/Counter1
    
    sei(); // Enable global interrupts
}

void resetTimer1(){
     
    TCNT1 = 0;  // Reset the Timer/Counter1
    
    TCCR1B |= (1 << CS12) | (1 << CS10); // Reset prescaler to 1024
}

int main() {
    
    // Initialize Functions
    initializeTimer1();
    initializeButton();
    initializeBuzzer();

    while (1) {
        
        /*if (BUTTON_PRESS) { // Check if the button is pressed
            
            ENABLE_BUZZER;  // Enable the Buzzer
           
            resetTimer1();  // Reset the timer/counter1
        }*/
    }
}