/*
 * main.c
 *
 * Created: 9/1/2024 12:29:15 AM
 *  Author: ASUS
 */ 

#define F_CPU 16000000UL  // Define the CPU clock frequency as 16 MHz (standard for Arduino Uno)
#include <avr/io.h>       // Include input/output library for AVR
#include <util/delay.h>   // Include delay functions for timing
#include <stdio.h>
// Pin definitions
#define TRIG_PIN_1 PD3       // Define TRIG_PIN_1 as PD7 (Pin 7 on Port D)
#define ECHO_PIN_1 PD2       // Define ECHO_PIN_1 as PD6 (Pin 6 on Port D)
#define LED_RED_1 PB4        // Define LED_RED_1 as PB4 (Pin 12 on Port B)
#define LED_GREEN_1 PB5      // Define LED_GREEN_1 as PB5 (Pin 13 on Port B)
#define LED_ORANGE_1 PB3
// Function to initialize USART (serial communication)
void USART_Init(unsigned int baud) {
	// Set the baud rate using UBRR (USART Baud Rate Register)
	unsigned int ubrr = F_CPU / 16 / baud - 1;
	UBRR0H = (unsigned char)(ubrr >> 8);  // Set high byte of UBRR
	UBRR0L = (unsigned char)ubrr;         // Set low byte of UBRR
	
	// Enable the USART transmitter and receiver
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	// Set frame format: 8 data bits, 1 stop bit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Function to transmit a single character via USART
void USART_Transmit(unsigned char data) {
	// Wait until the transmit buffer is empty
	while (!(UCSR0A & (1 << UDRE0)));
	
	// Load data into the buffer, which sends the data
	UDR0 = data;
}

// Function to receive a single character via USART
unsigned char USART_Receive(void) {
	// Wait until data is received (RXC0 flag is set)
	while (!(UCSR0A & (1 << RXC0)));
	
	// Return the received data from the buffer
	return UDR0;
}

// Function to initialize I/O pins for the ultrasonic sensor and LEDs
void initPins() {
	// Set TRIG_PIN_1 (PD7) as output, and ECHO_PIN_1 (PD6) as input
	DDRD |= (1 << TRIG_PIN_1);   // Set PD7 as an output (trigger pin)
	DDRD &= ~(1 << ECHO_PIN_1);  // Set PD6 as an input (echo pin)

	// Set LED_RED_1 (PB4) and LED_GREEN_1 (PB5) as outputs
	DDRB |= (1 << LED_RED_1) | (1 << LED_GREEN_1) | (1 << LED_ORANGE_1); // Configure PB4 and PB5 as outputs
}



// Function to trigger the ultrasonic sensor and measure distance
void triggerUltrasonic() {
	// Send a 10-microsecond pulse to the trigger pin to initiate the ultrasonic measurement
	PORTD &= ~(1 << TRIG_PIN_1); // Ensure the trigger pin is LOW
	_delay_us(2);
	PORTD |= (1 << TRIG_PIN_1);  // Set the trigger pin HIGH
	_delay_us(10);               // Wait for 10 microseconds
	PORTD &= ~(1 << TRIG_PIN_1); // Set the trigger pin LOW
}

uint16_t read_echo()
{
	// Measure the time for which the Echo pin is high
	uint16_t count = 0;


	// Wait for the Echo pin to go high
	while (!(PIND & (1 << ECHO_PIN_1)));

	// Start counting as long as the Echo pin is high
	while (PIND & (1 << ECHO_PIN_1))
	{
		count++;
		_delay_us(1);  // 1us delay
	}

	return count;
}

uint16_t calculate_distance(uint16_t pulse_duration)
{
	// Calculate distance in cm
	return (pulse_duration / 58);
}




int main(void) {
	// Initialize I/O pins, ADC, and USART
	initPins();
	// initADC();
	USART_Init(9600); // Set baud rate to 9600 for 16MHz clock
    
	uint16_t pulse_duration = 0;  // Initialize to avoid warning
	// uint16_t distance = 0;        // Initialize to 0
    uint16_t current_distance = 0;
    uint16_t previous_distance = 0;


	while (1) {

		
		triggerUltrasonic();
		pulse_duration = read_echo();
		current_distance = calculate_distance(pulse_duration);
		
		
		
		
		if (current_distance < previous_distance) {
			// Send 'A' to indicate the object is within 500 cm
			USART_Transmit('A');
			} 
		else if (current_distance < 390)
		{
			USART_Transmit('B');
		}
					
		else {
			// Send 'B' to indicate the object is beyond 500 cm
			USART_Transmit('C');
		}
		
		// Update the previous distance for the next loop
		previous_distance = current_distance;
		
		_delay_ms(100);


		// Receive a value via USART
		
		unsigned char Incoming_value = USART_Receive();

		if (Incoming_value == 'D') {
			PORTB |= (1 << LED_RED_1);
			PORTB &= ~(1 << LED_GREEN_1);
			
			
			} 
		else if (Incoming_value == 'E') {
			PORTB &= ~(1 << LED_GREEN_1);
			PORTB &= ~(1 << LED_RED_1);
			PORTB |= (1 << LED_ORANGE_1);
		}
		
		else if (Incoming_value == 'F') {
			PORTB |= (1 << LED_GREEN_1);
			PORTB &= ~(1 << LED_RED_1);
			PORTB &= ~(1 << LED_ORANGE_1);
			
		}
	
	}
}

