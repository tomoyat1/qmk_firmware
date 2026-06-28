#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "version.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE = 0,
  _SYMBOLS,
  _MOUSE,
  _VIM_NORMAL,
  _VIM_SHIFTED_NORMAL,
  _VIM_VISUAL_LINE,
};

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  VRSN,
  CLEAR,
  QUIT_VIM,
  GO_ERR,
  VIM_A,
  VIM_O,
  VIM_SHIFT_A,
  VIM_SHIFT_I,
  VIM_SHIFT_O,
  VIM_U,
  VIM_X,
  VIM_V,
  VIM_SHIFT_V,
  VIM_VS_DW,
  VIM_VS_UP,
  VIM_ESC_VIS,
  VIM_Y,
  VIM_P,
  VIM_SHIFT_P,
  VIM_VISUAL_LINE,
};

int is_visual_mode = false;
int is_visual_line_mode = false;
int is_clipboard_visual_line = false;

enum tap_dance_keycodes {
  VIM_DD,
  VIM_YY
};

enum {
  VIM_DD_ACTION = 0,
  VIM_YY_ACTION,
  MULTILAYER
};

void dance_vim_dd_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    register_code (KC_HOME);
    unregister_code (KC_HOME);
    register_code (KC_LSFT);
    register_code (KC_END);
    unregister_code (KC_END);
    unregister_code (KC_LSFT);
    SEND_STRING (SS_LCTL("x"));
  }
}

void dance_vim_dd_reset (tap_dance_state_t *state, void *user_data) {
  return;
}

void dance_vim_yy_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    register_code (KC_HOME);
    unregister_code (KC_HOME);
    register_code (KC_LSFT);
    register_code (KC_END);
    unregister_code (KC_END);
    unregister_code (KC_LSFT);
    SEND_STRING (SS_LCTL("c"));
  }
}

void dance_vim_yy_reset (tap_dance_state_t *state, void *user_data) {
  return;
}

void dance_multilayer_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_on(1);
    layer_off(0);
  } else if (state->count == 2) {
    layer_on(3);
    layer_off(0);
  }
}

void dance_multilayer_reset (tap_dance_state_t *state, void *user_data) {
  return;
}

tap_dance_action_t tap_dance_actions[] = {
  [VIM_DD_ACTION] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_vim_dd_finished, dance_vim_dd_reset),
  [VIM_YY_ACTION] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_vim_yy_finished, dance_vim_yy_reset),
  [MULTILAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_multilayer_finished, dance_multilayer_reset),
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#define GUI_ENT GUI_T(KC_ENT)
#define CTL_ESC CTL_T(KC_ESC)
#define MEH_SPC MEH(KC_SPC)
#define TTERM LGUI(KC_ENT)
#define TERM  LGUI(LSFT(KC_ENT))
#define TD_LYR TD(MULTILAYER)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   =  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  -   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   `  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | RAlt |CTL_ES|   N  |   M  |   ,  |   .  |   /  | Tab  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | TG(4)| LGUI | LAlt |MEH_SP|MO(2) |Space |Bksp  |GUI_EN|Shift |MO(1) | Home | Pgdn | Pgup | End  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_BASE] = LAYOUT_5row( \
      KC_EQUAL,KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS, \
      KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_RALT, CTL_ESC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_TAB, \
      TD_LYR,  KC_LGUI, KC_LALT, MEH_SPC, MO(2),   KC_SPC,  KC_BSPC, GUI_ENT, KC_RSFT, MO(1),   KC_HOME, KC_PGDN, KC_PGUP, KC_END \
      ),

  /* Symbols
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   F1 |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   !  |   @  |   {  |   }  |   =  |             |   \  |   7  |   8  |   9  |   *  |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   #  |   $  |   (  |   )  |   -  |             |GO_ERR|   4  |   5  |   6  |   +  |______|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   %  |   ^  |   [  |   ]  |   ~  | TERM |TTERM | Tab  |   1  |   2  |   3  |   \  |______|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | TO(1)|   &  |   *  |______|______|______|______|______|______|______|   0  |   .  |   =  |______|
   * `-------------------------------------------------------------------------------------------------'
   */
  [_SYMBOLS] = LAYOUT_5row( \
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
      KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_EQUAL,                  KC_BSLS, KC_9,    KC_8,    KC_9,    KC_ASTR, KC_F12, \
      KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_MINUS,                  GO_ERR,  KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS, \
      KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_GRV,  TERM,    TTERM,   KC_TAB,  KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS, \
      TO(0),   KC_AMPR, KC_ASTR, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,  KC_TRNS, KC_TRNS, KC_TRNS, KC_0,    KC_DOT,  KC_EQUAL,KC_TRNS \
      ),

  /* Numbers and Function
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   7  |   8  |   9  |   0  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  | MS_L | MS_DN| MS_R |   I  |             |   D  | WH_L | WH_DN| WH_R |   S  |  /   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  |   [  |   ]  |   B  |   M  |   W  |   V  |   Z  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Adjust| Esc  | Alt  | GUI  | EISU |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_MOUSE] = LAYOUT_5row( \
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
      KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12, \
      KC_TRNS, KC_TRNS, MS_LEFT, MS_DOWN, MS_RGHT, KC_TRNS,                   KC_TRNS, MS_WHLL, MS_WHLD, MS_WHLR, KC_S,    KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, MS_BTN3, KC_TRNS, KC_M,    KC_W,    KC_V,    KC_Z,    KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC,  MS_BTN2, MS_BTN1, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS \
      ),

#define TD_DD TD(VIM_DD_ACTION)
#define TD_YY TD(VIM_YY_ACTION)
#define QUIT_V QUIT_VIM
#define VEV VIM_ESC_VIS
  /* Universal vim controls
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  NO  |______|______|______|______|______|             |______|______|______|______|______|______|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |______|______|______|______|______|______|             |VIM_YY|VIM_U |QUIT_V|VIM_O |VIM_P |______|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |______|VIM_A |______|VIM_DD|______|______|             |LEFT  |DOWN  | UP   |RIGHT |______|______|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |______|______|VIM_X |______|VIM_V |______|______|______|______|______|______|______|______|______|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |QUIT_V|______|______|______|______|______|______|______|______|______|______|______|______|______|
   * `-------------------------------------------------------------------------------------------------'
   */
  [_VIM_NORMAL] = LAYOUT_5row( \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, QK_BOOT, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   TD_YY,   VIM_U,   QUIT_V,  VIM_O,   VIM_P,   KC_TRNS, \
      KC_TRNS, VIM_A,   KC_TRNS, TD_DD,   KC_TRNS, KC_TRNS,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, VIM_X,   KC_TRNS, VIM_V,   KC_TRNS, KC_TRNS, VEV,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      QUIT_V,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(4),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS \
      ),

#define VSA VIM_SHIFT_A
#define VSI VIM_SHIFT_I
#define VSO VIM_SHIFT_O
#define VSV VIM_SHIFT_V
  /* Universal vim controls (shifted)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  NO  |______|______|______|______|______|             |______|______|______|______|______|______|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |______|______|______|______|______|______|             |VIM_YY|VIM_U |QUIT_V|VIM_O |VIM_P |______|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |______|VIM_A |______|VIM_DD|______|______|             |LEFT  |DOWN  | UP   |RIGHT |______|______|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |______|______|VIM_X |______| VSV  |______|______|______|______|______|______|______|______|______|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |QUIT_V|______|______|______|______|______|______|______|______|______|______|______|______|______|
   * `-------------------------------------------------------------------------------------------------'
   */
  [_VIM_SHIFTED_NORMAL] = LAYOUT_5row( \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, QK_BOOT, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   TD_YY,   VIM_U,   VSI,     VSO,     VIM_P,   KC_TRNS, \
      KC_TRNS, VSA,     KC_TRNS, TD_DD,   KC_TRNS, KC_TRNS,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, VSV,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      QUIT_V,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS \
      ),

#define VVS_DW VIM_VS_DW
#define VVS_UP VIM_VS_UP
  /* Universal vim controls (shifted)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  NO  |______|______|______|______|______|             |______|______|______|______|______|______|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |______|______|______|______|______|______|             |VIM_YY|VIM_U |QUIT_V|VIM_O |VIM_P |______|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |______|  NO  |______|______|______|______|             |LEFT  |DOWN  | UP   |RIGHT |______|______|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |______|______|______|______|______|______|______|______|______|______|______|______|______|______|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |______|______|______|______|______|______|______|______|______|______|______|______|______|______|
   * `-------------------------------------------------------------------------------------------------'
   */
  [_VIM_VISUAL_LINE] = LAYOUT_5row( \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, QK_BOOT, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   TD_YY,   VIM_U,   VSI,     VSO,     KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_NO,   VVS_DW,  VVS_UP,  KC_NO,   KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS \
      )
};


// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case CLEAR:
      if (record->event.pressed) {
        SEND_STRING (SS_LCTL("l"));
      }
      return false;
      break;
    case QUIT_VIM:
      if (record->event.pressed) {
        SEND_STRING (SS_UP(X_LSFT));
        layer_off(3);
      }
      return false;
      break;
    case VIM_A:
      if (record->event.pressed) {
        SEND_STRING (SS_TAP(X_RIGHT));
        SEND_STRING (SS_UP(X_LSFT));
        layer_off(3);
      }
      return false;
      break;
    case VIM_SHIFT_A:
      if (record->event.pressed) {
        SEND_STRING (SS_TAP(X_END));
        SEND_STRING (SS_UP(X_LSFT));
        layer_off(4);
        layer_off(3);
      }
      return false;
      break;
    case VIM_O:
      if (record->event.pressed) {
        SEND_STRING (SS_TAP(X_END)SS_TAP(X_ENTER));
        SEND_STRING (SS_UP(X_LSFT));
        layer_off(3);
      }
      return false;
      break;
    case VIM_SHIFT_O:
      if (record->event.pressed) {
        SEND_STRING (SS_TAP(X_HOME)SS_TAP(X_ENTER));
        layer_off(4);
        SEND_STRING (SS_UP(X_LSFT));
        layer_off(3);
        SEND_STRING (SS_TAP(X_UP));
      }
      return false;
      break;
    case VIM_SHIFT_I:
      if (record->event.pressed) {
        SEND_STRING (SS_TAP(X_HOME));
        layer_off(4);
        SEND_STRING (SS_UP(X_LSFT));
        layer_off(3);
        layer_off(5);
      }
      return false;
      break;
    case VIM_P:
      if (record->event.pressed) {
        if (is_clipboard_visual_line) {
          SEND_STRING (SS_TAP(X_END)SS_TAP(X_ENTER));
          SEND_STRING (SS_LCTL("v"));
        } else {
          SEND_STRING (SS_TAP(X_RIGHT));
          SEND_STRING (SS_LCTL("v"));
        }
      }
      return false;
      break;
    case VIM_SHIFT_P:
      if (record->event.pressed) {
        if (is_clipboard_visual_line) {
          SEND_STRING (SS_TAP(X_HOME)SS_TAP(X_ENTER));
          SEND_STRING (SS_LCTL("v"));
        } else {
          SEND_STRING (SS_LCTL("v"));
        }
      }
      return false;
      break;
    case VIM_U:
      if (record->event.pressed) {
        SEND_STRING (SS_LCTL("z"));
      }
      return false;
      break;
    case VIM_V:
      if (record->event.pressed) {
        is_visual_mode = true;
        SEND_STRING (SS_DOWN(X_LSFT));
        SEND_STRING (SS_TAP(X_RIGHT));
      }
      return false;
      break;
    case VIM_SHIFT_V:
      if (record->event.pressed) {
        is_visual_mode = true;
        is_visual_line_mode = true;
        layer_on(5);
        layer_on(3);
        layer_off(4);
        SEND_STRING (SS_TAP(X_HOME));
        SEND_STRING (SS_DOWN(X_LSFT));
        SEND_STRING (SS_TAP(X_END));
      }
      return false;
      break;
    case VIM_ESC_VIS:
      if (record->event.pressed) {
        if (is_visual_mode) {
          is_visual_mode = false;
          is_visual_line_mode = false;
          SEND_STRING (SS_UP(X_LSFT));
          SEND_STRING (SS_TAP(X_LEFT)SS_TAP(X_LEFT));
          layer_off(5);
          /*
           * Unselects current text selection
           * Conflicts with application-side vim-like key bindings
           */
          SEND_STRING (SS_TAP(X_ESCAPE));
        } else {
          /* Unselects current text selection */
          SEND_STRING (SS_TAP(X_ESCAPE));
        }
      }
      return false;
      break;
    case VIM_VS_DW:
      if (record->event.pressed) {
        SEND_STRING (SS_TAP(X_DOWN)SS_TAP(X_HOME)SS_TAP(X_END));
      }
      return false;
      break;
    case VIM_VS_UP:
      if (record->event.pressed) {
        SEND_STRING (SS_TAP(X_UP)SS_TAP(X_HOME)SS_TAP(X_END));
      }
      return false;
      break;
    case VIM_X:
      if (record->event.pressed) {
        if (is_visual_mode) {
          SEND_STRING (SS_UP(X_LSFT)); //for visual mode
          SEND_STRING (SS_LCTL("x"));
          is_visual_mode = false;
          if (is_visual_line_mode) {
            is_clipboard_visual_line = true;
          } else {
            is_clipboard_visual_line = false;
          }
        } else {
          SEND_STRING (SS_DOWN(X_LSFT));
          SEND_STRING (SS_TAP(X_RIGHT));
          SEND_STRING (SS_UP(X_LSFT));
          SEND_STRING (SS_LCTL("x"));
          is_clipboard_visual_line = false;
        }
      }
      return false;
      break;
    case VIM_Y:
      if (record->event.pressed) {
        if (is_visual_mode) {
          SEND_STRING (SS_UP(X_LSFT)); // for visual mode
          SEND_STRING (SS_LCTL("c"));
          SEND_STRING (SS_TAP(X_LEFT));
          is_visual_mode = false;
          if (is_visual_line_mode) {
            is_clipboard_visual_line = true;
          } else {
            is_clipboard_visual_line = false;
          }
        }
        is_clipboard_visual_line = false;
      }
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

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


#ifdef OLED_ENABLE

// assign the right code to your layers for OLED display
#define L_BASE (1<<_BASE)
#define L_SYMBOLS (1<<_SYMBOLS)
#define L_MOUSE (1<<_MOUSE)
#define L_VIM_NORMAL (1<<_VIM_NORMAL)
#define L_VIM_SHIFTED_NORMAL (1<<_VIM_SHIFTED_NORMAL)
#define L_VIM_VISUAL_LINE (1<<_VIM_VISUAL_LINE)

static void render_status(void) {
  oled_write_P(PSTR("Layer: "), false);
  switch (layer_state) {
    case 0:
      /* fall-through */
    case L_BASE:
      oled_write_ln_P(PSTR("Default"), false);
      break;
    case L_SYMBOLS:
      oled_write_ln_P(PSTR("Symbols"), false);
      break;
    case L_MOUSE:
      oled_write_ln_P(PSTR("Mouse"), false);
      break;
    case L_VIM_NORMAL:
      oled_write_ln_P(PSTR("Vim normal"), false);
      break;
    case L_VIM_SHIFTED_NORMAL | L_VIM_NORMAL:
      oled_write_ln_P(PSTR("Vim normal (shifted)"), false);
      break;
    case L_VIM_VISUAL_LINE | L_VIM_NORMAL:
      oled_write_ln_P(PSTR("Vim visual line"), false);
      break;
    default: {
      char buf[24];
      snprintf(buf, sizeof(buf), "Undef-%u", (unsigned)layer_state);
      oled_write_ln(buf, false);
      break;
    }
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.num_lock    ? PSTR("NUMLOCK ") : PSTR("        "), false);
  oled_write_P(led_state.caps_lock   ? PSTR("CAPS ")    : PSTR("     "),    false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCLK")     : PSTR("    "),     false);
}

bool oled_task_user(void) {
  if (!is_keyboard_master()) {
    // let the keyboard-level oled_task_kb() render the logo on the slave half
    return true;
  }
  render_status();
  // suppress the keyboard's default master rendering
  return false;
}

#endif
/* vim:set ts=2 sts=2 sw=2 expandtab: */
