#include "switch.h"
#include "Arduino.h"

Switch::Switch(int relaisPin, int lightButtonPin, int modifyButtonPin)
{
    relais = relaisPin;
    lightButton = lightButtonPin;
    modifyButton = modifyButtonPin;

    pinMode(relais, OUTPUT);
    pinMode(lightButton, INPUT_PULLUP);
    pinMode(modifyButton, INPUT_PULLUP);

    digitalWrite(relais, LOW);

    lightCount = 0;
    modifyCount = 0;
    isOn = false;
    tickerDefault = 6000;
    
}

void Switch::handle()
{
    readButtons();

    if(lightCount > 2)                   //if interaction...
    {
        if(isOn)
        {
            digitalWrite(relais, LOW);  //turn light off
            isOn = false;

            debounce();                 //wait while button is still hold        
        }
        else
        {
            digitalWrite(relais, HIGH); //turn light on
            isOn = true;
            ticker = tickerDefault;
            lightDuration = 1;

            checkModify();
        }
    }
    else                                //if no interaction...
    {
        if(isOn)
        {
            ticker--;
            if(ticker <= 0)
            {
                lightDuration--;
                if(lightDuration <= 0)
                {
                    digitalWrite(relais, LOW);  //turn light off
                    isOn = false;

                    lightDuration = 0;
                    ticker = 0;
                }
                else
                {
                    ticker = tickerDefault;
                }
            }
        }
    }
}

void Switch::readButtons()
{
     if(digitalRead(lightButton) == LOW)
     {
         lightCount++;
         if(lightCount > 10000)     //prevent overflow
         {
             lightCount = 10000;
         }
     }
     else
     {
         lightCount = 0;
     }
     
     if(digitalRead(modifyButton) == LOW)
     {
         modifyCount++;
         if(modifyCount > 10000)    //prevent overflow
         {
             modifyCount = 10000;
         }
     }
     else
     {
         modifyCount = 0;
     }
}

void Switch::debounce()
{
    while(lightCount > 2)
    {
        readButtons();
        delay(10);
    }
}

void Switch::checkModify()
{
    while(lightCount > 2)
    {
        readButtons();
        if(modifyCount > 2)
        {
            lightDuration = lightDuration * 2;
            while(modifyCount > 2)    //wait to release modify button
            {
                readButtons();
                delay(10);
            }
        }
        delay(10);
    }
}

