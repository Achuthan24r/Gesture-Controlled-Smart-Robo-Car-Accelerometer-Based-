#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

MPU6050 mpu;
RF24 radio(9, 10);
const byte address[6] = "00001";

struct Data {
  int x;
  int y;
} data;

void setup() {
  Wire.begin();
  mpu.initialize();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  data.x = mpu.getAccelerationX();
  data.y = mpu.getAccelerationY();
  radio.write(&data, sizeof(data));
  delay(50);
}
