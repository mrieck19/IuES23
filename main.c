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
//#include "tft.h"
#include "spi.h"

volatile uint8_t overflow_counter = 0;


    const char* myText = "Hello, World!";
    U8 startX = 10;
    U8 startY = 20;
    U8 scale = 0.5;
    U16 textColor = 0x0000;       // White color
    U16 backgroundColor = 0xFFFF; // Black color
    U8 displayOrientation = 1; 
    
int main() {
    
    // Initialize Functions
    initializeTimer1();
    initializeButton();
    initializeBuzzer();
    

      
    sei();
    
    while (1) {

    }
}
/*
int initialiseDisplay() {

    SPI_init();
    TFT_init();
}
*/
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
        //void TFT_Print(char* myText,U8 startX,U8 startY,U8 scale,U16 textColor,U16 backgroundColor,U8 displayOrientation); 
        ENABLE_BUZZER;          // Enable the Buzzer
        
        RESET_TIMER1;
        
        RESET_TIMER1_PRESCALER;
        
    }
}



