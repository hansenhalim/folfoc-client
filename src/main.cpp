#include <Arduino.h>
#include <ESP32Encoder.h>
#include <Wire.h>

// Constants that the user passes in to the motor calls
#define FORWARD 1
#define BACKWARD 2

#define MOTOR_A 0
#define MOTOR_B 1

#define CLK 25 // CLK ENCODER
#define DT 26  // DT ENCODER

#define I2C_ADDR 8 // The I2C address of server

ESP32Encoder encoder;

void setup()
{
  encoder.attachSingleEdge(DT, CLK);
  encoder.setCount(0);
  Wire.begin();
}

void sendCommand(uint8_t address, uint8_t motor_id, uint8_t dir, uint16_t steps)
{
  String command = String(motor_id) + "," + String(dir) + "," + String(steps) + ";";
  Wire.beginTransmission(address);
  Wire.write(command.c_str());
  Wire.endTransmission();
}

void loop()
{
  if (encoder.getCount() != 0)
  {
    long long encoderCount = encoder.getCount();

    if (encoderCount > 0) // Clockwise
      sendCommand(I2C_ADDR, MOTOR_A, FORWARD, 100);
    else if (encoderCount < 0) // Counterclockwise
      sendCommand(I2C_ADDR, MOTOR_B, BACKWARD, 100);
    encoder.clearCount();
  }
}
