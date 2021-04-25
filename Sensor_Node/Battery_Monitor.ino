float Battery_monitor(){
  //vOUT from voltage divider for battery voltage
  float vOUT;
  int value;
  value = analogRead(arduino.pins.Vbat);
  vOUT = (float)value * 5.0 / 1024.0;
  return vOUT;
}
