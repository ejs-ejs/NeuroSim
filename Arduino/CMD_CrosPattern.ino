
/* The layout is 6x4, two rows controlled by single byte
 *  top row is LSB, bottom row is MSB part 
 *  display a cross pattern like
 *  *--* < ROW[0], LSB on the right
 *  *--* < ROW[0], MSB on the left
 *  -**- < ROW[1], LSB on the right
 *  -**- < ROW[1], MSB on the left
 *  *--* < ROW[2], LSB on the right
 *  *--* < ROW[2], MSB on the left
 *  
*/

void CMD_CrosPattern(void) {
  ROWS[0]=remap(0x99);
  ROWS[1]=remap(0x66);
  ROWS[2]=remap(0x99);
  Serial.println("\nCommand CROSS executed sucessfully");
  }
