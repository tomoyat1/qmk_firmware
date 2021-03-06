#include QMK_KEYBOARD_H

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  VIM_INS,
  GO_ERR,
};

enum tap_dance_keycodes {
  TD_ESC
};

#define TERM LGUI(KC_ENT)
#define TERMN LGUI(LSFT(KC_ENT))
#define GUIENT GUI_T(KC_ENT)
#define CTLESC CTL_T(KC_ESC)
#define CUT LCTL(KC_X)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define UNDO LCTL(KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi( // default layer
        KC_GESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_LCTL,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_CLCK,        KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   MO(2),   KC_RCTL
    ),
    [1] = LAYOUT_60_ansi( // symbols layer
        TG(3),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_TRNS, KC_EXLM, KC_AT  , KC_LCBR, KC_RCBR, KC_EQL,  KC_BSLS, KC_7   , KC_8   , KC_9   , KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,
        KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_MINS, GO_ERR,  KC_4   , KC_5   , KC_6   , KC_COLN, _______,          _______,
        KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_GRV,  KC_AMPR, KC_1   , KC_2   , KC_3   , KC_QUES,           _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),
    [2] = LAYOUT_60_ansi( // backlight/media layer
        _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, RGB_TOG, _______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SPI, RGB_SPD, XXXXXXX, XXXXXXX,          _______,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, KC_SLEP
    ),
    [3] = LAYOUT_60_ansi( // vim layer
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, _______, _______, _______, _______, COPY,    UNDO,    VIM_INS, XXXXXXX, PASTE,   XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,          _______,
        _______,          _______, CUT,     _______, _______, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,          XXXXXXX,
        _______, _______, _______,                            _______,                            XXXXXXX, XXXXXXX, XXXXXXX, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case VIM_INS:
      layer_off(3);
      return false;
      break;
    case GO_ERR:
      if (record->event.pressed) {
        SEND_STRING("if err != nil {");
        SEND_STRING(SS_TAP(X_ENTER));
      }
      return false;
      break;
  }
  return true;
}

void td_esc(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING (SS_TAP(X_GRV));
  } else if (state->count == 2) {
    SEND_STRING (SS_TAP(X_ESC));
  } else {
    unsigned int i;
    for (i = state->count; i > 0; i--) {
      SEND_STRING ("`");
    }
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC] = ACTION_TAP_DANCE_FN (td_esc)
};
