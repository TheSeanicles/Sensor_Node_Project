void PWM_Generator() {
  arduino.PWM.VoutValue = analogRead(arduino.pins.Vout);
  arduino.PWM.vOUT = arduino.PWM.VoutValue * 5.0/ 1023.0; // convert from bits to a voltage between 0-5
  analogWrite(arduino.pins.PWM, arduino.PWM.pulseSig);
  
  arduino.PWM.vBatValue = analogRead(arduino.pins.Vbat);
  arduino.PWM.vBat = arduino.PWM.vBatValue * 5.0 / 1023.0;
  
  arduino.PWM.vHold = arduino.PWM.vOUT - arduino.PWM.vBat;

  arduino.PWM.v = arduino.PWM.vDif - arduino.PWM.vHold;

  arduino.PWM.fPWM = arduino.PWM.fPWM +  (1.0 * arduino.PWM.v);
  arduino.PWM.pulseSig = arduino.PWM.fPWM;
}
