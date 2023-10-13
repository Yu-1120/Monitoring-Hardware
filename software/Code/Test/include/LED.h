#include <Arduino.h>

#define PIN_LED1 12
#define PIN_LED2 13


#define PIN_LED1_LOW        digitalWrite(PIN_LED1, LOW);
#define PIN_LED1_HIGH  digitalWrite(PIN_LED1, HIGH);      
#define PIN_LED2_HIGH   digitalWrite(PIN_LED2, HIGH);
#define PIN_LED2_LOW   digitalWrite(PIN_LED2, LOW);


void LED_Init(){

    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
}