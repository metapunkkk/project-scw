void loop() {
  delay(5);
  if(sys_active==true && timer>=mx_time){
    sys_stop();
    timer=0;
    cli();
    TIMSK1 &= ~(1 << OCIE1A);
    sei(); 
  }
  
}
  
