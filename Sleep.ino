void Sleep(){
  MCUCR = B01100000;
  SMCR = B00000101;
  __asm__ ("SLEEP");
  attachInterrupt(digitalPinToInterrupt(2), Wakeup, FALLING);
  delay(1000);
}

void Wakeup(){
}
