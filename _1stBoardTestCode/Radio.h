#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>
#include <stdint.h>
#include "defines.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

struct List{
  char idOwn;
  char brightness;
  char idCurrent;
  char groupSize;
  char singleBits;//bit0: ownBeaconMode bit1: ownMoved bit2: rob1Moved bit3: rob2Moved bit4: rob3Moved bit5: rob4Moved
  char visibleRobots[3][4];
  char otherRobots[14][4];
};
extern struct List listRobots;

#define UNCONNECTED 16
#define IDCONFLICT 32
#define MEASURING1 40
#define MEASURING2 41
#define MEASURING3 42
#define STANDING 48
#define WANTTOMOVE 64
#define MOVING 65
#define BEACON1 66
#define BEACON2 67
#define WAITING 68
#define SPREADINGOUT 80

void initRadio();
void checkRadio();
char write(char flag);
char callculateNextID();
int createProtocol(char *msg, char maxSizeMsg);
char read(char flag);
void readProtocol(char *message);

#endif // #ifndef RADIO_H
