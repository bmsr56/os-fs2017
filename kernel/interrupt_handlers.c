#include "interrupt_handlers.h"
 // yanks you out of what the cpu was doing and puts you into this code
 // saves cpu registers somewhere
 // when it returns it puts those registers back

__attribute__((interrupt))
void keypress(void* frame)
{
  char buf[3];
  getScancodeByte(buf);
  terminal_writestring(buf);
  PIC_sendEOI(0x1); // I saw the interrupt and did something
}

__attribute__((interrupt))
void hi(void* frame)
{
  terminal_writestring("hi!\n");
}
