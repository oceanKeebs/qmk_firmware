#pragma once

#define SPLIT_USB_DETECT
#define EE_HANDS


#ifdef OLED_ENABLE
#   define OLED_FONT_H "keyboards/oceankeebs/split67/glcdfont.c"
#   define OLED_DISPLAY_128X64
//#   define SPLIT_OLED_ENABLE
#   define SPLIT_LAYER_STATE_ENABLE
#   define SPLIT_MODS_ENABLE
#   define OLED_TIMEOUT 0
#endif


#ifdef POINTING_DEVICE_ENABLE
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#endif

/**
 *
 * TRACKPAD STUFF
 *
 */
//define behavior
#define MOUSEKEY_WHEEL_INTERVAL     50 //ms
#define MOUSEMOVEMENT_SENSITIVITY   0.50 //factor raw data to sent data
#define TRACKPAD_RATE       10

//enable / disable gestures
#define ZOOM_ENABLED            true
#define SCROLL_ENABLED          true

//physical data
#define IQS5xx_ADDR              0x74
#define RDY_PIN                  D2
#define    END_WINDOW                (uint16_t)0xEEEE
