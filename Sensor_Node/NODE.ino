void NODE(){
  enum class states {START, CHARGING, TEMP, SLEEP, BLUETOOTH, HALT};
    states state = states::START;
    while (state != states::HALT){
      switch (state){
      case states::START:
        if ((Solar_Panel_Active(solar_Pin) == 1) && (Battery_monitor(Vbat_Pin) <= 1.70)){
          state = states::CHARGING;
        }
        else{
          state = states::SLEEP;
        }
        break;
      case states::CHARGING:
        op_state = 1;
        // get the current battery voltage
        vBat = Battery_monitor(Vbat_Pin);
        int i;
        for (i=0; i <= (charging_time / 10); i++){
          PWM_Generator(Vout_Pin, PWM_Pin, vBat);
          delay(10);
        }
          state = states::TEMP;
        break;
      case states::SLEEP:
        op_state = 0;
        //Sleep(); //If you are using a bluetooth terminal any input wakes from sleep
        delay(1000); //If no terminal Un comment the delay() and comment the sleep function
        state = states::TEMP;
        break;
      case states::TEMP:
        temp = Read_Temp(temp_Pin);
        state = states::BLUETOOTH;
        break;
      case states::BLUETOOTH:
        Bluetooth_Send(temp, op_state, node_id);
        state = states::START;
        break;
      case states::HALT:
        break;
      }
    }
}
