/*
 * main.c
 *
 * Created: 9/1/2024 9:12:44 AM
 *  Author: ASUS
 */ 

#define F_CPU 16000000UL  // Define the CPU clock frequency as 16 MHz
#include <avr/io.h>       // Include input/output library for AVR
#include <util/delay.h>   // Include delay functions for timing
#include <stdio.h>

// Pin definitions
#define TRIG_PIN_1 PD3       // Define TRIG_PIN_1 as PD3 (Pin 3 on Port D)
#define ECHO_PIN_1 PD2       // Define ECHO_PIN_1 as PD2 (Pin 2 on Port D)
#define LED_RED_1 PB2        // Define LED_RED_1 as PB2 (Pin 10 on Port B)
#define LED_GREEN_1 PB3      // Define LED_GREEN_1 as PB3 (Pin 11 on Port B)
#define LED_ORANGE_1 PB1
// Function to initialize USART (serial communication)
void USART_Init(unsigned int baud) {
	unsigned int ubrr = F_CPU / 16 / baud - 1;
	UBRR0H = (unsigned char)(ubrr >> 8);  // Set high byte of UBRR
	UBRR0L = (unsigned char)ubrr;         // Set low byte of UBRR
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Enable transmitter and receiver
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit
}

// Function to transmit a single character via USART
void USART_Transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));  // Wait until buffer is empty
	UDR0 = data;  // Send data
}

// Function to receive a single character via USART
unsigned char USART_Receive(void) {
	while (!(UCSR0A & (1 << RXC0)));  // Wait until data is received
	return UDR0;  // Return received data
}

// Function to initialize I/O pins for the ultrasonic sensor and LEDs
void initPins() {
	DDRD |= (1 << TRIG_PIN_1);   // Set TRIG_PIN_1 as output
	DDRD &= ~(1 << ECHO_PIN_1);  // Set ECHO_PIN_1 as input
	DDRB |= (1 << LED_RED_1) | (1 << LED_GREEN_1) | (1 << LED_ORANGE_1);  // Set LEDs as outputs
}

// Function to trigger the ultrasonic sensor and measure distance
void triggerUltrasonic() {
	PORTD &= ~(1 << TRIG_PIN_1); // Ensure trigger pin is LOW
	_delay_us(2);
	PORTD |= (1 << TRIG_PIN_1);  // Set trigger pin HIGH
	_delay_us(10);               // Wait for 10 microseconds
	PORTD &= ~(1 << TRIG_PIN_1); // Set trigger pin LOW
}

// Function to measure the time of the echo pulse
uint16_t read_echo() {
	uint16_t count = 0;
	while (!(PIND & (1 << ECHO_PIN_1))); // Wait for Echo pin to go HIGH
	while (PIND & (1 << ECHO_PIN_1)) {   // Count while Echo pin is HIGH
		count++;
		_delay_us(1);  // 1us delay
	}
	return count;
}

// Function to calculate distance based on echo pulse duration
uint16_t calculate_distance(uint16_t pulse_duration) {
	return (pulse_duration / 58);  // Convert pulse duration to distance in cm
}

int main(void) {
	// Initialize I/O pins and USART
	initPins();
	USART_Init(9600);  // Set baud rate to 9600 for 16MHz clock
	
	uint16_t pulse_duration = 0;  // To store echo pulse duration 
	uint16_t current_distance = 0;
    uint16_t previous_distance = 0;

	while (1) {
		// Trigger the ultrasonic sensor
		triggerUltrasonic();
		pulse_duration = read_echo();
		current_distance = calculate_distance(pulse_duration);

		// Transmit 'A' if object is within 390 cm, else 'B'
		if (current_distance < previous_distance) {
			USART_Transmit('D');
			} 
		else if (current_distance < 390)
		{
			USART_Transmit('E');
		}
		
		else {
			USART_Transmit('F');
		}
		
		previous_distance = current_distance;
				
		_delay_ms(100);

		// Receive a value via USART
		unsigned char Incoming_value = USART_Receive();

		// Control the LEDs based on the received value
		if (Incoming_value == 'A') {
			PORTB |= (1 << LED_RED_1);    // Turn on RED LED
			PORTB &= ~(1 << LED_GREEN_1); // Turn off GREEN LED
			} 
			
		else if (Incoming_value == 'B') {
			PORTB &= ~(1 << LED_GREEN_1);  // Turn on GREEN LED
			PORTB &= ~(1 << LED_RED_1);   // Turn off RED LED
			PORTB |= (1 << LED_ORANGE_1);
		}
		else if (Incoming_value == 'C') {
			PORTB |= (1 << LED_GREEN_1);  // Turn on GREEN LED
			PORTB &= ~(1 << LED_RED_1);   // Turn off RED LED
			PORTB &= ~(1 << LED_ORANGE_1);
		}

	}
}

