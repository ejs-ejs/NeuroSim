
void CMD_parse() {
  unsigned short bContinue=1;
  unsigned short cRow;
  unsigned short cRows[3];
  cRows[0]=0;
  cRows[1]=0;
  cRows[2]=0;
  
  char *arg;
  char *arg2;

  Serial.print(F("Processing command "));
  arg = sCmd.current();

 if (strcmp(arg[0],'x') == 0 ) {
  Serial.print(F("\n\t[PARSER] at 'x': '"));
  Serial.print(arg[0]);
  Serial.print(F("' command found at "));
  Serial.println(arg);
  
  unsigned int cIndex=1;
  while (bContinue) {
    if (cIndex >= sizeof(arg)){
      bContinue=0;
      } else {
        if (strcmp(arg[cIndex],'y') == 0) {
           bContinue=0;
           }
        if (strcmp(arg[cIndex],"\n") == 0) {
            bContinue=0;
        }
        if (strcmp(arg[cIndex],"\r") == 0) {
            bContinue=0;
        }
      
        // switch(arg[cIndex]) {
        if (strcmp(arg[cIndex],'A') == 0) {
            unsigned int cCol = atoi(arg[cIndex+1]);
            cRows[0] |= pinSet(cCol, 'A');
        } else if (strcmp(arg[cIndex],'B') == 0) {
            unsigned int cCol = atoi(arg[cIndex+1]);
            cRows[1] |= pinSet(cCol, 'B');
        } else if (strcmp(arg[cIndex],'C') == 0) {
            unsigned int cCol = atoi(arg[cIndex+1]);
            cRows[2] |= pinSet(cCol, 'C');
        } else if (strcmp(arg[cIndex],'g') == 0) {
            Serial.println(F("\n\t[PARSER] 'g' command unsupported in this configuration, ignored"));
         } else if (strcmp(arg[cIndex],'f') == 0) {
            Serial.println(F("\n\t[PARSER] 'f' command unsupported in this configuration, ignored"));
          } else if (strcmp(arg[cIndex],'e') == 0) {
            Serial.println(F("\n\t[PARSER] 'e' command unsupported in this configuration, ignored"));
          } else {
            Serial.print(F("\n\t[PARSER]: Unknown symbol found: "));
            Serial.println(arg[cIndex]);
          }
      // advance cIndex by 2 positions
      cIndex += 2;
      } // cIndex< sizeof(arg)
      Serial.print(F("\nCommand '"));
      Serial.print(arg);
      Serial.println(F("' executed sucessfully"));
      Serial.println(F(" Rows right now:"));
      Serial.print("A: ");
      Serial.println(cRows[0], HEX);
      Serial.print("B: ");
      Serial.println(cRows[1], HEX);
      Serial.print("C: ");
      Serial.println(cRows[2], HEX);
    } // end of WHILE loop

    // copy parsed string to global variable
    CAN_DISPLAY=0;
    for (unsigned int i=0; i<NUM_ROWS;i++) {
      ROWS[i] = remap(cRows[i]);
      }
     CAN_DISPLAY=1;
      
  } else {
  Serial.print(F("\n\tUnknown command "));
  Serial.println(arg);
  }
}

unsigned short pinSet(unsigned short cPin, char cRow) {
#ifdef NEUROSIM_DEBUG
  Serial.print(F("\n\t[pinSet] Row "));
  Serial.print(cRow);
  Serial.print(F(" pin "));
  Serial.println(cPin);
#endif
  if (cPin < 8) {
    unsigned short cRow = 1<<(cPin-1); // set bit in byte
#ifdef NEUROSIM_DEBUG
    Serial.print(F("\n\t[pinSet] Row "));
    Serial.print(cRow);
    Serial.print(F(" pin "));
    Serial.println(cPin);
#endif
   } else {
    Serial.print(F("\n\t[pinSet] illegal pin "));
    Serial.print(cRow);
    Serial.println(cPin);
  }
  return cRow;
}


