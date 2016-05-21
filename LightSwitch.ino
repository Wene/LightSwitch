#define LIGHT1 7
#define LIGHT2 6
#define BTN1 9
#define BTN2 8
#define LED 13
#define TICKER 12000    // TICKER * DELAY => Timeout in ms
#define DELAY 10

#include "switch.h"

Switch Sw1(LIGHT1, BTN1, BTN2, TICKER, DELAY);
Switch Sw2(LIGHT2, BTN2, BTN1, TICKER, DELAY);

void setup()
{
    pinMode(OUTPUT, LED);
}

int ledCount = 0;
bool ledOn = true;

void loop()
{
    Sw1.handle();
    Sw2.handle();

    // Blink the LED
    ledCount++;
    if(ledCount > 100)
    {
        ledCount = 0;
        ledOn = !ledOn;
        digitalWrite(LED, ledOn);
    }
    
    delay(DELAY);
}
