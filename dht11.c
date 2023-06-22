/*
 * File:   dht11.c
 * Author: alex
 *
 * Created on 11. Juni 2023, 14:42
 * 
 * PIN Order ATMega: Yellow - Ground, Orange Stromversorgung, Rot Signal
 */

#define DHT11_PIN PC0
#define F_CPU 16000000UL
#define DATA_LINE_HIGH (PINC & (1<<PC0))
#define DATA_LINE_LOW (! (PINC & (1<<PC0)))

#include <avr/io.h>
#include <util/delay.h>

void initializeDHT11() {
    DDRC &= ~(1 << DHT11_PIN);      // Set DHT11 pin (PC0) as input
}

uint8_t dht11_readBytes() {
    uint8_t data = 0;
    
    for (int8_t i = 0; i <= 7; i++) 
    {
        while (DATA_LINE_LOW);      // Wait for DHT11 to pull high (50us)
        _delay_us(30);              // Wait 30us
        
        // If DHT11 is high after 30us, the bit is 1
        if (DATA_LINE_HIGH) {
            data |= (1 << (7 - i));
        }
        
        while (DATA_LINE_HIGH);     // Wait for DHT11 to pull low
    }
    
    return data;
}

void dht11_getData(uint8_t *humidity, uint8_t *temperature) {
    // ====== Start ======
    DDRC  |=  (1 << DHT11_PIN);     // Set DHT11 pin as output
    PORTC &= ~(1 << DHT11_PIN);     // Set DHT11 pin low
    _delay_ms(18);                  // Wait 18ms
    PORTC |=  (1 << DHT11_PIN);     // Set DHT11 pin high
    _delay_us(40);                  // Wait 40us
    DDRC  &= ~(1 << DHT11_PIN);     // Set DHT11 pin as input
    // ===================
    
    // ======= Wait ======
    while (DATA_LINE_HIGH);         // Wait for DHT11 to pull low
    while (DATA_LINE_LOW);          // Wait for DHT11 ro pull high (80us)
    while (DATA_LINE_HIGH);         // Wait for DHT11 to pull low for Data (80us)
    // ===================

    // ======= Data ======
    uint8_t data[5] = {0};
    // Read 40 bits of data (5*8bit)
    for (uint8_t i = 0; i < 5; i++)
    {
        data[i] = dht11_readBytes();
    }
    // ===================
    
    // ===== Checksum ====
    if (data[0] + data[1] + data[2] + data[3] == data[4])
    {
        *humidity = data[0];
        *temperature = data[2];
    }
    // ===================
}

