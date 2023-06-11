
#include <avr/io.h>
#include <util/delay.h>
#include "temp_hum_sensor.h"



// Function to read data from the DHT11 sensor
uint8_t dht11_read_data(uint8_t* temperature, uint8_t* humidity) {
  uint8_t bits[5];
  uint8_t i, j;

  // Request data from the sensor
  DDRD |= (1 << PD4);   // Set PD4 (Port D4) as output
  PORTD &= ~(1 << PD4); // Pull the line low
  _delay_ms(18);        // Hold the line low for at least 18ms
  PORTD |= (1 << PD4);  // Release the line
  _delay_us(1);         // Wait for 1us

  // Configure the data pin as an input
  DDRD &= ~(1 << PD4);  // Set PD4 (Port D4) as input

  // Wait for the response from the sensor
  _delay_us(40);        // Wait for 40us
  if ((PIND & (1 << PD4))) {
    // No response received
    return 0;
  }

  _delay_us(80);        // Wait for 80us
  if (!(PIND & (1 << PD4))) {
    // Sensor should pull the line low for 80us
    // If not, something went wrong
    return 0;
  }

  _delay_us(80);        // Wait for 80us

  // Read the data from the sensor
  for (j = 0; j < 5; ++j) {
    uint8_t result = 0;
    for (i = 0; i < 8; ++i) {
      while (!(PIND & (1 << PD4)));  // Wait for the line to go high
      _delay_us(30);                  // Wait for the line to go low again
      if (PIND & (1 << PD4)) {
        // If the line is still high, it's a 1
        result |= (1 << (7 - i));
      }
      while (PIND & (1 << PD4));      // Wait for the line to go low again
    }
    bits[j] = result;
  }

  // Check the checksum
  if ((bits[0] + bits[1] + bits[2] + bits[3]) != bits[4]) {
    // Checksum does not match, data is invalid
    return 0;
  }

  // Extract temperature and humidity
  *humidity = bits[0];
  *temperature = bits[2];

  return 1;  // Data read successfully
}

int main(void) {
  uint8_t temperature, humidity;

  while (1) {
    if (dht11_read_data(&temperature, &humidity)) {
      // Data read successfully
      // Use the temperature and humidity values
      // ...
    } else {
      // Failed to read data
      // Handle the error
      // ...
    }

    _delay_ms(1000);  // Delay for 1 second before reading again
  }

  return 0;
}
