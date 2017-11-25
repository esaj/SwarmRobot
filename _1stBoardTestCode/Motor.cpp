#include "Motor.h"

int16_t motorSpeed[2] = { 0, 0 };

void initMotors()
{
  pinMode(MOTOR1_PWM, OUTPUT);
  pinMode(MOTOR1_DIR, OUTPUT);
  pinMode(MOTOR2_PWM, OUTPUT);
  pinMode(MOTOR2_DIR, OUTPUT);

  //Shutdown motors
  digitalWrite(MOTOR1_PWM, 0);
  digitalWrite(MOTOR1_DIR, 0);
  digitalWrite(MOTOR2_PWM, 0);
  digitalWrite(MOTOR2_DIR, 0);
}


//Motor control
void updateMotorSpeed(int16_t motorTargetSpeed, enum motor side)
{
#ifdef REVERSE_MOTORSPEED
  motorTargetSpeed = -motorTargetSpeed;
#endif //#ifdef REVERSE_MOTORSPEED

  int pwmPin = side == LEFT ? MOTOR1_PWM : MOTOR2_PWM;
  int dirPin = side == LEFT ? MOTOR1_DIR : MOTOR2_DIR;

  if(motorTargetSpeed == 0)
  {
    //Stop immediately, if both are low (0), stand-by, both high = actual braking
    analogWrite(pwmPin, 255);
    digitalWrite(dirPin, HIGH);
    motorSpeed[side] = 0;
  }
  else
  {

    //If the direction is opposite, switch to stop immediately
    if((motorTargetSpeed > 0 && motorSpeed[side] < 0) ||
       (motorTargetSpeed < 0 && motorSpeed[side] > 0))
    {
        motorSpeed[side] = 0;
    }
    else
    {
      int16_t speedChange = abs(motorTargetSpeed - motorSpeed[side]);

      if(motorTargetSpeed > motorSpeed[side])
      {
        motorSpeed[side] += speedChange > 20 ? 20 : speedChange;

        if(motorSpeed[side] > MAX_MOTOR_PWM)
        {
          motorSpeed[side] = MAX_MOTOR_PWM;
        }
      }
      else if(motorTargetSpeed < motorSpeed[side])
      {
        motorSpeed[side] -= speedChange > 20 ? 20 : speedChange;

        if(motorSpeed[side] < -MAX_MOTOR_PWM)
        {
          motorSpeed[side] = -MAX_MOTOR_PWM;
        }
      }

      if(motorSpeed[side] > MAX_MOTOR_PWM)
      {
        motorSpeed[side] = MAX_MOTOR_PWM;
      }
      else if(motorSpeed[side] < -MAX_MOTOR_PWM)
      {
        motorSpeed[side] = -MAX_MOTOR_PWM;
      }
    }
  }

  analogWrite(pwmPin, motorSpeed[side] > 0 ? motorSpeed[side] : 255 - abs(motorSpeed[side]));
  digitalWrite(dirPin, motorSpeed[side] > 0 ? LOW : HIGH);
}

void stopMotors()
{
  updateMotorSpeed(0, LEFT);
  updateMotorSpeed(0, RIGHT);
}

void motorDirTest(uint16_t strongestReading, uint8_t strongestReadingIndex)
{
  int16_t targetForward = 0;
  int16_t targetLeft = 0;
  int16_t targetRight = 0;

  /*
  uint16_t front = lastPhotoReadings[FRONT_INDEX];
  if(front > 20)
  {
    targetForward = 255 - front / 2;
    if(front > 400 && front <= 500)
    {
      targetForward = 0;
    }
    else if(front > 500)
    {
      targetForward = -255;
    }
  }

  //Backing up
  if(lastPhotoReadings[BACK_LEFT_INDEX] > 30 && lastPhotoReadings[BACK_RIGHT_INDEX] > 30)
  {
    targetForward = -255;
  }

  //Left side
  for(int i = FRONT_LEFT_INDEX; i < BACK_RIGHT_INDEX; i++)
  {
    targetLeft += (lastPhotoReadings[i] / 4) * i;
  }

  //Right side
  for(int i = BACK_RIGHT_INDEX; i < LED_COUNT; i++)
  {
    targetRight += (lastPhotoReadings[i] / 4) * (7-i);
  }*/

  if(strongestReadingIndex != NONE_INDEX)
  {
    switch(strongestReadingIndex)
    {
      case FRONT_INDEX:
        if(strongestReading > 400 && strongestReading <= 650)
        {
          stopMotors();
        }
        else if(strongestReading > 650)
        {
          targetForward = -255;
        }
        else
        {
          targetForward = 255;
        }

        break;

      case FRONT_LEFT_INDEX:
        targetLeft = (MAX_MOTOR_PWM/2);
        targetRight = -(MAX_MOTOR_PWM/2);
        break;

      case LEFT_INDEX:
         targetLeft = MAX_MOTOR_PWM;
         targetRight = -MAX_MOTOR_PWM;
        break;

      case BACK_LEFT_INDEX:
        if(strongestReading > 300)
        {
          targetForward = (MAX_MOTOR_PWM/2);
        }
        else
        {
         targetLeft = MAX_MOTOR_PWM;
         targetRight = -MAX_MOTOR_PWM;
        }
        break;

      case BACK_RIGHT_INDEX:
        if(strongestReading > 300)
        {
          targetForward = (MAX_MOTOR_PWM/2);
        }
        else
        {
          targetLeft = -MAX_MOTOR_PWM;
          targetRight = MAX_MOTOR_PWM;
        }
        break;

      case RIGHT_INDEX:
          targetLeft = -MAX_MOTOR_PWM;
          targetRight = MAX_MOTOR_PWM;
          break;

      case FRONT_RIGHT_INDEX:
        targetLeft = -(MAX_MOTOR_PWM/2);
        targetRight = (MAX_MOTOR_PWM/2);
        break;
    }
  }
  else
  {
    updateMotorSpeed(0, LEFT);
    updateMotorSpeed(0, RIGHT);
    return;
  }

  if(abs(targetForward) > MIN_MOTOR_PWM || targetLeft > MIN_MOTOR_PWM)
  {
    updateMotorSpeed(targetForward - targetLeft, LEFT);
    updateMotorSpeed(targetForward + targetLeft, RIGHT);
  }
  else if(abs(targetForward) > MIN_MOTOR_PWM || targetRight > MIN_MOTOR_PWM)
  {
    updateMotorSpeed(targetForward + targetRight, LEFT);
    updateMotorSpeed(targetForward - targetRight, RIGHT);
  }
  else
  {
    updateMotorSpeed(0, LEFT);
    updateMotorSpeed(0, RIGHT);
  }


  //Slow down both motors so things stop if there's no signal
  if(motorSpeed[LEFT] > 0)
  {
    motorSpeed[LEFT]--;
  }
  else if(motorSpeed[LEFT] < 0)
  {
    motorSpeed[LEFT]++;
  }

  if(motorSpeed[RIGHT] > 0)
  {
    motorSpeed[RIGHT]--;
  }
  else if(motorSpeed[RIGHT] < 0)
  {
    motorSpeed[RIGHT]++;
  }
}
