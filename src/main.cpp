//receiver
#include <Arduino.h>
#include <IRremote.h>

int recvPin = 2;
IRrecv irrecv;
IRData* irdata;

void setup() {
  irrecv.begin(recvPin, true);
  Serial.begin(9600);
}

void manufacturer(IRData* irdata){
  switch (irdata->protocol){
  case SAMSUNG: Serial.print("SAMSUNG"); break;
  case LG: Serial.print("LG     "); break;
  default: Serial.print("DEFAULT"); break;
  }
}

void command(IRData* irdata){
  manufacturer(irdata);
  Serial.print('\t');
  Serial.print("\t address: ");
  Serial.print(irdata->address, HEX);
  Serial.print("\t command: ");
  Serial.print(irdata->command, HEX);
  Serial.print("\t extra: ");
  Serial.print(irdata->extra, HEX);
  Serial.print("\t numberOfBits: ");
  Serial.print(irdata->numberOfBits, HEX);
  Serial.print("\t flags: ");
  Serial.print(irdata->flags, HEX);
  Serial.print("\t decodedRawData: ");
  Serial.print(irdata->decodedRawData, HEX);
}

void loop() {
  if(irrecv.decode()){
   irdata=irrecv.read();
   if(irdata->flags==0x40){
     Serial.print("OverFlowed\n");
     return ;
   }
  //  manufacturer(irdata);
  //  Serial.print('\t');
   command(irdata);
   Serial.print('\n');
   irrecv.resume();
  }
  irdata=nullptr;
}