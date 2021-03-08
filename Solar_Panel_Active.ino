bool Solar_Panel_Active(int analogPin) {
  float val;
  float vout;
  val = analogRead(analogPin);
  vout = val * (5.0 / 1023.0);
  if(vout > 4.7){ // If vout is greater than 4.9 volts the solar panel is considered active.
    return 1;
  }
  else{
    return 0;
  }
}
