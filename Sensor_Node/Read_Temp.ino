float Read_Temp() {
  float val;
  float tempC;
  float tempF;
  float vout;
  val = analogRead(arduino.pins.temp);
  vout = val * (5.0 / 1023.0);
  tempC = (vout - 0.5) / 0.01;
  tempF = (tempC * (9.0 / 5.0)) + 32.0;
  //Serial.println(val);
  //Serial.println(vout);
  //Serial.println(tempC);
  //Serial.println(tempF);
  if (arduino.temp_type = Fahrenheit){
    return tempF;
  }
  else {
    return tempC;
  }
}
