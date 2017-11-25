#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H
#include <Arduino.h>
#include <stdint.h>
#include "defines.h"

//Shift register status
extern uint16_t shiftState;
extern uint16_t oldState;

/**
 * Initializes the shift register to a known state
 */
void initShiftRegister();

/**
 * Writes the current state to the actual shift registers
 */
void writeShiftRegisterState();

/**
 * Sets given bit or bits on, note that the value won't be written
 * to the registers until writeShiftRegisterState has been
 * called.
 */
void turnOn(uint16_t bitVal);

/**
 * Sets given bit or bits off, note that the value won't be written
 * to the registers until writeShiftRegisterState has been
 * called.
 */
void turnOff(uint16_t bitVal);


uint8_t isEnabled(uint16_t bitVal);

/*
* Returns the current state set, which may not be yet written to the
* actual shift registers (depends whether writeShiftRegisterState has
* been called)
*/
inline uint16_t getCurrentBits() { return shiftState; }

/**
 * Returns the last state written to the shift registers, this is the
 * state the actual shift registers are in
 */
inline uint16_t getLastActiveBits() { return oldState; }

#endif //#ifndef SHIFTREGISTER_H
