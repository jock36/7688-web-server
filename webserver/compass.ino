void compass()
{
  
  // Initiate communications with compass
  Wire.beginTransmission(Addr);
  Wire.write(0x03);        // Send request to X MSB register
  Wire.endTransmission();

  Wire.requestFrom(Addr, 6);    // Request 6 bytes; 2 bytes per axis
  if (Wire.available() <= 6) {  // If 6 bytes available
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
    angle = atan2((double)y, (double)x) * (180 / 3.14159265) + 180; // angle in degrees
  }
}
