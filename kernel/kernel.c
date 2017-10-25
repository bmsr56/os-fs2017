#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include"screen.h"
#include "ps2.h"
#include "tables.h"
#include "interrupt.h"
#include "interrupt_handlers.h"

/* This is a dummy function that sits around for the TSS to hop to if that ever happens.
 * It probably shouldn't happen, but if it does at least you'll know what's up.
 */
void new_main(void) {
	terminal_writestring("\nYou probably shouldn't have gotten here\n");
}

/* Kernel execution starts here! */
void kernel_main(void) {
  /* Set up various tables so interrupts will work */
	// Setting up memory connection stuff, turns off memory protection. Everything is R/W/X.
	// Look at the instruction manual for processor to do this stuff. Processor specific.
  create_tss((uintptr_t) &new_main);
  create_gdt();

	// Set up CPU Interrupts. PIC connects to a real time clock, keyboard, and other stuff. 15 or so protocols.
	// Generates hardware interrupts
	// Keyboard connected to line 1 on this PIC
  /* Set up the PIC (programmable interrupt controller):
   * IRQs from the master chip show up as interrupts 0x20-0x27;
   * IRQs from the slave chip show up as interrupts 0x28-0x2F.
   */
  PIC_remap(0x20,0x28); // hex 20 to hex 20+16
  /* Disable IRQs for all PIC devices
   * (so we don't try to jump to 0x0 when an IRQ
   * we don't want to handle fires)
   */
  IRQ_mask_all();

  /* Add an interrupt for the PS/2 keyboard (on PIC IRQ 0x1)
   * and enable that IRQ
   */
  add_idt_entry(0x21, (uintptr_t) &keypress); //number 1 event on PIC corresponds to 0x21. this is where the scancodes come from
  IRQ_clear_mask(0x1);

  /* Interrupt 0x42 prints 'hi'! */
	// set this yourself!
	// See if interrupts work
  add_idt_entry(0x42, (uintptr_t) &hi);

  /* Enable interrupts */
  enable_interrupts();

	/* Initialize terminal interface */
	terminal_initialize();

	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, kernel World!\nThis is a second line\n");

  /* Send interrupt 0x42 */
	// asm means executre assembly code inline. x86 assembly.
	// int raises an interuppt
  asm("int $0x42");

  /* Hang forever */
	//  will probably put more stuff in here
	// use this to halt and wait for interrupts before doing something
  for(;;) {
    asm("hlt");
  }
}
