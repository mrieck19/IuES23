/*
 * File:   main.c
 * Author: malterieck, alex
 *
 * Created on June 2, 2023, 2:32 PM
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#include "dht11.h"
#include "timer1.h"
#include "buzzer1.h"
#include "button.h"
//#include "tft.h"
#include "spi.h"

int main() {
    
    // Initialize Functions
    initializeTimer1();
    initializeButton();
    initializeBuzzer();
    
    sei();                                      // Enable Global Interrupts
    
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
volatile uint8_t overflow_counter = 0;
ISR(TIMER1_OVF_vect) {

    // Increment overflow counter
    overflow_counter++;
    
    // If 5 seconds (interrupts)
    if (overflow_counter >= 5){
        DISABLE_BUZZER;                         // Disable the BUZZER on Port C4
    
        TCCR1B &= ~(1 << CS12) & ~(1 << CS10);  // Clear prescaler
        
        overflow_counter = 0;                   // Reset overflow counter
    }
    
    RESET_TIMER1; 
}

// Interrupt Service Routine for PCINT1 (PB1)
ISR(PCINT0_vect) {
    // Check if the button on PD1 is pressed
    if (BUTTON_PRESS){
        //void TFT_Print(char* myText,U8 startX,U8 startY,U8 scale,U16 textColor,U16 backgroundColor,U8 displayOrientation); 
        ENABLE_BUZZER;                          // Enable the Buzzer
        
        RESET_TIMER1;
        
        RESET_TIMER1_PRESCALER;
    }
}



