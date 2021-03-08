void PWM_Generator(int analog_pin, int digital_pin, float vBat) {
  pinMode(digital_pin, OUTPUT);
  pinMode(analog_pin, INPUT);
  
  int pulseSig = 113; // .44 duty cycle in the arduino PWM range 0-255 (113)
  int pwmMax = 200;  
  int pwmMin = 25;
  float vRef = 1.537; // calculated with voltage divider of 9V output 
  float vOUT;
  int value; // store the 10bit number that arduino reads
  float vDif = 1.9;
  float vBatHold;
  float vHold;
  
  value = analogRead(analog_pin);
  vOUT = (float)value * 5.0 / 1023.0; // convert from bits to a voltage between 0-5 
  //Serial.println(vOUT); //Used for debugging

  // set / update the reference voltage so that we are charging at a constant current 
  // w/ 68ohm load we want a current of 28mA(.1C) so we are going to have a voltage differce of 1.9V 
  // this difference is measured between the battery voltage and the output voltage of the boost converter 
  vBatHold = vBat;
  // 
  vBatHold = vBatHold / .17;
  vOUT = vOUT / .17;
  vHold = vOUT - vBatHold;
  if (vHold < vDif)
  {
    float v;
    v = (vDif - vHold) * .17;
    vRef = vRef + v;
  }
  else 
  {
    float v;
    v = (vHold - vDif) *.17;
    vRef = vRef - v;
  }
  
  
  // if the output is higher than the reference 
  // decrease the duty cycle by 1
  if ((vOUT > vRef) && (pulseSig > pwmMin)) 
  {
    pulseSig = pulseSig - 1;
  }
  // if the output is higher than the reference 
  // decrease the duty cycle by 1
  if((vOUT < vRef) && (pulseSig < pwmMax))
  {
    pulseSig = pulseSig + 1;
  }
  analogWrite(digital_pin, pulseSig);
}
