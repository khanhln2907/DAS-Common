#include <Arduino.h>
#include "BasicType.h"
#include "ArduinoLog.h"
#include "HardwareSerial.h"

#define USING_MAKEFILE 

extern "C" int main(void)
{
#ifdef USING_MAKEFILE

	// To use Teensy 3.0 without Arduino, simply put your code here.
	// For example:

	pinMode(13, OUTPUT);
	while (1) {
      // put your main code here, to run repeatedly:
    digitalWriteFast(13, HIGH);
    delay(500);
    digitalWriteFast(13, LOW);
    delay(500);
    Serial.printf("Hello \n");
	}


#else
	// Arduino's main() function just calls setup() and loop()....
	setup();
	while (1) {
		loop();
		yield();
	}
#endif
}