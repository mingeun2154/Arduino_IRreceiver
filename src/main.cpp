//Receiver
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Servo.h>
#include <string.h>

#define ON "on"//right
#define OFF "off"//left

//RF module.
RF24 radio(9, 10);
const byte address[6]="00001"; //Address value must be same in sender and receiver
//servo motors.
Servo leftServo;
Servo rightServo;
int leftServo_pin=4;
int rightServo_pin=5;
bool isOn_first=0;
bool isOn_second=0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  //RF module.
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); //Set this module as receiver.
  //servo motors.
  pinMode(leftServo_pin, OUTPUT);
  pinMode(rightServo_pin, OUTPUT);
  leftServo.attach(leftServo_pin);
  rightServo.attach(rightServo_pin);
}

void loop() {
  char signal[16]="";
  //Initialize servo motors angle to 0.
  if(leftServo.read()!=0){
    leftServo.write(0); 
    delay(100);
  }
  if(rightServo.read()!=0){
    rightServo.write(0); 
    delay(100);
  }
  //Receive signal.
  if(radio.available()){
    char signal[16]="";
    radio.read(&signal, sizeof(signal));
    if(!strcmp(signal, OFF)){  //strcmp() return 0 if they are same strings.
      leftServo.write(30); 
      delay(500);
    }
    else if(!strcmp(signal, ON)){
      rightServo.write(35); 
      delay(500);
    }
    else;
  }

}