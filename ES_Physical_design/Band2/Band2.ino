#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int trig = 5;
int echo = 4;
int LED1 = 9;   //orange
int LED2 = 2;   //red
int LED3 = 3;   //green
int timeInMicro;
uint16_t current_distance;
uint16_t previous_distance;
uint16_t distance_1;
RF24 radio(6, 7); // CE, CSN
uint8_t addresses[][5] = {"00001", "00002"};

void setup() {


  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  Serial.begin(9600);
}

void loop() {
  delay(50);

  radio.stopListening();
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  timeInMicro = pulseIn(echo, HIGH, 10000); // Set timeout to 10ms

  distance_1 = timeInMicro / 29 / 2;
  Serial.println(distance_1);

  bool success = radio.write(&distance_1, sizeof(distance_1));
  if (!success) {
    Serial.println("Transmission failed!");
  }
  delay(50);

  radio.startListening();
  unsigned long start_time = millis();
  while (!radio.available()) {
    if (millis() - start_time > 1000) { // Exit loop after 1 second
      break;
    }
  }


  if (radio.available()) {
    radio.read(&current_distance, sizeof(current_distance));
    Serial.print("current_distance received: ");
    Serial.println(current_distance);
    if (current_distance < (previous_distance-1) && current_distance < 20) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      delay(1000);
    }
    else if(current_distance > (previous_distance+1) && current_distance < 20){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);

    }
    else if(current_distance < (previous_distance-1) && current_distance > 20){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);

    }
    
    else if(current_distance > (previous_distance+1) && current_distance > 20){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);

    }

    else if(current_distance <= 20){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);

    }

    else {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
    }
   previous_distance = current_distance;

   delay(200);    
  } 
  // else {
  //   digitalWrite(LED3, HIGH);
  //   digitalWrite(LED2, LOW);
  //   digitalWrite(LED1, LOW);
  // }
  Serial.println( );
}