/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
  #define RGBLIGHT_DEFAULT_HUE 120
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_SLEEP
#endif

// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2

// The Leader key allows to flexibly assign macros to key sequences.
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 350

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
#define EE_HANDS

// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10

// For PS2 Trackpoint
#ifdef PS2_USE_INT
  // clock on pin 3 (d0, int0)
  #define PS2_CLOCK_PORT PORTD
  #define PS2_CLOCK_PIN PIND
  #define PS2_CLOCK_DDR DDRD
  #define PS2_CLOCK_BIT 0
  #define PS2_INT_INIT() do { EICRA |= ((1<<ISC01) | (0<<ISC00)); } while (0)
  #define PS2_INT_ON() do { EIMSK |= (1<<INT0); } while (0)
  #define PS2_INT_OFF() do { EIMSK &= ~(1<<INT0); } while (0)
  #define PS2_INT_VECT INT0_vect
  // data on pin 2 (d1)
  #define PS2_DATA_PORT PORTD
  #define PS2_DATA_PIN PIND
  #define PS2_DATA_DDR DDRD
  #define PS2_DATA_BIT 1
  #define PS2_MOUSE_SCROLL_BTN_MASK (1 << PS2_MOUSE_BTN_MIDDLE)
  #define PS2_MOUSE_SCROLL_BTN_SEND TAPPING_TERM
  #define PS2_MOUSE_SCROLL_DIVISOR_V 3
  #define PS2_MOUSE_SCROLL_DIVISOR_H PS2_MOUSE_SCROLL_DIVISOR_V
#endif