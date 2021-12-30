//receiver
#include <Arduino.h>
#include <IRremote.h>

int recvPin=2;
IRrecv irrecv(recvPin);

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void  ircode(decode_results* results){
  // if(results->decode_type==SAMSUNG){
  //   Serial.print(results->address, HEX);
  //   Serial.print(":");
  // }
  Serial.print(results->value, HEX);
}

void encoding(decode_results* results){
  switch (results->decode_type)
  {
  case UNKNOWN: Serial.print("UNKNOWN"); break;
  case SAMSUNG: Serial.print("SAMSUNG"); break;
  case LG: Serial.print("LG"); break;
  default: Serial.print("DEFAULT"); break;
  }
}

void dumpInfo(decode_results* results){
  if(results->overflow){
    Serial.println("IR code too long. Edit IRremoteInt.h and increase RAWLEN");
    return ;
  }
  //Show encoding standard
  Serial.print("Encoding : ");
  encoding(results);
  Serial.print(" ");
  //Show code&length
  Serial.print("Code : ");
  ircode(results);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
}

void loop() {
  // put your main code here, to run repeatedly:
  decode_results results;
  if(irrecv.decode(&results)){
    dumpInfo(&results);
    Serial.println("");
    irrecv.resume();
  }
}