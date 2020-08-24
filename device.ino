#include "plug.h"
#include "button.h"

#define PLUG_PIN 10
#define BUTTON_PIN 2

Plug plug(PLUG_PIN);

Button onButton(BUTTON_PIN);
void setup()
{
    // open the serial port at 9600 bps:
    Serial.begin(9600);
}

long startMillis = 0;
// 4.5 minutes
const long endInterval = 270000;
//const long endInterval = 210;

// 60 minutes
const long hourlyInterval = 3600000;
unsigned long previousMillis = 0;
void loop()
{
    unsigned long currentMillis = millis();
    if (onButton.isPressed())
    {
        Serial.println("Button Pressed");
        plug.on();
        Serial.println("Plug turned on.");
        startMillis = currentMillis;
    }
    if (currentMillis - startMillis >= endInterval)
    {
        plug.off();
        Serial.println("Plug turned off.");
    }

    if (currentMillis - previousMillis >= hourlyInterval)
    {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        startMillis = currentMillis;
        Serial.println("Hourly Run.");
        plug.on();
        Serial.println("Plug turned on.");
    }
}
