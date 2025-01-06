#pragma once

#define OLED_DISPLAY_128X32
#define OLED_TIMEOUT 60000

/* ChibiOS I2C definitions */
#define I2C_DRIVER              I2CD1
#define I2C1_SDA_PIN            GP2
#define I2C1_SCL_PIN            GP3
#define I2C1_CLOCK_SPEED        400000              //100000 (use for slow/standard mode)
#define I2C1_DUTY_CYCLE         FAST_DUTY_CYCLE_2   //STD_DUTY_CYCLE (use for slow/standard mode)

/* definitions of expander adresses of the connected side modules */
#define PORT_EXPANDER0_ADDRESS  0x20
#define PORT_EXPANDER1_ADDRESS  0x21
#define PORT_EXPANDER2_ADDRESS  0x22
#define PORT_EXPANDER3_ADDRESS  0x23

/* TRACKPAD STUFF */
#define TRACKPAD_RATE           10
// enable/disable gestures
#define ZOOM_ENABLED            TRUE
#define SCROLL_ENABLED          TRUE
// I2C settings
#define IQS5xx_ADDR             0x74
#define RDY_PIN                 GP26
#define END_WINDOW              (uint16_t)0xEEEE
// for how long taps are ignored after a tap happened, helps with unwanted doubletaps
#define MOUSEBUTTON_DEADTIME    50 //ms
// mouse cursor sensitivity
#define TRACKPAD_SENSITIVITY    15 // usually between 10 and 20