#include <Arduino.h>
#include "BasicType.h"
#include "ArduinoLog.h"
#include "HardwareSerial.h"

void setup() {
  Serial.begin(115200);
  Serial.printf("Hello World \n");

  Log.begin(LOG_LEVEL_NOTICE, &Serial1);
  Log.notice("Hello \n");

  pinMode(13, OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWriteFast(13, HIGH);
  delay(1000);
  digitalWriteFast(13, LOW);
  delay(1000);
  Log.notice("Hello \n");
}