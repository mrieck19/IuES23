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

volatile char receivedChar;

void initializeUART() {
  // Set baud rate
  UBRR0H = (UBRR_VAL >> 8);
  UBRR0L = UBRR_VAL;

  // Enable receiver and transmitter
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  // Enable receive complete interrupt
  UCSR0B |= (1 << RXCIE0);

  // Set frame format: 8 data bits, 1 stop bit, no parity
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void transmitUART(char data) {
  // Wait for empty transmit buffer
  while (!(UCSR0A & (1 << UDRE0)));

  // Put data into buffer, sends the data
  UDR0 = data;
}

void sendStringUART(const char* str) {
  while (*str != '\0') {
    transmitUART(*str);
    str++;
  }
}

// UART receive complete interrupt service routine
ISR(USART_RX_vect) {
  receivedChar = UDR0;
  
  // Process received character here
}
