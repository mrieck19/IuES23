/*
 * File:   uart.c
 * Author: Alex
 *
 * Created on 14. Juni 2023, 12:18
 */

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VAL (F_CPU / 16 / BAUD - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "buzzer1.h"
#include "timer1.h"

volatile char receivedChar;
char command[2];
volatile uint8_t commandIndex;

void initializeUART() {
    // Set baud rate
    UBRR0H = (UBRR_VAL >> 8);
    UBRR0L = UBRR_VAL;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);       // Enable receiver and transmitter

    UCSR0B |= (1 << RXCIE0);        // Enable receive complete interrupt

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);         // Set frame format: 8 data bits, 1 stop bit, no parity
}

void transmitUART(char data) {
    
    while (!(UCSR0A & (1 << UDRE0)));       // Wait for empty transmit buffer

    UDR0 = data;        // Put data into buffer, sends the data
}

void sendStringUART(const char* str) {
    while (*str != '\0') {
        transmitUART(*str);
        str++;
    }
}

void compareCommand() {
    if (strcmp(command, "B1") == 0) {
        ENABLE_BUZZER;                          // Enable the Buzzer
        
        RESET_TIMER1;
        
        RESET_TIMER1_PRESCALER;
    }
}

// UART receive complete interrupt service routine
ISR(USART_RX_vect) {
    receivedChar = UDR0;

    // Start of command
    if (receivedChar == '/'){       
        memset((char*)command, '\0', sizeof(command));      // Reset array
        commandIndex = 0;       // Reset index
        return;
    }

    // End of command
    if (receivedChar == '\\'){
        compareCommand();
        commandIndex = 0;
        return;
    }

    // Our char buffer is only 2 bytes
    if (commandIndex > 1) {
        return;
    }
    
    command[commandIndex] = receivedChar;
    commandIndex++;
}
