bool Solar_Panel_Active() {
  pinMode(arduino.pins.solar, INPUT);
  float val;
  float vout;
  val = analogRead(arduino.pins.solar);
  vout = val * (5.0 / 1023.0);
  if(vout > 2){ // If vout is greater than 4.9 volts the solar panel is considered active.
    return 1;
  }
  else{
    return 0;
  }
}
