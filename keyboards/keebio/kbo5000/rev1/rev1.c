#include "kbo5000.h"
#include "split_util.h"

enum encoder_names {
  LEFT_HALF_ENC = 0,
  RIGHT_HALF_ENC1 = 2,
  RIGHT_HALF_ENC2,
};

void matrix_init_kb(void) {
    setPinOutput(CAPS_LOCK_LED_PIN);
    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    // Only update if left half
    if (isLeftHand && led_update_user(led_state)) {
        writePin(CAPS_LOCK_LED_PIN, !led_state.caps_lock);
    }
    return true;
}

void eeconfig_init_kb(void) {
#ifdef BACKLIGHT_ENABLE
    backlight_enable();
    backlight_level(3);
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_enable(); // Enable RGB by default
    rgblight_sethsv(0, 255, 255);  // Set default HSV - red hue, full saturation, full brightness
#ifdef RGBLIGHT_ANIMATIONS
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2); // set to RGB_RAINBOW_SWIRL by default
#endif
#endif

    eeconfig_update_kb(0);
    eeconfig_init_user();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == LEFT_HALF_ENC) {
      if (IS_LAYER_ON(0)) {
        if (clockwise) {
            tap_code(KC_WWW_FORWARD);
        } else {
            tap_code(KC_WWW_BACK);
        }
      } else if (IS_LAYER_ON(1)) {
        if (clockwise) {
          tap_code16(RGB_MODE_FORWARD);
        } else {
          tap_code16(RGB_MODE_REVERSE);
        }
      }
        
    } else if (index == RIGHT_HALF_ENC1) {
      if (IS_LAYER_ON(0)) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
      } else if (IS_LAYER_ON(1)) {
        if (clockwise) {
            tap_code16(RGB_HUI);
        } else {
            tap_code16(RGB_HUD);
        }
      }
        
    } else if (index == RIGHT_HALF_ENC2) {
      if (IS_LAYER_ON(0)) {
        if (clockwise) {
            tap_code(KC_MEDIA_NEXT_TRACK);
        } else {
            tap_code(KC_MEDIA_PREV_TRACK);
        }
      } else if (IS_LAYER_ON(1)) {
        if (clockwise) {
            tap_code16(RGB_VAI);
        } else {
            tap_code16(RGB_VAD);
        }
      }
        
    }
    return true;
}
