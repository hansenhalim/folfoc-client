#include <Arduino.h>
#include <ESP32Encoder.h>
#include <Wire.h>

#define CLK 25 // CLK ENCODER
#define DT 26  // DT ENCODER

ESP32Encoder encoder;

void setup()
{
  encoder.attachSingleEdge(DT, CLK);
  encoder.setCount(0);
  Wire.begin();
}

void sendCommand(uint8_t address, int motor_id, String direction, int steps)
{
  String command = String(motor_id) + "," + direction + "," + String(steps) + ";";
  Wire.beginTransmission(address);
  Wire.write(command.c_str());
  Wire.endTransmission();
}

void loop()
{
  if (encoder.getCount() != 0)
  {
    if (encoder.getCount() > 0)
      sendCommand(8, 1, "CW", 100); // 8 is the I2C address of Arduino A
    else if (encoder.getCount() < 0)
      sendCommand(8, 2, "CCW", 50); // 8 is the I2C address of Arduino A
    encoder.clearCount();
  }
}
