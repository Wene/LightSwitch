#define LIGHT1 8
#define LIGHT2 9
#define BTN1 4
#define BTN2 5
#define TICKER 6000
#define DELAY 10

#include "switch.h"

Switch Sw1(LIGHT1, BTN1, BTN2, TICKER, DELAY);
Switch Sw2(LIGHT2, BTN2, BTN1, TICKER, DELAY);

void setup()
{
    //so far nothing here...
}

void loop()
{
    Sw1.handle();
    Sw2.handle();
    delay(DELAY);
}
