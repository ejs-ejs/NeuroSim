unsigned int remap(unsigned int arg) {
  /* remap bits for display
   *  0 1 2 3 4 5 6 7
   *  a b c d e f g h
   *  
   *  goes to 
   *  0 1 2 3 4 5 6 7
   *  a   b   c   d
   *    e   f   g   h
   */
   unsigned int res=0;

   for (unsigned short i=1; i<7; i++) {
    res |= arg & B1; //segment "a"
    res |= arg & B10 ? (1 << 2) : 0; // segment "b"
    res |= arg & B100 ? (1 << 4) : 0; // segment "c"
    res |= arg & B1000 ? (1 << 6) : 0; // segment "d"
    res |= arg & B10000 ? (1 << 1) : 0; // segment "e"
    res |= arg & B100000 ? (1 << 3) : 0; // segment "f"
    res |= arg & B1000000 ? (1 << 5) : 0; // segment "f"
    res |= arg & B10000000 ? (1 << 7) : 0; // segment "h"
    }
    return res;
  }
