
// command inteface
#include <SerialCommand.h>
SerialCommand sCmd;     // The SerialCommand object


#define __VERSION "0.1a"
#define _Baudrate 115200
#define NEUROSIM_DEBUG 1

//#define NEUROSIM_USE_ISR 1


// data: Data Segment, Active High
// Pin connected to pin14/mtx8,3/ DS of 74HC595
#define DS_H 9
#define DS_L 10

// Latch, rising edge
//Pin connected to pin12/mtx9,5/ST_CP of 74HC595
#define STCP_H 3
#define STCP_L 4

// clock, rising edge
//Pin connected to pin11/mtx10,6/SH_CP of 74HC595
#define SHCP_H 5
#define SHCP_L 6

// Output Enable pin13/mtx4/O-E
#define OE 7

// Memory Reset pin10/mtx7/M-R
#define MR 8

//number of rows
#define NUM_ROWS 3

// current row
unsigned int CR=0;

// flag: display symbols
byte CAN_DISPLAY=1;

// rows
unsigned short ROWS[NUM_ROWS];


//prototype
//unsigned int remap(unsigned int);

#ifdef NEUROSIM_USE_ISR

// display current row at interrupt
ISR(TIMER1_OVF_vect)  {
  if (CAN_DISPLAY) {
    
    // clear registers on 595
    digitalWrite(STCP_H, LOW);
    digitalWrite(STCP_H, HIGH);
    digitalWrite(OE,HIGH);  // disable output
    digitalWrite(MR,LOW); 
    
    //shift out column
    digitalWrite(STCP_H, LOW);
    shiftOut(DS_H, SHCP_H, MSBFIRST, ROWS[CR]); 
    digitalWrite(STCP_H, HIGH);
  
   //shift out row
    digitalWrite(STCP_L, LOW);
    shiftOut(DS_L, SHCP_L, MSBFIRST, CR);
    digitalWrite(STCP_L, HIGH);
  
    // enabele output
    digitalWrite(OE,LOW); 
    digitalWrite(MR,HIGH);
    
    if (++CR > NUM_ROWS) { //prepare CR for next cycle
      CR=0;
      } 
  }
}
#endif

#ifndef NEUROSIM_USE_ISR
void updateMTX(void)  {
  if (CAN_DISPLAY) {
    // disable output
  //  digitalWrite(OE,1); 
    #ifdef NEUROSIM_DEBUG
  Serial.println(F("\t[updateMTX] disabling output"));
    #endif
    
    // clear registers on 595
 //   digitalWrite(MR,1); 
 //   digitalWrite(MR,0);
    #ifdef NEUROSIM_DEBUG
  Serial.println(F("\t\t[updateMTX] registers cleared"));
    #endif
    
    //shift out column
    #ifdef NEUROSIM_DEBUG
  Serial.print(F("\t\t[updateMTX] shifting out row "));
  Serial.print(CR);
  Serial.print(" :\t");
  Serial.println(ROWS[CR], HEX);
    #endif
    
    digitalWrite(STCP_H, LOW);
    shiftOut(DS_H, SHCP_H, LSBFIRST, ROWS[CR]); 
    digitalWrite(STCP_H, HIGH);
  
   //shift out row
    digitalWrite(STCP_L, LOW);
    shiftOut(DS_L, SHCP_L, LSBFIRST, CR);
    digitalWrite(STCP_L, HIGH);
  
    // enabele output
  //  digitalWrite(OE,0); 
    #ifdef NEUROSIM_DEBUG
  Serial.println("\t[updateMTX] enabling output");
    #endif
    
   //prepare CR for next cycle
    if (++CR >= NUM_ROWS) {
      CR=0;
      }
  }
}
#endif

void setup() {
  // put your setup code here, to run once:
pinMode(DS_H, OUTPUT);
pinMode(DS_L, OUTPUT);

pinMode(STCP_H, OUTPUT);
pinMode(STCP_L, OUTPUT);

pinMode(SHCP_H, OUTPUT);
pinMode(SHCP_L, OUTPUT);

pinMode(OE, OUTPUT);
pinMode(MR, OUTPUT);

//init rows with smiley
CMD_smiley();

// start serial port
  Serial.begin(_Baudrate);
  delay(300);

  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("ALL_ON", CMD_ON);          // all LEDs on
  sCmd.addCommand("ALL_OFF", CMD_OFF);         // all LEDs off
  sCmd.addCommand("CROSS", CMD_CrosPattern);   // cross pattern
  sCmd.addCommand("SMILEY", CMD_smiley);   // smiley pattern
  sCmd.addCommand("A1", CMD_A1);   // light up A1 pixel
  sCmd.addCommand("?", CMD_help);        // help un use
  sCmd.setDefaultHandler(CMD_parse);      // parse default string

  Serial.println(F("\nThis is NeuroSim simulator"));
  Serial.print(F("\t version "));
  Serial.println(__VERSION);
  delay(300);

  // enable matrix
    digitalWrite(OE,LOW); 
    digitalWrite(MR,LOW); 

#ifdef NEUROSIM_USE_ISR
  // set up interrups ant ISR
 // set timer1 interrupt at 75Hz
//  noInterrupts();           // disable all interrupts
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 75hz increments
  OCR1A = 0xD0;// = (16*10^6) / (1*1024) / 74
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
//   interrupts();             // enable all interrupts
#endif

}

void loop() {
  // read serial port
  sCmd.readSerial();
#ifndef NEUROSIM_USE_ISR
  delay(1500);
  updateMTX();
 #endif
}
