#ifndef PHOTODIODE_H
#define PHOTODIODE_H

#include <Arduino.h>
#include <stdint.h>
#include "defines.h"
#include "ShiftRegister.h"

//** Robot status data
extern uint16_t lastPhotoReadings[LED_COUNT];

//Tracking strongest reading from all photodiodes
extern uint8_t strongestReadingIndex;
extern uint16_t strongestReading;
//Average reading is used to try to filter out ambient IR-radiation, so if the strongest
//reading is close to ambient "noise", no reaction should occur
extern uint16_t averageReading;

void initPhotoDiodes();
void measurePhotoDiode(uint8_t diodeNumber);
void measureAllPhotoDiodes();

extern inline uint16_t getLastPhotoReading(uint8_t index) { return lastPhotoReadings[index]; }
extern inline uint16_t getStrongestPhotoReading() { return strongestReading; }
extern inline uint16_t getStrongestPhotoReadingIndex() { return strongestReadingIndex; }
extern inline uint16_t getAveragePhotoReading() { return averageReading; }

#endif //#ifndef PHOTODIODE_H
