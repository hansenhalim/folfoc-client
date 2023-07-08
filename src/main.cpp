#include "Arduino.h"
#include <ESP32Encoder.h>

#define CLK_PIN 23
#define DT_PIN 22
#define SW_PIN 21

ESP32Encoder encoder;
volatile int32_t newPosition = 0;
int32_t oldPosition = 0;
bool switchState = false;

void IRAM_ATTR handleEncoder()
{
  if (digitalRead(CLK_PIN) == digitalRead(DT_PIN))
  {
    newPosition++;
  }
  else
  {
    newPosition--;
  }
}

void setup()
{
  Serial.begin(9600);
  encoder.attachSingleEdge(CLK_PIN, DT_PIN);
  pinMode(SW_PIN, INPUT_PULLUP);
  attachInterrupt(CLK_PIN, handleEncoder, CHANGE);
  attachInterrupt(DT_PIN, handleEncoder, CHANGE);
}

void loop()
{
  if (newPosition != oldPosition)
  {
    if (newPosition > oldPosition)
    {
      Serial.println("CW");
    }
    else
    {
      Serial.println("CCW");
    }
    oldPosition = newPosition;
  }

  if (digitalRead(SW_PIN) == LOW && !switchState)
  {
    Serial.println("Switch pressed");
    switchState = true;
  }
  else if (digitalRead(SW_PIN) == HIGH)
  {
    switchState = false;
  }

  delay(100); // Adjust the delay time as needed
}
