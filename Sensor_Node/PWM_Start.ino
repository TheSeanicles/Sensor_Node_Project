void PWM_Start() {
  // the command is for D5 (digital out ~5) 
  pinMode(arduino.pins.PWM, OUTPUT);
  pinMode(arduino.pins.Vout, INPUT);
  pinMode(arduino.pins.Vbat, INPUT);
  TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz
}
