/*
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_german_ch.h"

// Left-hand home row mods
#define RALT_X RALT_T(KC_X)
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define CTL_F LCTL_T(KC_F)

// Right-hand home row mods
#define CTL_J RCTL_T(KC_J)
#define SFT_K RSFT_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_ODI RGUI_T(CH_ODIA)
#define RALT_DT RALT_T(KC_DOT)

// Shortcuts
#define UC_COPY LCTL(KC_C)
#define UC_PSTE LCTL(KC_V)
#define UC_CUT  LCTL(KC_X)
#define UC_UNDO LCTL(CH_Z)
#define UC_REDO LCTL(CH_Y)

// Thumbcluster
#define UC_TL1 LT(MOUR, KC_ESC)
#define UC_TL2 LT(NAVR, KC_SPC)
#define UC_TL3 LT(NUMR, KC_TAB)

#define UC_TR3 LT(FUNL, KC_BSPC)
#define UC_TR2 LT(SYMB, KC_ENT)
#define UC_TR1 KC_BTN1

enum layers {
    BASE = 0,
    NAVR,
    MOUR,
    NUMR,
    FUNL,
    SYMB,
    ADJU
};

enum custom_keycodes {
    UC_REC = SAFE_RANGE
};

uint16_t record_start_stop_timer;
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// /*
//  * Base Layer
//  *
//  * ,-----------------------------------------.                              ,-----------------------------------------.
//  * |      |  Q   |  W   |  E   |  R   |  T   |                              | CH_Z |  U   |  I   |  O   |  P   |      |
//  * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
//  * |      |  A   |  S   |  D   |  F   |  G   |                              |  H   |  J   |  K   |  L   | ö  é |      |
//  * |      | GUI  | LALT | LSFT | LCTL |      |                              |      | LCTL | LSFT | LALT | GUI  |      |
//  * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
//  * |      | CH_Y |  X   |  C   |  V   |  B   |      |      |  | Lead |      |  N   |  M   | ,  ; | .  : | -  _ |      |
//  * |      |      | ALGR |      |      |      |                              |      |      |      | ALGR |      |      |
//  * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
//  *                      |      |      | ESC  | SPC  | TAB  |  | BSPC | ENT  | BTN1 |      |      |
//  *                      |      |      | MOUR | NAVR | NUMR |  | FUNL | SYMB |      |      |      |
//  *                      `----------------------------------'  `----------------------------------'
//  */
     [BASE] = LAYOUT(
       _______, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                       CH_Z   , KC_U   , KC_I   , KC_O   , KC_P   , _______,
       _______, GUI_A  , ALT_S  , SFT_D  , CTL_F  , KC_G   ,                                       KC_H   , CTL_J  , SFT_K  , ALT_L  , GUI_ODI, _______,
       _______, CH_Y   , RALT_X , KC_C   , KC_V   , KC_B   , _______, _______,   KC_LEAD, _______, KC_N   , KC_M   , KC_COMM, RALT_DT, CH_MINS, _______,
                                  _______, _______, UC_TL1 , UC_TL2 , UC_TL3 ,   UC_TR3, UC_TR2 , UC_TR1, _______ , _______
     ),

// /*
//  * Navigation Layer (Right):
//  *
//  * ,-----------------------------------------.                              ,-----------------------------------------.
//  * |      |      |      |      |      |      |                              | UNDO | REDO | WH_U | WH_D | CAPS |      |
//  * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
//  * |      |      |      |      |      |      |                              | INS  | LEFT |  UP  | DOWN | RGHT |      |
//  * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |      |  |      |      | REC  | HOME | PGUP | PGDN | END  |      |
//  * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
//  *                      |      |      |      |      |      |  | BSPC | ENT  | DEL  |      |      |
//  *                      `----------------------------------'  `----------------------------------'
//  */
     [NAVR] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                       UC_UNDO, UC_REDO, KC_WH_U, KC_WH_D, KC_CAPS, _______,
       _______, _______, _______, _______, _______, _______,                                       KC_INS , KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, _______,
       _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, UC_REC , KC_HOME, KC_PGUP, KC_PGDN, KC_END , _______,
                                  _______, _______, _______, _______, _______,   KC_BSPC, KC_ENT , KC_DEL , _______ , _______
     ),

// /*
//  * Mouse Layer (Right)
//  *
//  * ,-----------------------------------------.                              ,-----------------------------------------.
//  * |      |      |      |      |      |      |                              |      |      | WH_U | WH_D |      |      |
//  * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
//  * |      |      |      |      |      |      |                              |      |      | BTN3 | BTN2 |      |      |
//  * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |      |
//  * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
//  *                      |      |      |      |      |      |  |      |      | BTN1 |      |      |
//  *                      `----------------------------------'  `----------------------------------'
//  */
     [MOUR] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                       _______, _______, KC_WH_U, KC_WH_D, _______, _______,
       _______, _______, _______, _______, _______, _______,                                       _______, _______, KC_BTN3, KC_BTN2, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______, _______, _______,  _______, _______ , KC_BTN1, _______, _______
     ),

// /*
//  * Number Layer (Right)
//  *
//  * ,-----------------------------------------.                              ,-----------------------------------------.
//  * |      |      |      |      |      |      |                              |      | 7  / | 8  ( | 9  ) |      |      |
//  * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
//  * |      |      |      |      |      |      |                              |      | 4  ç | 5  % | 6  & |  +   |      |
//  * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |      |  |      |      |      | 1  + | 2  " | 3  * | .  : |      |
//  * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
//  *                      |      |      |      |      |      |  | BSPC | ENT  | 0  = |      |      |
//  *                      `----------------------------------'  `----------------------------------'
//  */
     [NUMR] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                       _______, KC_7   , KC_8   , KC_9   , _______, _______,
       _______, _______, _______, _______, _______, _______,                                       _______, KC_4   , KC_5   , KC_6   , CH_PLUS, _______,
       _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, KC_1   , KC_2   , KC_3   , KC_DOT , _______,
                                  _______, _______, _______, _______, _______,   KC_BSPC, KC_ENT , KC_0   , _______, _______
     ),

// /*
//  * Fn Layer (Left)
//  *
//  * ,-----------------------------------------.                              ,-----------------------------------------.
//  * |      | F12  |  F7  |  F8  |  F9  | PSCR |                              |      |      |      |      |      |      |
//  * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
//  * |      | F11  |  F4  |  F5  |  F6  | SLCK |                              |      |      |      |      |      |      |
//  * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
//  * |      | F10  |  F1  |  F2  |  F3  | PAUS |      |      |  |      |      |      |      |      |      |      |      |
//  * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
//  *                      |      |      |    	| SPC  | ADJT |  |      |      |      |      |      |
//  *                      `----------------------------------'  `----------------------------------'
//  */
     [FUNL] = LAYOUT(
       _______, KC_F12 , KC_F7  , KC_F8  , KC_F9  , KC_PSCR,                                       _______, _______, _______, _______, _______, _______,
       _______, KC_F11 , KC_F4  , KC_F5  , KC_F6  , KC_SLCK,                                       _______, _______, _______, _______, _______, _______,
       _______, KC_F10 , KC_F1  , KC_F2  , KC_F3  , KC_PAUS, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, _______, KC_SPC , LT(ADJU, KC_TAB),   _______, _______, _______, _______, _______
     ),

// /*
//  * Symbol Layer
//  *
//  * ,-----------------------------------------.                              ,-----------------------------------------.
//  * |      |  `   |  @   |  {   |  }   |  $   |                              |   ¨  |  ü   |  /   |  \   |  ^   |      |
//  * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
//  * |      |  ä   |  &   |  (   |  )   |  |   |                              |   '  |  "   |  ?   |  !   |  +   |      |
//  * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
//  * |      |  %   |  #   |  [   |  ]   |  ~   |      |      |  |      |      |   €  |  =   |  *   |  <   |  >   |      |
//  * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
//  *                      |      |      |      | SPC  | TAB  |  |      |      |      |      |      |
//  *                      `----------------------------------'  `----------------------------------'
//  */
    [SYMB] = LAYOUT(
      _______, CH_GRV , CH_AT  , CH_LCBR, CH_RCBR, CH_DLR ,                                       CH_DIAE, CH_UDIA, CH_SLSH, CH_BSLS, KC_CIRC, _______,
      _______, CH_ADIA, CH_AMPR, CH_LPRN, CH_RPRN, CH_PIPE,                                       CH_QUOT, CH_DQUO, CH_QUES, CH_EXLM, CH_PLUS, _______,
      _______, CH_PERC, CH_HASH, CH_LBRC, CH_RBRC, CH_TILD, _______, _______,   _______, _______, CH_EURO, CH_EQL , CH_ASTR, CH_LABK, CH_RABK, _______,
                                 _______, _______, _______, KC_SPC , KC_TAB ,   _______, _______, _______, _______, _______
    ),

// /*
//  * Adjust Layer
//  *
//  * ,-----------------------------------------.                              ,-----------------------------------------.
//  * |      |      |      |      |      |      |                              |      |      |      |      |      |      |
//  * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
//  * |      |  TOG | SAI  | HUI  | VAI  | MOD  |                              |      | Prev | VolDn| VolUp| Next |      |
//  * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
//  * |      |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      | Play | Mute |      |      |      |
//  * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
//  *                      |      |      |      |      |      |  |      |      |      |      |      |
//  *                      `----------------------------------'  `----------------------------------'
//  */
    [ADJU] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                        _______, _______, _______,   _______,   _______,  _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                        _______, KC_MPRV, KC_VOLD,   KC_VOLU,   KC_MNXT,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______, _______,   _______, _______, _______, KC_MPLY, KC_MUTE,   _______,   _______,  _______,
                                  _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
    ),


// -------------------------------------------------------- TEMPLATE -----------------------------------------------------------------
// /*
//  * Layer
//  *
//  * ,-----------------------------------------.                              ,-----------------------------------------.
//  * |      |      |      |      |      |      |                              |      |      |      |      |      |      |
//  * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
//  * |      |      |      |      |      |      |                              |      |      |      |      |      |      |
//  * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |      |
//  * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
//  *                      |      |      |      |      |      |  |      |      |      |      |      |
//  *                      `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
//     ),
// -----------------------------------------------------------------------------------------------------------------------------------
};

LEADER_EXTERNS();

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t macro_kc = keycode;
    
    if (keycode == UC_REC) {
        if (record->event.pressed) {
            record_start_stop_timer = timer_read();
        } else {
            if (timer_elapsed(record_start_stop_timer) > TAPPING_TERM) {  // start / stop recording
                macro_kc = DYN_REC_START1;
            } else { // play recording
                macro_kc = DYN_MACRO_PLAY1;
            }
        }
    }
    
    if (!process_dynamic_macro(macro_kc, record)) {
        return false;
    }
    
    return true;
}

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_T) { // CTRL + SHIFT + T (Reopen Tap)
            SEND_STRING(SS_LCTRL(SS_LSFT("t")));
        }
        SEQ_ONE_KEY(KC_C) { // Inline Code
            tap_code16(CH_GRV);
            tap_code16(CH_GRV);
            tap_code16(KC_LEFT);
        }
        SEQ_TWO_KEYS(KC_C, KC_B) { // Discord code block
            tap_code16(CH_GRV);
            tap_code16(CH_GRV);
            tap_code16(CH_GRV);
            tap_code16(CH_GRV);
            tap_code16(CH_GRV);
            tap_code16(CH_GRV);
            tap_code16(KC_LEFT);
            tap_code16(KC_LEFT);
            tap_code16(KC_LEFT);
            tap_code16(KC_ENT);
            tap_code16(KC_ENT);
            tap_code16(KC_UP);
        }
        SEQ_TWO_KEYS(KC_L, KC_G) { // Greeting
            SEND_STRING("Liebe Gr");
            tap_code16(CH_UDIA);
            SEND_STRING("sse\nChristoph");
        }
    }
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case NAVR:
            oled_write_P(PSTR("Nav (R)\n"), false);
            break;
        case MOUR:
            oled_write_P(PSTR("Mouse (R)\n"), false);
            break;
        case NUMR:
            oled_write_P(PSTR("Numpad (R)\n"), false);
            break;
        case FUNL:
            oled_write_P(PSTR("Fn (L)\n"), false);
            break;
        case SYMB:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case ADJU:
            oled_write_P(PSTR("RGB & Media\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK)    ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK)   ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status();
    }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case ADJU: // Underglow hue
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                break;
            case FUNL:
                // History scrubbing. For Adobe products, hold shift while moving
                // backward to go forward instead.
                if (clockwise) {
                    tap_code16(C(KC_Y));
                } else {
                    tap_code16(C(KC_Z));
                }
                break;
            case SYMB:
                if (clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
                break;
            default: // left/right
                if (clockwise) {
                    tap_code(KC_LEFT);
                } else {
                    tap_code(KC_RIGHT);
                }
                break;
        }
    }
}
#endif