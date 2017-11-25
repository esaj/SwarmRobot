#include "ShiftRegister.h"

uint16_t shiftState = 0;
uint16_t oldState = 0xFFFF;

void writeShiftRegisterState()
{
  /*
  //The simple version, digitalWrite is slow
  digitalWrite(SHIFT_STORE, LOW);
  shiftOut(SHIFT_DATA, SHIFT_CLOCK, MSBFIRST, shiftState);
  shiftOut(SHIFT_DATA, SHIFT_CLOCK, MSBFIRST, shiftState >> 8);
  digitalWrite(SHIFT_STORE, HIGH);
  */

  //Bail out if the state is the same, no need to rewrite it
  if(oldState == shiftState)
  {
    return;
  }

  //Set shift & store low (although they already should be, but just in case there's some "funny" state at start up or such)
  bit_clear(PORTC, PORTC_SHIFT_STORE | PORTC_SHIFT_STORE);

  //Value is shifted on rising edge of SHIFT_CLOCK, go through the shiftState bit-by-bit
  for(int i = 15; i >= 0; i--)
  {
    //Note that the data is written MSB first (as the first bit entered will be the value of the last output of the shift registers)
    uint8_t nextBit = (shiftState >> i) & 1;
    bit_write(nextBit, PORTC, PORTC_SHIFT_DATA);
    bit_set(PORTC, PORTC_SHIFT_CLOCK);
    bit_clear(PORTC, PORTC_SHIFT_CLOCK);
  }

  //Store value (ie. activate shift-register outputs to current values)
  bit_set(PORTC, PORTC_SHIFT_STORE);

  oldState = shiftState;
}

void turnOn(uint16_t bitVal)
{
  bit_set(shiftState, bitVal);
}

void turnOff(uint16_t bitVal)
{
  bit_clear(shiftState, bitVal);
}

uint8_t isEnabled(uint16_t bitVal)
{
  return (shiftState & bitVal) > 0 ? 1 : 0;
}

void initShiftRegister()
{
  //Write out the shift register, the reset- and output enable -pins are not available so the state can be pretty much anything at start up
  shiftState = RGB_R | PHOTOREAD_DISABLE; //Just turn on the red led and disable analog multiplexer
  writeShiftRegisterState();
}
