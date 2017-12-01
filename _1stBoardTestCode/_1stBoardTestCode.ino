#include <Arduino.h>

#include <stdint.h>
#include <stdlib.h>
#include "proto_thread.h" //Simple co-operative threading
#include "defines.h"

#ifdef DISPLAY_ENABLED
  #include "SSD1306AsciiAvrI2C.h" //OLED driver
#endif  //#ifdef DISPLAY_ENABLED

#ifndef DISABLE_MOTORS
  #include "Motor.h"
#endif


#include "Radio.h"
#include "PhotoDiode.h"
#include "ShiftRegister.h"

uint16_t lastLDRReading = 0;

//Protothread for sensor update
pt sensorPt;
pt radioPt;


#ifdef DISPLAY_ENABLED
  //**** OLED for testing
  #define I2C_ADDRESS 0x3C
  SSD1306AsciiAvrI2c SSD1306;

  //Protothread for display update
  pt displayPt;

  //Text buffer for writing to display
  #define CHARBUFFER_SIZE 16
  char textBuffer[CHARBUFFER_SIZE];
#endif //#ifdef DISPLAY_ENABLED

#ifndef DISABLE_MOTORS
  //Protothread for motor update
  pt motorPt;
#endif //#ifndef DISABLE_MOTORS


//*** Testing
uint32_t timer = 0;
uint8_t rgb = 0;



void setup()
{

  Serial.begin(9600); //For debugging


  initPhotoDiodes();
  initRadio();

  pinMode(LDR_IN, INPUT);

  //Analog pins used as digital outputs
  pinMode(SHIFT_CLOCK, OUTPUT);
  pinMode(SHIFT_STORE, OUTPUT);
  pinMode(SHIFT_DATA, OUTPUT);

#ifndef DISABLE_MOTORS
  initMotors();
  PT_INIT(&motorPt);
#endif //#ifndef DISABLE_MOTORS

  pinMode(RADIO_IRQ, INPUT);
  pinMode(RADIO_CE, OUTPUT);
  pinMode(RADIO_CSN, OUTPUT);
  pinMode(RADIO_MOSI, OUTPUT);
  pinMode(RADIO_MISO, INPUT);
  pinMode(RADIO_SCK, OUTPUT);

  initShiftRegister();

#ifdef DISPLAY_ENABLED
  //Set up the display
  SSD1306.begin(&Adafruit128x64, I2C_ADDRESS);
  SSD1306.setFont(Adafruit5x7);
  SSD1306.clear();

  memset(textBuffer, '\0', 16);
  PT_INIT(&displayPt);
#endif //#ifdef DISPLAY_ENABLED

  PT_INIT(&sensorPt);
  PT_INIT(&radioPt);
}

void measureLDR()
{
  lastLDRReading = analogRead(LDR_IN);
  //Serial.println(lastLDRReading);
}

#ifdef DISPLAY_ENABLED
  void fillLedStatesToTextBuffer()
  {
    memset(textBuffer, '\0', 16);
    strcpy(textBuffer, "LEDS: ");
    uint8_t offset = 5;
    for(int i = 0; i <= LED_COUNT; i++)
    {
      textBuffer[offset++] = isEnabled(LED1 << i) ? '1' : '0';
    }
  }

  void writeToDisplay(int x, int y, const char* text, int size = 1)
  {
    if(size == 1)
    {
      SSD1306.set1X();
    }
    else
    {
      SSD1306.set2X();
    }

    if(x > -1)
    {
      SSD1306.setCol(x);
    }
    if(y > -1)
    {
      SSD1306.setRow(y);
    }

    int i = 0;

    while(text[i] != '\0')
    {
      SSD1306.write(text[i++]);

      //Bail out after CHARBUFFER_SIZE chars, in case the null-termination is missing
      if(i == CHARBUFFER_SIZE)
      {
        break;
      }
    }
  }


  PT_THREAD(updateDisplay(struct pt *pt))
  {
    PT_BEGIN(pt);
    while(1)
    {
      PT_WAIT_MS(pt, 100);

      /*
      fillLedStatesToTextBuffer();
      writeToDisplay(0, 0, textBuffer);
      */

      writeToDisplay(0, 0, "LDR: ", 1);
      itoa(lastLDRReading, textBuffer, 10);
      writeToDisplay(-1, -1, textBuffer, 1);

      /*
         +--------------------+
         |LED4   LED3     LED2|
         |                LED1|   -- Front --> (motors are on the front side)
         |LED5   LED6     LED7|
         +--------------------+
      */

      itoa(getLastPhotoReading(3), textBuffer, 10);
      writeToDisplay(0, 2, "    ", 1);
      writeToDisplay(0, 2, textBuffer, 1);

      itoa(getLastPhotoReading(2), textBuffer, 10);
      writeToDisplay(40, 2, "    ", 1);
      writeToDisplay(40, 2, textBuffer, 1);

      itoa(getLastPhotoReading(1), textBuffer, 10);
      writeToDisplay(80, 2, "    ", 1);
      writeToDisplay(80, 2, textBuffer, 1);

      itoa(getLastPhotoReading(0), textBuffer, 10);
      writeToDisplay(100, 3, "    ", 1);
      writeToDisplay(100, 3, textBuffer, 1);

      itoa(getLastPhotoReading(4), textBuffer, 10);
      writeToDisplay(0, 4, "    ", 1);
      writeToDisplay(0, 4, textBuffer, 1);

      itoa(getLastPhotoReading(5), textBuffer, 10);
      writeToDisplay(40, 4, "    ", 1);
      writeToDisplay(40, 4, textBuffer, 1);

      itoa(getLastPhotoReading(6), textBuffer, 10);
      writeToDisplay(80, 4, "    ", 1);
      writeToDisplay(80, 4, textBuffer, 1);

#ifndef DISABLE_MOTORS
      itoa(getMotorSpeed(LEFT), textBuffer, 10);
      writeToDisplay(0, 5, "LEFT: ", 1);
      writeToDisplay(-1, -1, textBuffer, 1);

      itoa(getMotorSpeed(RIGHT), textBuffer, 10);
      writeToDisplay(60, 5, "RIGHT: ", 1);
      writeToDisplay(-1, -1, textBuffer, 1);
#endif //#ifndef DISABLE_MOTORS
    }
    PT_END(pt);
  }

#endif //#ifdef DISPLAY_ENABLED

PT_THREAD(updateSensors(struct pt *pt))
{
  PT_BEGIN(pt);
  while(1)
  {
    PT_WAIT_MS(pt, 100);

    measureLDR();
    measureAllPhotoDiodes();
  }
  PT_END(pt);
}

PT_THREAD(updateRadio(struct pt *pt))
{
  PT_BEGIN(pt);
      
  while(1)
  {
    
    PT_WAIT_MS(pt, 1000);
    checkRadio();
    
    //*************************************************************************************************
    //*************************************************************************************************
    //*************************************************************************************************
  }
  PT_END(pt);
}

#ifndef DISABLE_MOTORS
  PT_THREAD(updateMotors(struct pt *pt))
  {
    PT_BEGIN(pt);
    while(1)
    {
      PT_WAIT_MS(pt, 20);

      motorDirTest(getStrongestPhotoReading(), getStrongestPhotoReadingIndex());
    }
    PT_END(pt);
  }
#endif //#ifndef DISABLE_MOTORS


void setIRLEDs(bool on)
{
  on ? turnOn(ALL_LEDS) : turnOff(ALL_LEDS);
}


void loop()
{
#ifdef DISPLAY_ENABLED
  updateDisplay(&displayPt);
#endif  //#ifdef DISPLAY_ENABLED

  updateSensors(&sensorPt);
  updateRadio(&radioPt);
  if(lastLDRReading > 500)
  {
    setIRLEDs(false);
    turnOn(RGB_B);
    turnOff(RGB_G | RGB_R);
    writeShiftRegisterState();

    #ifndef DISABLE_MOTORS
      updateMotors(&motorPt);
    #endif  //#ifndef DISABLE_MOTORS
  }
  else
  {
    //Turn on IR-leds, shutdown motors
    #ifndef DISABLE_MOTORS
      stopMotors();
    #endif
    turnOff(RGB_G | RGB_B);
    turnOn(RGB_R);
    setIRLEDs(true);
    writeShiftRegisterState();
  }

  /*
  //RGB LED color test
  if(millis() - timer > 1000)
  {
    rgb++;
    (rgb & 1) > 0 ? turnOn(RGB_R) : turnOff(RGB_R);
    ((rgb >> 1) & 1) > 0 ? turnOn(RGB_G) : turnOff(RGB_G);
    ((rgb >> 2) & 1) > 0 ? turnOn(RGB_B) : turnOff(RGB_B);
    if(rgb == 8)
    {
      turnOff(RGB_R | RGB_G | RGB_B);
      rgb = 0;
    }
    writeShiftRegisterState();
    timer = millis();
  }
  */
}
