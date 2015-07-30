#include "switch.h"
#include "Arduino.h"

#define LIMIT 3

Switch::Switch(int relayPin, int lightButtonPin, int modifyButtonPin, int ticker, int delay)
{
    relay = relayPin;
    lightButton = lightButtonPin;
    modifyButton = modifyButtonPin;

    pinMode(relay, OUTPUT);
    pinMode(lightButton, INPUT_PULLUP);
    pinMode(modifyButton, INPUT_PULLUP);

    digitalWrite(relay, LOW);

    lightBtnPushed = 0;
    modifyBtnPushed = 0;
    isOn = false;
    tickerDefault = ticker;
    delayTime = delay;
}

void Switch::handle()
{
    readButtons();

    if(lightBtnPushed > LIMIT)                  //if interaction...
    {
        if(isOn)
        {
            digitalWrite(relay, LOW);           //turn light off
            isOn = false;

            waitForRelease(lightBtnPushed);     //wait while button is still hold
        }
        else
        {
            digitalWrite(relay, HIGH);          //turn light on
            isOn = true;
            cycleTicker = tickerDefault;
            cycleCount = 1;

            checkModify();
        }
    }
    else                                        //if no interaction...
    {
        if(isOn)
        {
            cycleTicker--;
            if(cycleTicker <= 0)
            {
                cycleCount--;
                if(cycleCount <= 0)
                {
                    digitalWrite(relay, LOW);   //turn light off
                    isOn = false;

                    cycleCount = 0;
                    cycleTicker = 0;
                }
                else
                {
                    cycleTicker = tickerDefault;
                }
            }
        }
    }
}

void Switch::readButtons()
{
     if(digitalRead(lightButton) == LOW)
     {
         lightBtnPushed++;
         if(lightBtnPushed > 10000)             //prevent overflow
         {
             lightBtnPushed = 10000;
         }
     }
     else
     {
         lightBtnPushed = 0;
     }
     
     if(digitalRead(modifyButton) == LOW)
     {
         modifyBtnPushed++;
         if(modifyBtnPushed > 10000)            //prevent overflow
         {
             modifyBtnPushed = 10000;
         }
     }
     else
     {
         modifyBtnPushed = 0;
     }
}

void Switch::waitForRelease(int &button)        //wait while the buttin in the reference is still pressed
{
    while(button > LIMIT)
    {
        readButtons();
        delay(delayTime);
    }
}

void Switch::checkModify()                      //doubles the cycleCount every time the second button is pressed
{
    while(lightBtnPushed > LIMIT)
    {
        readButtons();
        if(modifyBtnPushed > LIMIT)
        {
            cycleCount = cycleCount * 2;
            waitForRelease(modifyBtnPushed);    //wait to release modify button
        }
        delay(10);
    }
}

