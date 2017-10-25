#pragma once
#include <stdint.h>
#include "port.h"

/* Gets the current scancode from the keyboard
 * and converts it into 2 hex digits
 */
void getScancodeByte(char* buf);

/* Get the current scancode from the keyboard */
uint8_t getScancode();

/* Loops until the keyboard scancode updates,
 * then converts the scancode into 2 hex digits
 *
 * You should probably not use this--the CPU just sits in a loop
 * reading the keyboard, so you can't really multitask here.
 * Use getScancodeByte() and an interrupt handler instead.
 */
void getScancodeByte_loop(char* buf);

/* Loops until the keyboard scancode updates,
 * then returns the new scancode.
 */
uint8_t getScancode_loop();

/* Given a byte, represent it as 2 hex digits */
void byte2chars(uint8_t byte, char* buf);
