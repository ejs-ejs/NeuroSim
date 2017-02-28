void CMD_OFF(void) {
  ROWS[0]=0x00;
  ROWS[1]=0x00;
  ROWS[2]=0x00;
  Serial.println(F("\nCommand ALL_OFF executed sucessfully"));
  }
