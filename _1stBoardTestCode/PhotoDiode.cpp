#include "PhotoDiode.h"

uint16_t lastPhotoReadings[LED_COUNT];
uint8_t strongestReadingIndex = NONE_INDEX;
uint16_t strongestReading = 0;
uint16_t averageReading = 0;

void initPhotoDiodes()
{
  pinMode(PHOTO_IN, INPUT);
  memset(lastPhotoReadings, 0, LED_COUNT * sizeof(uint16_t));
}

void measurePhotoDiode(uint8_t diodeNumber)
{
  //Select the correct channel
  ((diodeNumber & 1) > 0) ? turnOn(PHOTOREAD_A) : turnOff(PHOTOREAD_A);
  ((diodeNumber & 2) > 0) ? turnOn(PHOTOREAD_B) : turnOff(PHOTOREAD_B);
  ((diodeNumber & 4) > 0) ? turnOn(PHOTOREAD_C) : turnOff(PHOTOREAD_C);

  turnOff(PHOTOREAD_DISABLE);
  writeShiftRegisterState();

  //Let the value settle a bit
  //TODO: Is this needed really?
  delay(1);

  //Filter the value a bit
  lastPhotoReadings[diodeNumber] = (uint16_t)((1.0f - FILTER_ALPHA) * analogRead(PHOTO_IN) + FILTER_ALPHA * lastPhotoReadings[diodeNumber]);
  //lastPhotoReadings[diodeNumber] = (uint16_t)(((uint32_t)1023*lastPhotoReadings[diodeNumber] + (uint32_t)analogRead(PHOTO_IN)) / 1024);

  turnOn(PHOTOREAD_DISABLE);
  writeShiftRegisterState();
}

void measureAllPhotoDiodes()
{
  for(int i = 0; i < LED_COUNT; i++)
  {
    measurePhotoDiode(i);
  }

  averageReading = 0;
  uint32_t tempAvg;
  strongestReading = 0;
  for(int i = 0; i < LED_COUNT; i++)
  {
    uint16_t r = lastPhotoReadings[i];
    tempAvg += r;
    if(r > strongestReading)
    {
      strongestReading = r;
      strongestReadingIndex = i;
    }
  }

  averageReading = (uint16_t)(tempAvg/LED_COUNT);

  if((strongestReading - averageReading) < MINREADING_DIFF_TO_AVERAGE)
  {
    strongestReadingIndex = NONE_INDEX;
    strongestReading = 0;
  }
}
