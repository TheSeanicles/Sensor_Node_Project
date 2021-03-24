void PWM_Generator() {
  pinMode(arduino.pins.PWM, OUTPUT);
  pinMode(arduino.pins.Vout, INPUT);

  arduino.PWM.vBat = Battery_monitor();
  arduino.PWM.VoutValue = analogRead(arduino.pins.Vout);
  arduino.PWM.vOUT = arduino.PWM.VoutValue * 5.0/ 1023.0; // convert from bits to a voltage between 0-5
  analogWrite(arduino.pins.PWM, arduino.PWM.pulseSig);

  arduino.PWM.vHold = arduino.PWM.vOUT - arduino.PWM.vBat;

  arduino.PWM.v = arduino.PWM.vDif - arduino.PWM.vHold;
  arduino.PWM.vRef = arduino.PWM.vRef + (.1 * arduino.PWM.v);

  // if the output is higher than the reference
  // decrease the duty cycle by 1
  if ((arduino.PWM.vOUT > arduino.PWM.vRef) && (arduino.PWM.pulseSig > arduino.PWM.pwmMin))
  {
    arduino.PWM.pulseSig = arduino.PWM.pulseSig - 1; ;
  }
  // if the output is higher than the reference
  // decrease the duty cycle by 1
  if((arduino.PWM.vOUT < arduino.PWM.vRef) && (arduino.PWM.pulseSig < arduino.PWM.pwmMax))
  {
    arduino.PWM.pulseSig = arduino.PWM.pulseSig + 1;
  }
}
