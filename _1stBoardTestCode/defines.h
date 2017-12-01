#ifndef PROJECT_DEFINES_H
#define PROJECT_DEFINES_H

//Feature set
//#define DISPLAY_ENABLED   //Enables display, note that the robot won't do anything if this is enabled and there's no display

#define DISABLE_MOTORS      //Completely disables (removes) all motor control code. Meant for testing stuff when you don't
                            //want the robot to start moving around
#define REVERSE_MOTORSPEED  //Reverses the PWM-control for motors, needed for robots #2-5 (as robot #1 had different motors
                            //with reversed direction vs. the others, and of course I wired the motors according to #1 directions)


//Bit manipulation macros
#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define bit_flip(p,m) ((p) ^= (m))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
#define BIT(x) (0x01 << (x))


//**** Pin definitions
//Photodiode signal input
#define PHOTO_IN A0

//LDR
#define LDR_IN A7

//Shift register (74HC595)
#define SHIFT_CLOCK A1
#define SHIFT_STORE A2
#define SHIFT_DATA A3

//Direct port manipulation for faster writing
#define PORTC_SHIFT_MASK B00001110
#define PORTC_SHIFT_CLOCK BIT(1)
#define PORTC_SHIFT_STORE BIT(2)
#define PORTC_SHIFT_DATA BIT(3)

//Radio pins
#define RADIO_IRQ 2
#define RADIO_CE 7
#define RADIO_CSN 8
#define RADIO_MOSI 11
#define RADIO_MISO 12
#define RADIO_SCK 13

//Motor outputs
#define MOTOR1_PWM 6
#define MOTOR1_DIR 3
#define MOTOR2_PWM 5
#define MOTOR2_DIR 4

//**** Shift registers
//Leds/photodiodes are positioned as such:
/*
 +--------------------+
 |LED4   LED3     LED2|
 |                LED1|   -- Front --> (motors are on the front side)
 |LED5   LED6     LED7|
 +--------------------+
*/
//1st byte LSB is unused (unconnected in chip)
#define LED1 BIT(1)
#define LED2 BIT(2)
#define LED3 BIT(3)
#define LED4 BIT(4)
#define LED5 BIT(5)
#define LED6 BIT(6)
#define LED7 BIT(7)
#define ALL_LEDS 0xFE

//2nd byte LSB is unused (unconnected in chip)
#define RGB_B BIT(9)
#define RGB_G BIT(10)
#define RGB_R BIT(11)
#define PHOTOREAD_DISABLE BIT(12)  //NOTE: Active low
#define PHOTOREAD_C BIT(13)
#define PHOTOREAD_B BIT(14)
#define PHOTOREAD_A BIT(15)
#define PHOTOREAD_CHANNEL_MASK 0xE000


//** Robot status data
#define LED_COUNT 7
#define FILTER_ALPHA 0.3f

//Indices for directions of LEDs/readings
#define FRONT_INDEX 0
#define FRONT_LEFT_INDEX 1
#define LEFT_INDEX 2
#define BACK_LEFT_INDEX 3
#define BACK_RIGHT_INDEX 4
#define RIGHT_INDEX 5
#define FRONT_RIGHT_INDEX 6
#define NONE_INDEX 127

//Minimum difference for strongest reading vs. average required for the robot to react
#define MINREADING_DIFF_TO_AVERAGE 20

#endif //#ifndef PROJECT_DEFINES_H
