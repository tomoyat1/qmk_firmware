#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _VIM 3
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  VIM,
  VIM_NRM,
  GO_ERR,
};

#define EISU LALT(KC_GRV)
#define TERM LGUI(KC_ENT)
#define TERMN LGUI(LSFT(KC_ENT))
#define GUIENT GUI_T(KC_ENT)
#define CTLESC CTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  `   |   Q  |   W  |   E  |   R  |   T  |   -  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  | Term |                    |  Tab |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |Delete|                    |CTLESC|   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | Lower|||||||| Lower| Space| Bksp |||||||| Bksp |GUIENT| Raise|||||||| Home |PageDn|PageUp| End  |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,                              KC_EQL , KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    TERM   ,                              KC_TAB , KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_DEL ,                              CTLESC , KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_TAB , \
    VIM    , KC_LGUI, KC_LALT, EISU,             LOWER,   KC_SPC , KC_BSPC,              GUIENT,KC_LSFT, RAISE,            KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |   =  |  F1  |  F2  |  F3  |  F4  |  F5  |   _  |                    |   +  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Ctrl |   1  |   2  |   3  |   4  |   5  | TermN|                    | TRNS |   6  |   7  |   8  |    9 |   0  |  F12 |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   6  |   7  |   8  |   9  |   0  | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_EQL , KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_UNDS,                        KC_PLUS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
    KC_LCTL, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    TERMN,                          KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12 , \
    KC_LSFT, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,                        KC_TRNS, KC_N,    KC_M,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_LCTL, KC_LGUI, KC_LALT, EISU,             LOWER,   KC_TRNS, KC_TRNS,       KC_TRNS,KC_TRNS, RAISE,            KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
  ),

  /* Raise
  * ,----------------------------------------------------------------------------------------------------------------------.
  * |   `  |   !  |   @  |   {  |   }  |   =  | Trns |                    | Trns |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
  * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
  * |   ~  |   #  |   $  |   (  |   )  |   -  | Trns |                    | Trns | Left | Down |  Up  | Right|   :  |  F12 |
  * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
  * | Shift|   %  |   ^  |   8  |   ]  |   ~  | Trns |                    | Trns |   N  |   M  |   <  |   >  |   ?  | Shift|
  * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
  * | Ctrl |  F11 |  F12 | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
  * ,----------------------------------------------------------------------------------------------------------------------.
  */
  [_RAISE] = LAYOUT(
    KC_TRNS, KC_EXLM, KC_AT  , KC_LCBR, KC_RCBR, KC_EQUAL,KC_UNDS,                        KC_PLUS, KC_BSLS, KC_7   , KC_8   , KC_9   , KC_F10 , KC_F11 ,  \
    KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_MINUS,KC_TRNS,                        KC_TRNS, GO_ERR , KC_4   , KC_5   , KC_6   , KC_COLN, KC_F12 , \
    KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,                        KC_TRNS, KC_AMPR, KC_1   , KC_2   , KC_3   , KC_QUES, KC_TRNS, \
    KC_TRNS, KC_AMPR, KC_ASTR, KC_TRNS,          LOWER,   KC_TRNS, KC_TRNS,       KC_TRNS,KC_RSFT, RAISE,            KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
    ),

  /* Vim
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, VIM_NRM,_______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______  \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case VIM:
      if (record->event.pressed) {
        layer_on(_VIM);
      } else {
        layer_off(_VIM);
      }
    case VIM_NRM:
      layer_off(_VIM);
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
