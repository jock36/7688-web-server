void sonic()
{ 
  distance = ultrasonic.Ranging(CM);
  Serial.print(distance); // CM or INC
  Serial.println(" cm" );
}
