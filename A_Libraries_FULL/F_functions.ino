void sys_start(){
  sys_active = true;
  Serial.println("&");
  digitalWrite(led2, HIGH);
  cli();
  TIMSK1 |= (1 << OCIE1A);
  sei();
  myDFPlayer.start();
  
}

void sys_stop(){
  
  sys_active = false;
  digitalWrite(led2, LOW);
  digitalWrite(led1 , LOW);
  myDFPlayer.stop();
  
}
