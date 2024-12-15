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
#include "song_list.h"

extern MidiDevice midi_device;

#define MIDI_CC_OFF 0
#define MIDI_CC_ON  127

enum layers {
  _QWERTZ,
  _KOY,
  _PROTOOLS,
  _GAME,
  _STREETFIGHTER,
  _MOD3,
  _MOD4,
  _MOD5,
  _ADJUST
};

enum custom_keycodes {
  ND_CIRC = SAFE_RANGE,
  ND_GRV,
  PD_STRT,
  PD_STOP,
  SOMU_6,
  BNK_DWN
};

bool MASK_ALT = false;

float SONG_BEEP[][2] = SONG(TERMINAL_SOUND);
bool CH_TGL = true;
void switch_6_and_1(void);

deferred_token PD_TOKEN;
uint32_t pomodoro_timer(uint32_t trigger_time, void *cb_arg);
void start_pd_timer(void);
void stop_pd_timer(void);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



  [_QWERTZ] = LAYOUT_moonlander( // not assigned: DE_ADIA
    KC_ESC,    KC_1,        KC_2,      KC_3,      KC_4,      KC_5,      PD_STRT,    PD_STOP,     KC_6,    KC_7,     KC_8,        KC_9,        KC_0,    KC_BSPC,
    KC_TAB,    KC_Q,        KC_W,      KC_E,      KC_R,      KC_T,      _______,    _______,     DE_Z,    KC_U,     KC_I,        KC_O,        KC_P,    DE_UDIA,
    MO(_MOD3), KC_A,        KC_S,      KC_D,      KC_F,      KC_G,      _______,    MO(_MOD4),     KC_H,    KC_J,     KC_K,        KC_L,        DE_ODIA, MO(_MOD3),
    KC_LSFT,   DE_Y,        KC_X,      KC_C,      KC_V,      KC_B,                               KC_N,    KC_M,     KC_COMM,     KC_DOT,      DE_MINS, KC_RSFT,
    KC_LCTL,   _______,     MO(_MOD5), KC_LGUI,   KC_LALT,              SOMU_6,     MO(_ADJUST),   MO(_MOD4)   ,              KC_RALT,  KC_RGUI,      _______, KC_RCTL,
                                                  MO(_MOD4), KC_SPC,    _______,    _______,     _______,  KC_SPC
  ),

  [_KOY] = LAYOUT_moonlander( // not assigned: DE_SS
    KC_ESC,    KC_1,        KC_2,      KC_3,      KC_4,      KC_5,      PD_STRT,    PD_STOP,     KC_6,    KC_7,     KC_8,        KC_9,        KC_0,    KC_BSPC,
    KC_TAB,    KC_K,        KC_DOT,    KC_O,      KC_COMM,   DE_Y,      _______,    BNK_DWN,      KC_V,    KC_G,     KC_C,        KC_L,        DE_F,    DE_Z,
    MO(_MOD3), KC_H,        KC_A,      KC_E,      KC_I,      KC_U,      _______,    MO(_MOD4),     KC_D,    KC_T,     KC_R,        KC_N,        KC_S,    MO(_MOD3),
    KC_LSFT,   KC_X,        KC_Q,      DE_ADIA,   DE_UDIA,   DE_ODIA,                            KC_B,    KC_P,     KC_W,        KC_M,        KC_J,    KC_RSFT,
    KC_LCTL,   _______,     MO(_MOD5), KC_LGUI,   KC_LALT,              SOMU_6,     MO(_ADJUST),   MO(_MOD4),                KC_RALT,  KC_RGUI,      _______, KC_RCTL,
                                                  MO(_MOD4), KC_SPC,    _______,    _______,     _______,  KC_SPC
  ),

  [_PROTOOLS] = LAYOUT_moonlander(
    KC_ESC,    KC_1,        KC_2,      KC_3,    KC_4,      KC_5,      PD_STRT,    PD_STOP,     KC_6,      KC_7,      KC_8,        KC_9,        KC_0,    DE_SS,
    KC_TAB,    KC_Q,        KC_W,      KC_E,    KC_R,      KC_T,      _______,    _______,     DE_Z,      KC_U,      KC_I,        KC_O,        KC_P,    KC_DEL,
    MO(_MOD3), KC_A,        KC_S,      KC_D,    KC_F,      KC_G,      _______,    _______,     KC_H,      KC_J,      KC_K,        KC_L,        DE_ODIA, DE_HASH,
    KC_LSFT,   DE_Y,        KC_X,      KC_C,    KC_V,      KC_B,                               KC_N,      KC_M,      KC_COMM,     KC_DOT,      DE_MINS, KC_RSFT,
    KC_LGUI,   _______,     MO(_MOD5), KC_LALT, KC_LCTL,              SOMU_6,     MO(_ADJUST),   MO(_MOD4),       KC_RCTL,   KC_RALT,          _______, KC_PENT,
                                                MO(_MOD4), KC_SPC,    _______,    _______,      _______, KC_SPC
    ),

  [_GAME] = LAYOUT_moonlander(
    KC_ESC,    KC_1,        KC_2,      KC_3,      KC_4,      KC_5,      PD_STRT,    PD_STOP,     KC_6,    KC_7,     KC_8,        KC_9,        KC_0,    KC_BSPC,
    KC_TAB,    KC_Q,        KC_W,      KC_E,      KC_R,      KC_T,      _______,    _______,     DE_Y,    KC_U,     KC_I,        KC_O,        KC_P,    KC_DEL,
    KC_TAB,    KC_A,        KC_S,      KC_D,      KC_F,      KC_G,      _______,    _______,     KC_H,    KC_J,     KC_K,        KC_L,        DE_SCLN, KC_ENT,
    KC_LSFT,   DE_Z,        KC_X,      KC_C,      KC_V,      KC_B,                               KC_N,    KC_M,     KC_COMM,     KC_DOT,      KC_UP,   KC_RSFT,
    KC_LCTL,   _______,     MO(_MOD5), KC_LGUI,   KC_LALT,              _______,    MO(_ADJUST), KC_RALT,  KC_RALT,     KC_LEFT,     KC_DOWN, KC_RIGHT,
                                                  MO(_MOD4), KC_SPC,    _______,    _______,     KC_SPC,  MO(_MOD4)
    ),


  [_STREETFIGHTER] = LAYOUT_moonlander(
    KC_ESC,    KC_1,        KC_2,      KC_3,      KC_4,      KC_5,      PD_STRT,    PD_STOP,     KC_6,    KC_7,     KC_8,        KC_9,        KC_0,    KC_BSPC,
    KC_TAB,    KC_Q,        KC_W,      KC_E,      KC_R,      KC_T,      _______,    _______,     DE_Y,    KC_U,     KC_I,        KC_O,        KC_P,    KC_DEL,
    KC_TAB,    KC_A,        KC_S,      KC_D,      KC_F,      KC_G,      _______,    _______,     KC_H,    KC_J,     KC_K,        KC_L,        DE_SCLN, KC_ENT,
    KC_LSFT,   DE_Z,        KC_X,      KC_C,      KC_V,      KC_B,                               KC_N,    KC_M,     KC_H,        KC_Z,        KC_UP,   KC_RSFT,
    KC_LCTL,   _______,     XXXXXXX,   XXXXXXX,   KC_SPC,               _______,    MO(_ADJUST), _______, _______,  _______, _______, _______,
                                                  XXXXXXX,   KC_SPC,    _______,    _______,     KC_SPC,  MO(_MOD4)
    ),


  [_MOD3] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______,    _______,    _______, _______, _______, _______,  _______,  _______, _______,
    _______, _______, DE_UNDS, DE_LBRC, DE_RBRC, UC(0x005E), _______,    _______, DE_EXLM, DE_LABK, DE_RABK,  DE_EQL,   DE_AMPR, DE_AT,
    _______, DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR,    _______,    _______, DE_QUES, DE_LPRN, DE_RPRN,  DE_MINS,  DE_COLN, _______,
    _______, DE_HASH, DE_DLR,  DE_PIPE, DE_TILD, UC(0x0060),                      DE_PLUS, DE_PERC, DE_DQUO,  DE_QUOT,  DE_SCLN, _______,
    _______, _______, _______, _______, _______,             SOMU_6,     _______,          _______, _______,  _______,  _______, _______,
                                                 _______,    _______,    _______, _______, _______, _______
    ),

  [_MOD4] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSLS, KC_PAST, KC_PMNS, _______,
    _______, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, DE_COLN,
    _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_COMM, _______,
    _______, KC_ESC,  KC_TAB,  KC_INS,  KC_ENT,  _______,                   DE_COLN, KC_P1,   KC_P2,   KC_P3,   DE_SCLN, _______,
    _______, _______, _______, _______, _______,          SOMU_6,  _______,          _______, _______, _______, _______, _______,
                                                 _______, _______, _______, _______, _______, KC_0
    ),


  [_MOD5] = LAYOUT_moonlander(
    _______, KC_F1,   KC_F2,      KC_F3,   KC_F4,      KC_F5,   _______,    _______, KC_F6,     KC_F7,      KC_F8,      KC_F9,      KC_F10,  KC_F11, 
    _______, _______, UC(0x2022), _______, UC(0x2013), _______, _______,    _______, _______,   UC(0x201E), UC(0x201C), UC(0x201D), _______, KC_F12, 
    _______, _______, _______,    _______, _______,    _______, _______,    _______, _______,   UC(0x201A), UC(0x2018), UC(0x2019), DE_SS,   _______,
    _______, _______, _______,    _______, _______,    _______,                      _______,   _______,    UC(0x0060), UC(0x00B4), _______, _______,
    _______, _______, _______,    _______, _______,             BNK_DWN,    _______,            _______,    _______,    _______,    _______, _______,
                                           _______,    _______, _______,    _______, _______,   _______
    ),


  [_ADJUST] = LAYOUT_moonlander(
    _______, _______,     _______,            _______, _______, _______, _______,    _______, _______, _______, _______,  _______,    _______,       KC_NUM,
    _______, DF(_QWERTZ), _______,            _______, _______, _______, _______,    _______, _______, _______, _______,  _______,    DF(_PROTOOLS), _______,
    _______, _______,     DF(_STREETFIGHTER), _______, _______, _______, _______,    _______, _______, _______, DF(_KOY), _______,    RGB_TOG,       _______,
    _______, _______,     _______,            _______, _______, QK_BOOT,                      _______, _______, _______,  _______,    _______,       _______,
    UC_LINX, _______,     UC_MAC,            UC_WINC, _______,          _______,    _______,          _______, _______,  _______,    _______,       DF(_GAME),
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
      case PD_STRT:
        start_pd_timer();
        return false;
      case PD_STOP:
        stop_pd_timer();
        return false;
      case SOMU_6:
        midi_send_noteon(&midi_device, 0, 13, 128);
        midi_send_noteon(&midi_device, 0, 21, 128);
        return false;
      case BNK_DWN:
        midi_send_noteon(&midi_device, 0, 40, 128);
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
    0b111000,   //_STREETFIGHTER,
    0b000000,   //_MOD3,
    0b000000,   //_MOD4,
    0b000000,   //_MOD5,
    0b000000    //_ADJUST
  };

  // activates leds for the respective layer
  unsigned int code = ml_led_codes[act_state];
  ML_LED_1(((code >> 5) % 2) == 1);
  ML_LED_2(((code >> 4) % 2) == 1);
  ML_LED_3(((code >> 3) % 2) == 1);
  // ML_LED_4(((code >> 2) % 2) == 1);
  // ML_LED_5(((code >> 1) % 2) == 1);
  // ML_LED_6((code % 2) == 1);
  return state;
}

uint32_t pomodoro_timer(uint32_t trigger_time, void *cb_arg) {
  PLAY_SONG(SONG_BEEP);
  return 200;
}

void start_pd_timer(void){
  ML_LED_4(true);
  cancel_deferred_exec(PD_TOKEN);
  PLAY_SONG(SONG_BEEP);
  PD_TOKEN = defer_exec(25*60*1000, pomodoro_timer, NULL);
}

void stop_pd_timer(void){
  ML_LED_4(false);
  cancel_deferred_exec(PD_TOKEN);
}

/*
void switch_6_and_1(void){
  int16_t offval, on1val, on6val, lv_ch1, lv_ch6;
  offval = -8000;
  on1val = 5192;
  on6val = 2192;
  lv_ch1 = CH_TGL ? on1val : offval;
  lv_ch6 = CH_TGL ? offval : on6val;

  CH_TGL = !CH_TGL;

  midi_send_pitchbend(&midi_device, 0, lv_ch1);
  midi_send_pitchbend(&midi_device, 5, lv_ch6);

}
*/
