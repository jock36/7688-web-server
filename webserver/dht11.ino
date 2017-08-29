void temp_init()
{
  dht.begin();
  pinMode(7,INPUT);
}

void temp_read()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  if (dht.readTemperature())
  {
    t = dht.readTemperature();
    Serial.println("------------------------------");
    Serial.print("temperature = ");
    Serial.println(t);
  }
  else
    t = 0;
  if (dht.readHumidity())
  {
    h = dht.readHumidity();

    Serial.print("humidity = ");
    Serial.println(h);
  }
  else
    h = 0;
}
