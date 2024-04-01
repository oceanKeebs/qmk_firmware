#include "fauxkl.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE

// Forward declare RP2040 SDK declaration.
void gpio_init(uint gpio);

void keyboard_pre_init_kb(void) {
    // Ensures that GP26 through GP29 are initialized as digital inputs (as
    // opposed to analog inputs).  These GPIOs are shared with A0 through A3,
    // respectively.  On RP2040-B2 and later, the digital inputs are disabled by
    // default (see RP2040-E6).
    gpio_init(GP26);
    gpio_init(GP27);
    gpio_init(GP28);
    gpio_init(GP29);

    keyboard_pre_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }

// #ifdef RGBLIGHT_ENABLE
//     rgblight_enable_noeeprom();
//     rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
//     rgblight_setrgb(RGB_RED);
// #endif // RGBLIGHT_ENABLE

// #ifdef RGB_MATRIX_ENABLE
//     void rgb_matrix_update_pwm_buffers(void);
//     rgb_matrix_set_color_all(RGB_RED);
//     rgb_matrix_update_pwm_buffers();
// #endif // RGB_MATRIX_ENABLE
    return true;
}
