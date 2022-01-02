//Receiver
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 10);
const byte address[6]="00001"; //Address value must be same in sender and receiver
int led_pin=7;

void setup() {
  Serial.begin(9600);
  radio.begin();
  //RF
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); //Set this module as receiver.
  //led
  pinMode(led_pin, OUTPUT);
}

void loop() {
  if(radio.available()){
    digitalWrite(led_pin, HIGH);
    char text[32]="";
    radio.read(text, sizeof(text));
    Serial.println(text);
    delay(1000);
  }
  else{
    digitalWrite(led_pin, LOW);
    Serial.println("nothing received");
    delay(1000);
  }
}