#include <Arduino.h>
#include "CircularBuffer.h"
#include "ArduinoLog.h"

void setup() {
  // put your setup code here, to run once:
  Log.begin(LOG_LEVEL_NOTICE, &Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
}