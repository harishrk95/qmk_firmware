#include "org60.h"
#include "action_layer.h"

// Keyboard Layers
enum keyboard_layers {
  _BASE,        // Base Layer
  _FUNCTION,    // Function Layer
  _LIGHTING,    // Lighting Layer
  _ADVFUNC,     // Advanced Function Layer
  _BLANK,       // Blank Layer (copy me to make new layers)
};


// Custom key codes
enum custom_keys{
  // Three Finger Salute - Sends Ctl-Alt-Del 
  TFS = LCTL(LALT(KC_DEL)),
};


// Tap Dance Declarations
enum tap_dance_actions{
  TD_LAYER = 0,
  TD_SHRUG = 1,
};


// Layer switching functions
// 
// Tap and hold for function layer
// Tap twice to toggle lighting layer
// Tap three times to toggle advanced functions layer
void layers_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed)
  {
    layer_on(_FUNCTION);
  }
  else
  {
    switch (state->count)
    {
    case 1: // base layer on
      if (!state->pressed)
      {
        layer_off(_FUNCTION);
        layer_off(_LIGHTING);
        layer_off(_ADVFUNC);
      }
      break;
    case 2: // lighting layer on
      layer_off(_FUNCTION);
      layer_on(_LIGHTING);
      layer_off(_ADVFUNC);
      break;
    case 3: // advanced layer on
      layer_off(_LIGHTING);
      layer_off(_FUNCTION);
      layer_on(_ADVFUNC);
      break;
    }
  }
}
void layers_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
  uint8_t layer = biton32(layer_state);

  switch(state->count) {
    default:
      switch(layer) {
        case _FUNCTION:
          layer_off(_FUNCTION);
          break;
        default:
          break;
      }
      break;
  }
}


// Shrug functions
//
// Acts as Shift, otherwise tap 3-5 times for "::shrug::" ¯\_(ツ)_/¯
void shrug_dance_each(qk_tap_dance_state_t *state, void *user_data) {
  register_code (KC_LSFT);
}
void shrug_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 3:
    case 4:
    case 5:
      SEND_STRING("::shrug::");
      // process_unicode((0x30C4|QK_UNICODE), record);   // Face
      break;
    default:
      break;
  }
}
void shrug_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  unregister_code (KC_LSFT);
}


// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, layers_dance_finished, layers_dance_reset),
  [TD_SHRUG] = ACTION_TAP_DANCE_FN_ADVANCED (shrug_dance_each, shrug_dance_finished, shrug_dance_reset),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = KEYMAP(
  /*
    0: Base Layer
    .--------------------------------------------------------------------------------------------------------------------------------------.
    | ~      | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      | _      | +      |                 |
    |        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
    | Esc    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | Backspace       |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |            |        |        |        |        |        |        |        |        |        |        | {      | ]      | |           |
    |            |        |        |        |        |        |        |        |        |        |        |        |        |             |
    | Tab        | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \           |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |               |        |        |        |        |        |        |        |        |        | :      | "      |                   |
    |               |        |        |        |        |        |        |        |        |        |        |        |                   |
    | PrntScr       | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | Enter             |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |                   |        |        |        |        |        |        |        | <      | >      | ?      |░░░░░░|        |░░░░░░░░|
    |                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
    | Shift (TD_SHRUG)  | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      |░░░░░░| Up     |░░░░░░░░|
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |          |          |          |                                                        |          |░░░░░░|        |        |        |
    |          |          |          |                                                        |          |░░░░░░|        |        |        |
    | Ctrl     | Win      | Alt      | Space                                                  | Func     |░░░░░░| Left   | Down   | Right  |
    '--------------------------------------------------------------------------------------------------------------------------------------'
  */

   //--------------------------------------------------------------------------------------------------------------------------------------.
   //        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
   //        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
     KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_NO,   
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //            |        |        |        |        |        |        |        |        |        |        |        |        |             |
   //            |        |        |        |        |        |        |        |        |        |        |        |        |             |
     KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,      
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //               |        |        |        |        |        |        |        |        |        |        |        |                   |
   //               |        |        |        |        |        |        |        |        |        |        |        |                   |
     KC_PSCR,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NO, KC_ENT,      
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
   //                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
     TD(TD_SHRUG), KC_NO,KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO, KC_UP,   KC_NO,   
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //          |          |          |                                                        |          |░░░░░░|        |        |        |
   //          |          |          |                                                        |          |░░░░░░|        |        |        |
     KC_LCTL,   KC_LGUI,   KC_LALT,   KC_SPC,                                                  TD(TD_LAYER),KC_NO,KC_LEFT,KC_DOWN, KC_RIGHT),
   //--------------------------------------------------------------------------------------------------------------------------------------'


  [_FUNCTION] = KEYMAP(
  /*
    1: Function Layer
    .--------------------------------------------------------------------------------------------------------------------------------------.
    | ~      |        |        |        |        |        |        |        |        |        |        |        |        |                 |
    |        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
    | `      | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | Delete          |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |            |        |        |        |        |        |        |        |        |        |        |        |        |             |
    |            |        |        |        |        |        |        |        |        |        | Page   |        |        |             |
    |            | 7      | 8      | 9      |        |        |        |        | Insert | Calc   | Up     | Home   | End    | TFS         |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |               |        |        |        |        |        |        |        |        |        |        |        |                   |
    |               |        |        |        |        |        |        |        |        |        | Page   |        |                   |
    | Caps Lock     | 4      | 5      | 6      |        |        |        |        |        |        | Down   | Pause  | Enter             |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
    |                   |        |        |        |        |        |        |        | Prev   | Next   |        |░░░░░░| Vol    |░░░░░░░░|
    | Shift             | 1      | 2      | 3      |        |        |        |        | Track  | Track  |        |░░░░░░| Up     |░░░░░░░░|
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |          |          |          |                                                        |          |░░░░░░|        |        |        |
    |          |          |          |                                                        |          |░░░░░░|        | Vol    |        |
    | Ctrl     | Win      | Alt      | 0                                                      | Func     |░░░░░░| Mute   | Down   | Right  |
    '--------------------------------------------------------------------------------------------------------------------------------------'
  */

   //--------------------------------------------------------------------------------------------------------------------------------------.
   //        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
   //        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
     KC_GRAVE,KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_NO,   
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //            |        |        |        |        |        |        |        |        |        |        |        |        |             |
   //            |        |        |        |        |        |        |        |        |        |        |        |        |             |
     KC_NO,       KC_P7,   KC_P8,   KC_P9,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_INS,  KC_CALC, KC_PGUP, KC_HOME, KC_END,  TFS,          
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //               |        |        |        |        |        |        |        |        |        |        |        |                   |
   //               |        |        |        |        |        |        |        |        |        |        |        |                   |
     KC_CAPS,        KC_P4,   KC_P5,   KC_P6,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PGDN, KC_PAUS, KC_NO, KC_ENT,      
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
   //                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
     KC_LSFT, KC_NO,     KC_P1,   KC_P2,   KC_P3,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MPRV, KC_MNXT, KC_NO,   KC_NO, KC_VOLU, KC_NO,   
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //          |          |          |                                                        |          |░░░░░░|        |        |        |
   //          |          |          |                                                        |          |░░░░░░|        |        |        |
     KC_LCTL,   KC_LGUI,   KC_LALT,   KC_P0,                                                   TD(TD_LAYER),KC_NO,KC_MUTE,KC_VOLD, KC_MPLY),
   //--------------------------------------------------------------------------------------------------------------------------------------'


  [_LIGHTING] = KEYMAP(
  /*
    2: Lighting Layer
    .--------------------------------------------------------------------------------------------------------------------------------------.
    |        |        |        |        |        |        |        |        |        |        | Back   |        |        |                 |
    |        |        |        |        |        |        |        |        |        |        | Light  | Back   | Back   |                 |
    |        |        |        |        |        |        |        |        |        |        | 0      | Light- | Light+ |                 |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |            |        |        |        |        |        |        |        |        |        |        |        |        |             |
    |            |        |        |        | RGB    | RGB    | RGB    | RGB    |        |        |        |        |        |             |
    |            |        |        |        | Toggle | Mode   | Pwr+   | Pwr-   |        |        |        |        |        |             |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |               |        |        |        |        |        |        |        |        |        |        |        |                   |
    |               |        |        |        | RGB    | RGB    | RGB    | RGB    |        |        |        |        |                   |
    |               |        |        |        | Hue+   | Hue-   | Sat+   | Sat-   |        |        |        |        |                   |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
    |                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
    |                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |          |          |          |                                                        |          |░░░░░░|        |        |        |
    |          |          |          |                                                        |          |░░░░░░|        |        |        |
    |          |          |          |                                                        | Func     |░░░░░░|        |        |        |
    '--------------------------------------------------------------------------------------------------------------------------------------'
  */

   //--------------------------------------------------------------------------------------------------------------------------------------.
   //        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
   //        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   BL_0,    BL_DEC,  BL_INC,  KC_NO, KC_NO,     
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //            |        |        |        |        |        |        |        |        |        |        |        |        |             |
   //            |        |        |        |        |        |        |        |        |        |        |        |        |             |
     KC_NO,       KC_NO,   KC_NO,   KC_NO,   RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,          
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //               |        |        |        |        |        |        |        |        |        |        |        |                   |
   //               |        |        |        |        |        |        |        |        |        |        |        |                   |
     KC_NO,          KC_NO,   KC_NO,   KC_NO,   RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,       
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
   //                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
     KC_NO, KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //          |          |          |                                                        |          |░░░░░░|        |        |        |
   //          |          |          |                                                        |          |░░░░░░|        |        |        |
     KC_NO,     KC_NO,     KC_NO,     KC_NO,                                                   TD(TD_LAYER),KC_NO,KC_NO,  KC_NO,   KC_NO),
   //--------------------------------------------------------------------------------------------------------------------------------------'


  [_ADVFUNC] = KEYMAP(
  /*
    3: Advanced functions Layer
    .--------------------------------------------------------------------------------------------------------------------------------------.
    |        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
    |        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
    | Sleep  |        |        |        |        |        |        |        |        |        |        |        |        |                 |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |            |        |        |        |        |        |        |        |        |        |        |        |        |             |
    |            |        |        |        |        |        |        |        |        |        |        |        |        |             |
    | Reset      |        |        |        |        |        |        |        |        |        |        |        |        |             |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |               |        |        |        |        |        |        |        |        |        |        |        |                   |
    |               |        |        |        |        |        |        |        |        |        |        |        |                   |
    |               |        |        |        |        |        |        |        |        |        |        |        |                   |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
    |                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
    |                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |          |          |          |                                                        |          |░░░░░░|        |        |        |
    |          |          |          |                                                        |          |░░░░░░|        |        |        |
    |          |          |          |                                                        | Func     |░░░░░░|        |        |        |
    '--------------------------------------------------------------------------------------------------------------------------------------'
  */

   //--------------------------------------------------------------------------------------------------------------------------------------.
   //        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
   //        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
     KC_SLEP, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,     
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //            |        |        |        |        |        |        |        |        |        |        |        |        |             |
   //            |        |        |        |        |        |        |        |        |        |        |        |        |             |
     RESET,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //               |        |        |        |        |        |        |        |        |        |        |        |                   |
   //               |        |        |        |        |        |        |        |        |        |        |        |                   |
     KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,       
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
   //                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
     KC_NO, KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //          |          |          |                                                        |          |░░░░░░|        |        |        |
   //          |          |          |                                                        |          |░░░░░░|        |        |        |
     KC_NO,     KC_NO,     KC_NO,     KC_NO,                                                   TD(TD_LAYER),KC_NO,KC_NO,  KC_NO,   KC_NO),
   //--------------------------------------------------------------------------------------------------------------------------------------'


  [_BLANK] = KEYMAP(
  /*
    X: Blank Layer (copy me to make new layers)
    .--------------------------------------------------------------------------------------------------------------------------------------.
    |        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
    |        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
    |        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |            |        |        |        |        |        |        |        |        |        |        |        |        |             |
    |            |        |        |        |        |        |        |        |        |        |        |        |        |             |
    |            |        |        |        |        |        |        |        |        |        |        |        |        |             |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |               |        |        |        |        |        |        |        |        |        |        |        |                   |
    |               |        |        |        |        |        |        |        |        |        |        |        |                   |
    |               |        |        |        |        |        |        |        |        |        |        |        |                   |
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
    |                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
    |                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
    |--------------------------------------------------------------------------------------------------------------------------------------|
    |          |          |          |                                                        |          |░░░░░░|        |        |        |
    |          |          |          |                                                        |          |░░░░░░|        |        |        |
    |          |          |          |                                                        | Func     |░░░░░░|        |        |        |
    '--------------------------------------------------------------------------------------------------------------------------------------'
  */

   //--------------------------------------------------------------------------------------------------------------------------------------.
   //        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
   //        |        |        |        |        |        |        |        |        |        |        |        |        |                 |
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,     
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //            |        |        |        |        |        |        |        |        |        |        |        |        |             |
   //            |        |        |        |        |        |        |        |        |        |        |        |        |             |
     KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //               |        |        |        |        |        |        |        |        |        |        |        |                   |
   //               |        |        |        |        |        |        |        |        |        |        |        |                   |
     KC_NO,          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,       
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
   //                   |        |        |        |        |        |        |        |        |        |        |░░░░░░|        |░░░░░░░░|
     KC_NO, KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   
   //--------------------------------------------------------------------------------------------------------------------------------------|
   //          |          |          |                                                        |          |░░░░░░|        |        |        |
   //          |          |          |                                                        |          |░░░░░░|        |        |        |
     KC_NO,     KC_NO,     KC_NO,     KC_NO,                                                   TD(TD_LAYER),KC_NO,KC_NO,  KC_NO,   KC_NO),
   //--------------------------------------------------------------------------------------------------------------------------------------'


};


// Custom Actions
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(_FUNCTION),  // to Function overlay
};