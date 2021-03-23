void Sleep(){
  attachInterrupt(digitalPinToInterrupt(2), Wakeup, FALLING);
  MCUCR = B01100000;
  SMCR = B00000101;
  __asm__ ("SLEEP");
}

void Wakeup(){
}
