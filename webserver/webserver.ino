#include <SPI.h>
#include <Wire.h>
#include <Ultrasonic.h>
#include "DHT.h"

#define Addr 0x1E               // 7-bit address of HMC5883 compass
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)

#define DISTANCE_SENSOR_PIN A0

DHT dht(DHTPIN, DHTTYPE);
Ultrasonic ultrasonic(6,5);


long duration, distance;
int t = 0;
int h = 0;
int x, y, z;
double angle;
int ir_dis;

void setup() {
  // 初始化串口通信
  Serial.begin(9600);
  Serial1.begin(57600);
  Wire.begin();
  temp_init();

  // Set operating mode to continuous FOR COMPASS
  Wire.beginTransmission(Addr);
  Wire.write(0x02);
  Wire.write(0x00);
  Wire.endTransmission();
}

void loop() {
  compass();
  temp_read();
  ir();
  sonic();

  Serial1.print("x");
  Serial1.print(x);
  Serial1.print("y");
  Serial1.print(y);
  Serial1.print("z");
  Serial1.print(z);
  Serial1.println("s");
  Serial1.print("a");
  Serial1.print(angle);
  Serial1.println("d");
  Serial1.print("t");
  Serial1.print(t);
  Serial1.print("h");
  Serial1.print(h);
  Serial1.print("i");
  Serial1.print(ir_dis);
  Serial1.print("u");
  Serial1.print(distance);
  Serial1.print("e");

  delay(500);
}
