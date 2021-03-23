void PWM_Generator(int analog_pin, int digital_pin, float vBat) {
  pinMode(digital_pin, OUTPUT);
  pinMode(analog_pin, INPUT);
  
  int pulseSig = 170;                                      // duty cycle for 15V out in the arduino PWM range 0-255 (113)
  int pwmMax = 225;  
  int pwmMin = 25;
  float vRef = 2.56;                                      // calculated with voltage divider of 9V output 
  float vOUT;
  int value;                                              // store the 10bit number that arduino reads
  float vDif = 1.16;
  float vBatHold;
  float vHold;
  float v = 0.0;
  int counter = 0;
  
  value = analogRead(analog_pin);
  vOUT = (float)value * 5.0 / 1023.0;                     // convert from bits to a voltage between 0-5 
  //Serial.println(vOUT); //Used for debugging
  


  if ((vOUT > vRef) && (pulseSig > pwmMin))               // if the output is higher than the reference 
                                                          // decrease the duty cycle by 1
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

delay(15000);

  vBatHold = vBat;
  vHold = vOUT - vBatHold;
  if (vHold < vDif)
  {
    vRef = vRef + .1;
  }
  else if (vHold > vDif) 
  {
    vRef = vRef - .1;
  }

}
