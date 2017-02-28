void CMD_help(void) {
  Serial.println(F("\n\nThis is NeuroSim simulator"));
  Serial.print(F("\t version "));
  Serial.println(__VERSION);
  Serial.println(F("=== COMMANDS ========================="));
  Serial.println(F(" ALL_ON   - to turn all LEDs on"));
  Serial.println(F(" ALL_OFF  - to turn all LEDs off"));
  Serial.println(F(" CROSS    - to show cross pattern"));
  Serial.println(F(" SMILEY   - to show smiley"));
  Serial.println(F(" A1       - to show dot in A1 position"));
  Serial.println(F(" or any controll commans, starting from 'x' \n\t\tand ending with 'y', '\\n' or '\\r'"));
  Serial.println(F("=== LED addressing ===================\n"));
  Serial.println(F("\t A4\t A3\t A2\t A1"));
  Serial.println(F("\t A8\t A7\t A6\t A5"));
  Serial.println(F("\t B4\t B3\t B2\t B1"));
  Serial.println(F("\t B8\t B7\t B6\t B5"));
  Serial.println(F("\t C4\t C3\t C2\t C1"));
  Serial.println(F("\t C8\t C7\t C6\t C5"));
  Serial.println(F("======================================\n"));

}
