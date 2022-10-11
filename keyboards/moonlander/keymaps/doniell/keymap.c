/* Copyright 2022 Daniel Meyer kontakt@djmeyer.de
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */



#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "sendstring_german.h"

enum layers {
  _QWERTZ,
  _KOY,
  _PROTOOLS,
  _GAME,
  _MOD3,
  _MOD4,
  _CSTSFT,
  _ADJUST
};

enum custom_keycodes {
  ND_CIRC = ML_SAFE_RANGE,
  ND_GRV,
};

bool MASK_ALT = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



  [_QWERTZ] = LAYOUT_moonlander( // not assigned: DE_ADIA
    KC_ESC,    KC_1,    KC_2,    KC_3,        KC_4,      KC_5,      _______,    _______, KC_6,   KC_7,      KC_8,        KC_9,    KC_0,    KC_BSPC,
    KC_TAB,    KC_Q,    KC_W,    KC_E,        KC_R,      KC_T,      _______,    _______, DE_Z,   KC_U,      KC_I,        KC_O,    KC_P,    DE_UDIA,
    MO(_MOD3), KC_A,    KC_S,    KC_D,        KC_F,      KC_G,      _______,    _______, KC_H,   KC_J,      KC_K,        KC_L,    DE_ODIA, MO(_MOD3),
    KC_LSFT,   DE_Y,    KC_X,    KC_C,        KC_V,      KC_B,                           KC_N,   KC_M,      KC_COMM,     KC_DOT,  DE_MINS, KC_RSFT,
    KC_LCTL,   KC_LGUI, KC_LALT, MO(_CSTSFT), MO(_MOD4),            _______,    _______,         MO(_MOD4), MO(_ADJUST), KC_RALT, KC_RGUI, KC_RCTL,
                                              KC_SPC,    KC_BSPC,   _______,    _______, KC_ENT, KC_SPC
  ),

  [_KOY] = LAYOUT_moonlander( // not assigned: DE_SS
    KC_ESC,    KC_1,    KC_2,    KC_3,        KC_4,      KC_5,    _______,    _______, KC_6,      KC_7,      KC_8,         KC_9,    KC_0,    KC_BSPC,
    KC_TAB,    KC_K,    KC_DOT,  KC_O,        KC_COMM,   DE_Y,    _______,    _______, KC_V,      KC_G,      KC_C,         KC_L,    DE_F,    DE_Z,
    MO(_MOD3), KC_H,    KC_A,    KC_E,        KC_I,      KC_U,    _______,    _______, KC_D,      KC_T,      KC_R,         KC_N,    KC_S,    MO(_MOD3),
    KC_LSFT,   KC_X,    KC_Q,    DE_ADIA,     DE_UDIA,   DE_ODIA,                      KC_B,      KC_P,      KC_W,         KC_M,    KC_J,    KC_RSFT,
    KC_LCTL,   KC_LGUI, KC_LALT, MO(_CSTSFT), MO(_MOD4),          _______,    _______,            MO(_MOD4), MO(_ADJUST),  KC_RALT, KC_RGUI, KC_RCTL,
                                              KC_SPC,    KC_BSPC, _______,    _______, KC_ENT,    KC_SPC
  ),

  [_PROTOOLS] = LAYOUT_moonlander(
    KC_ESC,    KC_1,    KC_2,    KC_3,        KC_4,         KC_5, _______,    _______, KC_6,      KC_7,      KC_8,        KC_9,    KC_0,    DE_SS,
    KC_TAB,    KC_Q,    KC_W,    KC_E,        KC_R,         KC_T, _______,    _______, DE_Z,      KC_U,      KC_I,        KC_O,    KC_P,    KC_DEL,
    MO(_MOD3), KC_A,    KC_S,    KC_D,        KC_F,         KC_G, _______,    _______, KC_H,      KC_J,      KC_K,        KC_L,    DE_HASH, MO(_MOD3),
    KC_LSFT,   DE_Y,    KC_X,    KC_C,        KC_V,         KC_B,                      KC_N,      KC_M,      KC_COMM,     KC_DOT,  DE_MINS, KC_RSFT,
    KC_LGUI,   KC_LALT, KC_LCTL, MO(_CSTSFT), MO(_MOD4),          _______,    _______,            MO(_MOD4), MO(_ADJUST), KC_RCTL, KC_RALT, KC_PENT,
                                              KC_SPC,    KC_BSPC, _______,    _______, KC_ENT,    KC_SPC
    ),

  [_GAME] = LAYOUT_moonlander(
    KC_ESC,    KC_1,    KC_2,    KC_3,        KC_4,      KC_5,    _______,    _______, KC_6,      KC_7,      KC_8,        KC_9,    KC_0,    KC_BSPC,
    KC_TAB,    KC_Q,    KC_W,    KC_E,        KC_R,      KC_T,    _______,    _______, DE_Y,      KC_U,      KC_I,        KC_O,    KC_P,    KC_DEL,
    KC_TAB,    KC_A,    KC_S,    KC_D,        KC_F,      KC_G,    _______,    _______, KC_H,      KC_J,      KC_K,        KC_L,    DE_SCLN, KC_ENT,
    KC_LSFT,   DE_Z,    KC_X,    KC_C,        KC_V,      KC_B,                         KC_N,      KC_M,      KC_COMM,     KC_DOT,  KC_UP,   KC_RSFT,
    KC_LCTL,   KC_LGUI, KC_LALT, MO(_CSTSFT), MO(_MOD4),          _______,    _______,            MO(_MOD4), MO(_ADJUST), KC_LEFT, KC_DOWN, KC_RGHT,
                                              KC_SPC,    KC_BSPC, _______,    _______, KC_ENT,    KC_SPC
    ),


  [_MOD3] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______,    _______,    _______, _______, _______, _______,  _______,  _______, _______,
    _______, _______, DE_UNDS, DE_LBRC, DE_RBRC, UC(0x005E), _______,    _______, DE_EXLM, DE_LABK, DE_RABK,  DE_EQL,   DE_AMPR, DE_AT,
    _______, DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR,    _______,    _______, DE_QUES, DE_LPRN, DE_RPRN,  DE_MINS,  DE_COLN, _______,
    _______, DE_HASH, DE_DLR,  DE_PIPE, DE_TILD, UC(0x0060),                      DE_PLUS, DE_PERC, DE_DQUO,  DE_QUOT,  DE_SCLN, _______,
    _______, _______, _______, _______, _______,             _______,    _______,          _______, _______,  _______,  _______, _______,
                                                 _______,    _______,    _______, _______, _______, _______
    ),

  [_MOD4] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, DE_SLSH, DE_ASTR, KC_PMNS, _______,
    _______, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, DE_COLN,
    _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_COMM, _______,
    _______, KC_ESC,  KC_TAB,  KC_INS,  KC_ENT,  _______,                   DE_COLN, KC_P1,   KC_P2,   KC_P3,   DE_SCLN, _______,
    _______, _______, _______, _______, _______,          _______, _______,          _______, _______, _______, _______, _______,
                                                 _______, _______, _______, _______, _______, KC_0
    ),


  [_CSTSFT] = LAYOUT_moonlander(
    _______, KC_F1,   KC_F2,      KC_F3,   KC_F4,      KC_F5,   _______,    _______, KC_F6,     KC_F7,      KC_F8,      KC_F9,      KC_F10,  KC_F11, 
    _______, _______, UC(0x2022), _______, UC(0x2013), _______, _______,    _______, _______,   UC(0x201E), UC(0x201C), UC(0x201D), _______, KC_F12, 
    _______, _______, _______,    _______, _______,    _______, _______,    _______, _______,   UC(0x201A), UC(0x2018), UC(0x2019), DE_SS,   _______,
    _______, _______, _______,    _______, _______,    _______,                      _______,   _______,    UC(0x0060), UC(0x00B4), _______, _______,
    _______, _______, _______,    _______, _______,             _______,    _______,            _______,    _______,    _______,    _______, _______,
                                           _______,    _______, _______,    _______, _______,   _______
    ),


  [_ADJUST] = LAYOUT_moonlander(
    _______, _______,     _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______,    _______,       _______,
    _______, DF(_QWERTZ), _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______,    DF(_PROTOOLS), _______,
    _______, _______,     _______, _______, _______, _______, _______,    _______, _______, _______, DF(_KOY), _______,    RGB_TOG,       _______,
    _______, _______,     _______, _______, _______, QK_BOOT,                      _______, _______, _______,  _______,    _______,       _______,
    UC_M_LN, UC_M_WC,     UC_M_MA, UC_M_WI, _______,          _______,    _______,          _______, _______,  _______,    _______,       DF(_GAME),
                                            _______, _______, _______,    _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // if flag is set: prevent alt from activating menu bar by registering KC_F24
  if (MASK_ALT && keycode == KC_LALT) {
    if (record->event.pressed) {
      register_code(KC_F24);
      return true;
    } else {
      unregister_code(KC_F24);
      return true;
    }
  }

  if (record->event.pressed) {
    switch (keycode) {
      case ND_CIRC:
      SEND_STRING("^");
      return false;
      case ND_GRV:
      SEND_STRING("`");
      return false;
    }
  }
  return true;
}


layer_state_t default_layer_state_set_user(layer_state_t state){
  
  unsigned int act_state = get_highest_layer(state);

  // activate mask alt for Pro Tools Layer  
  if (act_state == 2) {
    MASK_ALT = true;
  } else {
    MASK_ALT = false;
  }

  // define binary led flags for the layers
    unsigned int ml_led_codes[] = {
    0b100000,   //_QWERTZ,
    0b000000,   //_KOY,
    0b010000,   //_PROTOOLS,
    0b001000,   //_GAME,
    0b000000,   //_MOD3,
    0b000000,   //_MOD4,
    0b000000,   //_CSTSFT,
    0b000000    //_ADJUST
  };

  // activates leds for the respective layer
  unsigned int code = ml_led_codes[act_state];
  ML_LED_1(((code >> 5) % 2) == 1);
  ML_LED_2(((code >> 4) % 2) == 1);
  ML_LED_3(((code >> 3) % 2) == 1);
  ML_LED_4(((code >> 2) % 2) == 1);
  ML_LED_5(((code >> 1) % 2) == 1);
  ML_LED_6((code % 2) == 1);
  return state;
}

