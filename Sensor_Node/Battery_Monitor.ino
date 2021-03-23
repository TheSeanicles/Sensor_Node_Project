float Battery_monitor(int analog_pin){
  //vOUT from voltage divider for battery voltage 
  float vOUT;
  int value;
  value = analogRead(analog_pin);
  vOUT = (float)value * 5.0 / 1023.0;

  
  return vOUT;
}
