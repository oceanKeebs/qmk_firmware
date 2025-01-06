#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     
    [0] = LAYOUT(
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , XXXXXXX, XXXXXXX, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, KC_UP,   KC_ESC,  KC_2 , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , XXXXXXX, XXXXXXX, KC_Z   , KC_U   , KC_I   , KC_O   , KC_P   , KC_SLSH, KC_BSLS, KC_UP,   XXXXXXX, XXXXXXX,
            XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_3, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , XXXXXXX, XXXXXXX, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4, KC_Y   , KC_X   , KC_C   , KC_V   , KC_B   , KC_LBRC, KC_RBRC, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_MINS, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_5, MO(1)  , KC_LGUI, KC_LCTL, KC_ENT , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC , KC_BSPC, KC_RALT, MO(1)  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_6 , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , XXXXXXX, XXXXXXX, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, KC_UP,   KC_ESC,  KC_7 , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , XXXXXXX, XXXXXXX, KC_Z   , KC_U   , KC_I   , KC_O   , KC_P   , KC_SLSH, KC_BSLS, KC_UP,   XXXXXXX, XXXXXXX,
            XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_8, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , XXXXXXX, XXXXXXX, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_9, KC_Y   , KC_X   , KC_C   , KC_V   , KC_B   , KC_LBRC, KC_RBRC, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_MINS, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(1)  , KC_LGUI, KC_LCTL, KC_ENT , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC , KC_BSPC, KC_RALT, MO(1)  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                    KC_LSFT, KC_UP  , KC_LCTL,
                                                                                                                    KC_LEFT, KC_DOWN, KC_RGHT
    ),


    [1] = LAYOUT(
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , XXXXXXX, XXXXXXX, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, KC_UP,   KC_ESC,  KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , XXXXXXX, XXXXXXX, KC_Z   , KC_U   , KC_I   , KC_O   , KC_P   , KC_SLSH, KC_BSLS, KC_UP,   XXXXXXX, XXXXXXX,
            XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_LALT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , XXXXXXX, XXXXXXX, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, KC_Y   , KC_X   , KC_C   , KC_V   , KC_B   , KC_LBRC, KC_RBRC, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_MINS, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(1)  , KC_LGUI, KC_LCTL, KC_ENT , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC , KC_BSPC, KC_RALT, MO(1)  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_F1  ,    KC_F2,      KC_F3,               KC_F4  , KC_F5  ,  XXXXXXX,    XXXXXXX,    KC_F6  , KC_F7  ,    KC_F8  ,       KC_F9   ,   KC_F10 ,      KC_PSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, _______, _______, _______, _______,    _______,    _______,             _______, _______,  XXXXXXX,    XXXXXXX,    _______, RALT(KC_Y), KC_UP,         RALT(KC_P), RSFT(KC_GRV), KC_PAST, _______, _______, XXXXXXX, XXXXXXX,
            XXXXXXX, _______, _______, _______, TG(2),   RALT(KC_Q), RALT(KC_S), RALT(RSFT(KC_SCLN)), _______, _______,  XXXXXXX,    XXXXXXX,    KC_HOME, KC_LEFT,    KC_DOWN,       KC_RGHT,    RSFT(KC_2),   KC_PMNS, _______, _______, _______, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,    _______,    _______,             _______, _______,  LSFT(KC_9), LSFT(KC_0), KC_END , _______,    RSFT(KC_SLSH), RSFT(KC_1), KC_EQL,       KC_PPLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(2),      _______,    _______,             _______, XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX, _______,    KC_DEL ,       _______,    _______,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                                           XXXXXXX, KC_UP  , XXXXXXX,
                                                                                                                                           KC_LEFT, KC_DOWN, KC_RGHT
     ),


    [2] = LAYOUT(
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , XXXXXXX, XXXXXXX, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, KC_UP,   KC_ESC,  KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , XXXXXXX, XXXXXXX, KC_Z   , KC_U   , KC_I   , KC_O   , KC_P   , KC_SLSH, KC_BSLS, KC_UP,   XXXXXXX, XXXXXXX,
            XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_LALT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , XXXXXXX, XXXXXXX, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, KC_Y   , KC_X   , KC_C   , KC_V   , KC_B   , KC_LBRC, KC_RBRC, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_MINS, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(1)  , KC_LGUI, KC_LCTL, KC_ENT , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC , KC_BSPC, KC_RALT, MO(1)  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_F1  ,    KC_F2,      KC_F3,               KC_F4  , KC_F5  ,  XXXXXXX,    XXXXXXX,    KC_F6  , KC_F7  ,    KC_F8  ,       KC_F9   ,   KC_F10 ,      KC_PSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, _______, _______, _______, _______,    _______,    _______,             _______, _______,  XXXXXXX,    XXXXXXX,    _______, RALT(KC_Y), KC_UP,         RALT(KC_P), RSFT(KC_GRV), KC_PAST, _______, _______, XXXXXXX, XXXXXXX,
            XXXXXXX, _______, _______, _______, TG(2),   RALT(KC_Q), RALT(KC_S), RALT(RSFT(KC_SCLN)), _______, _______,  XXXXXXX,    XXXXXXX,    KC_HOME, KC_LEFT,    KC_DOWN,       KC_RGHT,    RSFT(KC_2),   KC_PMNS, _______, _______, _______, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,    _______,    _______,             _______, _______,  LSFT(KC_9), LSFT(KC_0), KC_END , _______,    RSFT(KC_SLSH), RSFT(KC_1), KC_EQL,       KC_PPLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(2),      _______,    _______,             _______, XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX, _______,    KC_DEL ,       _______,    _______,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                                           XXXXXXX, KC_UP  , XXXXXXX,
                                                                                                                                           KC_LEFT, KC_DOWN, KC_RGHT
     ),


    [3] = LAYOUT(
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , XXXXXXX, XXXXXXX, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, KC_UP,   KC_ESC,  KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , XXXXXXX, XXXXXXX, KC_Z   , KC_U   , KC_I   , KC_O   , KC_P   , KC_SLSH, KC_BSLS, KC_UP,   XXXXXXX, XXXXXXX,
            XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_LALT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , XXXXXXX, XXXXXXX, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, KC_Y   , KC_X   , KC_C   , KC_V   , KC_B   , KC_LBRC, KC_RBRC, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_MINS, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(1)  , KC_LGUI, KC_LCTL, KC_ENT , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC , KC_BSPC, KC_RALT, MO(1)  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_F1  ,    KC_F2,      KC_F3,               KC_F4  , KC_F5  ,  XXXXXXX,    XXXXXXX,    KC_F6  , KC_F7  ,    KC_F8  ,       KC_F9   ,   KC_F10 ,      KC_PSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, _______, _______, _______, _______,    _______,    _______,             _______, _______,  XXXXXXX,    XXXXXXX,    _______, RALT(KC_Y), KC_UP,         RALT(KC_P), RSFT(KC_GRV), KC_PAST, _______, _______, XXXXXXX, XXXXXXX,
            XXXXXXX, _______, _______, _______, TG(2),   RALT(KC_Q), RALT(KC_S), RALT(RSFT(KC_SCLN)), _______, _______,  XXXXXXX,    XXXXXXX,    KC_HOME, KC_LEFT,    KC_DOWN,       KC_RGHT,    RSFT(KC_2),   KC_PMNS, _______, _______, _______, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,    _______,    _______,             _______, _______,  LSFT(KC_9), LSFT(KC_0), KC_END , _______,    RSFT(KC_SLSH), RSFT(KC_1), KC_EQL,       KC_PPLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(2),      _______,    _______,             _______, XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX, _______,    KC_DEL ,       _______,    _______,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                                           XXXXXXX, KC_UP  , XXXXXXX,
                                                                                                                                           KC_LEFT, KC_DOWN, KC_RGHT
     )

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] = { ENCODER_CCW_CW(UG_HUED, UG_HUEU),  ENCODER_CCW_CW(UG_SATD, UG_SATU)  },
    [2] = { ENCODER_CCW_CW(UG_VALD, UG_VALU),  ENCODER_CCW_CW(UG_SPDD, UG_SPDU)  },
    [3] = { ENCODER_CCW_CW(UG_PREV, UG_NEXT),  ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif