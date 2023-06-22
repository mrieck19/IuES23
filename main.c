/*
 * File:   main.c
 * Author: malterieck, alex
 *
 * Created on June 2, 2023, 2:32 PM
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dht11.h"
#include "timer1.h"
#include "buzzer1.h"
#include "button.h"
#include "tft.h"
#include "spi.h"
#include "uart.h"

void resetDisplay() {
    uint16_t x = 0;
    
    // Reset Background to White
    for (x = 0; x < 23232; x++) {
        SPISend8Bit(0xFF);
        SPISend8Bit(0xFF);
    } 
}


int main() {

    // Initialize Functions
    initializeTimer1();
    initializeButton();
    initializeBuzzer();
    initializeDHT11();
    initializeUART();
    SPI_init();
    Display_init();

    resetDisplay();

    sei();                                      // Enable Global Interrupts

    uint8_t humidity, temperature;
    uint8_t last_mqtt_window_status = 0;

    while (1) {
        
        // Send DHT11 Data to MQTT
        char tempOut[25];
        dht11_getData(&humidity, &temperature);
        sprintf(tempOut, ">DHT%d.0:%d.0<", temperature, humidity);
        sendStringUART(tempOut);
        
        _delay_ms(5000);
        
        // Send switch Status to MQTT
        if (BUTTON_PRESS) {
            // Window Closed (0)
            if (last_mqtt_window_status == 1) {
                sendStringUART(">BTN0<");
            }

            last_mqtt_window_status = 0;
        }
        else
        {
            // Window Open (1)
            if (last_mqtt_window_status == 0) {
                sendStringUART(">BTN1<");
            }

            last_mqtt_window_status = 1;
        }
        
        resetDisplay();
        
        char displayTemp[6];
        sprintf(displayTemp, "%d.0°C", temperature);
        TFT_Print(&displayTemp[0], 5, 5, 4, 0x0000, 0xFFFF, 2);
        
        char displayHumid[4];
        sprintf(displayHumid, "%d%%", humidity);
        TFT_Print(&displayHumid[0], 5, 40, 4, 0x0000, 0xFFFF, 2);
        
        _delay_ms(30000);
    }
}


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

