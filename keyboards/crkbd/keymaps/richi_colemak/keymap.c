// Copyright 2022 Mark Stosberg (@markstos)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

char wpm_str[10];
char     key_namej = ' ';
uint16_t last_keycode;
uint8_t  last_row;
uint8_t  last_col;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  BATTLEFIELD,
  LOWER,
  RAISE,
  NUM,
  FUNC,
  BACKLIT
};

enum combos {
  DF_DASH,
  JK_ESC
};

const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  // Add commonly used dash to home row
  [DF_DASH]    = COMBO(df_combo, KC_MINS),
  // For Vim, put Escape on the home row
  [JK_ESC]    = COMBO(jk_combo, KC_ESC),
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers {
  _QWERTY,
  _COLEMAK,
  _BATTLEFIELD,
  _LOWER,
  _RAISE,
  _NUM,
  _FUNC,
};

// For _QWERTY layer
#define GUI_ENT     LT(_RAISE, KC_ENT)
#define LOW_TAB     LT(_LOWER, KC_TAB)
#define NUM_TAB     MT(_NUM, KC_TAB)
#define NUM_SPACE   LT(_NUM, KC_SPC)
#define OSL_FUN     OSL(_FUNC)
#define OSM_AGR     OSM(MOD_RALT)
#define OSM_LCTL    OSM(MOD_LCTL)
#define OSM_SFT     OSM(MOD_LSFT) 
#define RSE_BSP     LT(_RAISE, KC_BSPC)

// For _RAISE layer
#define CTL_ESC  LCTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_DEL  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LALT),  LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,   KC_H,LSFT_T(KC_J),   LCTL_T(KC_K),   LALT_T(KC_L),  LGUI_T(KC_QUOT) ,KC_RALT ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LSFT),   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         OSM_LCTL, NUM_SPACE, LOW_TAB,   KC_BSPC ,GUI_ENT ,KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),

  [_BATTLEFIELD] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_ESC  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_QUOT ,KC_LEFT_GUI ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
 KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         MO(_NUM), KC_SPC, KC_TAB,        KC_BSPC , KC_ENT  ,KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),
    [_COLEMAK] = LAYOUT(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                     KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_QUOT, KC_DEL  ,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    OSM(MOD_LALT),   LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_M,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O)    ,KC_RALT ,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    OSM(MOD_LSFT),   KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                     KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        OSM_LCTL, NUM_SPACE, LOW_TAB,   KC_BSPC ,GUI_ENT,KC_DEL
                                    //`--------------------------'  `--------------------------'
    ),

  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX , KC_TILD,KC_GRV, KC_LBRC, KC_LCBR,                       KC_RCBR, KC_RBRC, KC_COMM,KC_DOT,  KC_SLSH, _______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS,  KC_TRNS, LOWER,    KC_TRNS, KC_TRNS, KC_COLON
                                      //`--------------------------'  `--------------------------'
    ),


  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_DEL , XXXXXXX, KC_UNDS, KC_PLUS, KC_PGUP,                      XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_PIPE,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_END , KC_MINS, KC_EQL , KC_PGDN,                      KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_APP ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LT  , KC_GT  , KC_COPY, KC_PASTE, KC_SCLN,                      KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,_______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CTL_ESC, KC_TRNS, XXXXXXX,    RAISE  , KC_KB_MUTE, KC_TRNS\
                                      //`--------------------------'  `--------------------------'
  ), 

  [_FUNC] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_F1  , KC_F2  , KC_F3   , KC_F4 ,  KC_F5 ,                     KC_F6   , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_F11 , KC_F12 , XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , XXXXXXX, XXXXXXX, TO(_BATTLEFIELD),TO(_COLEMAK),  TO(_QWERTY) ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, FUNC   , XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [_NUM] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                      KC_NUM_LOCK, KC_P7, KC_P8, KC_P9,  	 	KC_PMNS, KC_PSLS ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                        KC_CALC,    KC_P4,    KC_P5,    KC_P6,    KC_PPLS,    KC_PAST ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX , XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, KC_P1, KC_P2,KC_P3,  KC_PDOT, _______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,  NUM, XXXXXXX,    KC_BSPC, KC_PENT,  KC_P0
                                      //`--------------------------'  `--------------------------'
    ),

};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case LT(_RAISE, KC_BSPC):
            return TAPPING_TERM_THUMB;
      case LT(_LOWER, KC_TAB):
            return TAPPING_TERM_THUMB;
      case LT(_NUM, KC_SPC):
            return TAPPING_TERM_THUMB;
      default:
            return TAPPING_TERM;
    }
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;
  }  
  return rotation;
}

static void render_status(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Colemak"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Battlefield"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case 4:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case 5:
            oled_write_ln_P(PSTR("Numpad"), false);
            break;
        case 6:
            oled_write_ln_P(PSTR("Function"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
            break;
    }
}

static const char *depad_str(const char *depad_str, char depad_char) {
    while (*depad_str == depad_char)
        ++depad_str;
    return depad_str;
}

static void oled_render_keylog(void) {
    oled_write_char('0' + last_row, false);
    oled_write_P(PSTR("x"), false);
    oled_write_char('0' + last_col, false);
    oled_write_P(PSTR(", k"), false);
    const char *last_keycode_str = get_u16_str(last_keycode, ' ');
    oled_write(depad_str(last_keycode_str, ' '), false);
    oled_write_P(PSTR(":"), false);
    oled_write_char(key_namej, false);
}

void oled_render_logo(void) {
    // clang-format off
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    // clang-format on
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
        oled_render_keylog();
		sprintf(wpm_str, "WPM  %03d", get_current_wpm());
        oled_write_ln("", false);
        oled_write(wpm_str, false);
    } 
	else {		
		oled_render_logo();
	}
    return false;
}
#endif