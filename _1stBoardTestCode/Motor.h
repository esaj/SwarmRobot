#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <stdint.h>
#include "defines.h"

//Motor states
//Static because of inlining of getMotorSpeed, still, not meant to be touched directly
extern int16_t motorSpeed[2];
enum motor { LEFT = 0, RIGHT = 1 };
#define MIN_MOTOR_PWM 75
#define MAX_MOTOR_PWM 152

void initMotors();

void updateMotorSpeed(int16_t motorTargetSpeed, enum motor side);

void stopMotors();

void motorDirTest(uint16_t strongestReading, uint8_t strongestReadingIndex);

extern inline int16_t getMotorSpeed(motor side) { return motorSpeed[side]; }

#endif // #ifndef MOTOR_H
