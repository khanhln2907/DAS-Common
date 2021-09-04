#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.printf("Hello World \n");

  pinMode(13, OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWriteFast(13, HIGH);
  delay(1000);
  digitalWriteFast(13, LOW);
  delay(1000);
  Serial.printf("Hello World \n");
}