float Read_Temp(int analogPin) {
  float val;
  float tempC;
  float tempF;
  float vout;
  val = analogRead(analogPin);
  vout = val * (5.0 / 1023.0);
  tempC = (vout - 0.5) / 0.01;
  tempF = (tempC * (9.0 / 5.0)) + 32.0;
  //Serial.println(val);
  //Serial.println(vout);
  //Serial.println(tempC);
  //Serial.println(tempF);
  return tempC;
}
