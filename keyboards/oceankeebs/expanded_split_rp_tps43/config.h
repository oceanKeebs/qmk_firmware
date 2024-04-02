#pragma once

#define OLED_DISPLAY_128X32


/* ChibiOS SPI definitions */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19
#define SPI_MISO_PIN GP20

/* ChibiOS I2C definitions */
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3
#define I2C1_CLOCK_SPEED 400000   //100000
#define I2C1_DUTY_CYCLE  FAST_DUTY_CYCLE_2   //STD_DUTY_CYCLE

/* Split board definitions of expander adresses */
#define PORT_EXPANDER0_ADDRESS 0x20
#define PORT_EXPANDER1_ADDRESS 0x21

/**
 *
 * TRACKPAD STUFF
 *
 */
#define MOUSEKEY_INTERVAL           8
#define MOUSEKEY_DELAY              0
#define MOUSEKEY_TIME_TO_MAX        60
#define MOUSEKEY_MAX_SPEED          6
#define MOUSEKEY_WHEEL_DELAY        400
#define MOUSEWHEEL_SENSITIVITY      1
#define TRACKPAD_RATE       10
//enable / disable gestures
#define ZOOM_ENABLED            FALSE
#define SCROLL_ENABLED          TRUE

#define IQS5xx_ADDR              0x74
#define RDY_PIN                  D2
#define    END_WINDOW                (uint16_t)0xEEEE
