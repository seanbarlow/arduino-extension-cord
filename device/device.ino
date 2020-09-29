#include "plug.h"
#include "button.h"

#define PUMP_PIN 13
#define LIGHT_PIN 1
#define LIGHT_BUTTON_PIN 7
#define PH_BUTTON_PIN 8
#define PUMP_BUTTON_PIN 9

Plug pump(PUMP_PIN);
Plug light(LIGHT_PIN);

Button pumpButton(PUMP_BUTTON_PIN);
Button lightButton(LIGHT_BUTTON_PIN);
Button phButton(PH_BUTTON_PIN);

void setup()
{
    // open the serial port at 9600 bps:
    Serial.begin(115200);
    light.on();
    pump.off();
}

long pumpMillis = 0;
// 4.5 minutes
const long endInterval = 270000;
//const long endInterval = 210;

// 60 minutes
const long hourlyInterval = 3600000;
unsigned long previousMillis = 0;

// 14 hours
const long fourteenHours = hourlyInterval * 14;
// 10 hours
const long tenHours = hourlyInterval * 10;
// time since last change (light on/off)
unsigned long lightMillis = 0;

void loop()
{
    unsigned long currentMillis = millis();
    if (pumpButton.isPressed())
    {
        Serial.println("Pump Button Pressed");
        pump.on();
        Serial.println("Pump turned on.");
        pumpMillis = currentMillis;
    }

    if (currentMillis - pumpMillis >= endInterval)
    {
        pump.off();
        Serial.println("Pump turned off.");
    }

    if (currentMillis - previousMillis >= hourlyInterval)
    {
        // save the last time you turned the pump on
        previousMillis = currentMillis;
        pumpMillis = currentMillis;
        Serial.println("Hourly Run.");
        pump.on();
        Serial.println("Plug turned on.");
    }

    if (lightButton.isPressed())
    {
        Serial.println("Light Button Pressed");
        if (light.status())
        {
            light.off();
            lightMillis = currentMillis;
        }
        else if (!light.status())
        {
            light.on();
            Serial.println("Light turned on.");
            lightMillis = currentMillis;
        }
    }
    // check to see if the light is on
    if (light.status())
    {
        if (currentMillis - lightMillis >= fourteenHours)
        {
            light.off();
            lightMillis = currentMillis;
        }
    }
    else if (!light.status())
    {
        if (currentMillis - lightMillis >= tenHours)
        {
            light.on();
            lightMillis = currentMillis;
        }
    }
}
