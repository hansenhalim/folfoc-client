#include <Arduino.h>
#include <ESP32Encoder.h>

#define CLK 25 // CLK ENCODER
#define DT 26  // DT ENCODER

ESP32Encoder encoder;

void setup()
{
  encoder.attachSingleEdge(DT, CLK);
  encoder.setCount(0);
  Serial.begin(115200);
}

void loop()
{
  if (encoder.getCount() != 0)
  {
    if (encoder.getCount() > 0)
      Serial.println("Clockwise");
    else if (encoder.getCount() < 0)
      Serial.println("Counterclockwise");
    encoder.clearCount();
  }
}