#include <Arduino.h>
#include <Timer.h>

Timer T(1000);  //create Timer with 1 sec interval (is activated by default)
bool LED = false;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    if (T.tick()) { //returns true when timerinterval has passed and automatically resets timer 
        LED = !LED;
        digitalWrite(LED_BUILTIN, LED);
    }
}
