void ir()
{
  ir_dis = (6787 / (analogRead(DISTANCE_SENSOR_PIN) - 3)) - 4; //unit: cm
  Serial.print(ir_dis);
  Serial.println(" cm ");
}
