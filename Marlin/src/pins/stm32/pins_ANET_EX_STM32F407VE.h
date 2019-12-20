/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * STM32F407VET6 with RAMPS-like shield
 * 'Black' STM32F407VET6 board - http://wiki.stm32duino.com/index.php?title=STM32F407
 * Shield - https://github.com/jmz52/Hardware
 */

#if !defined(STM32F4) && !defined(STM32F4xx)
  #error "Oops! Select an STM32F4 board in 'Tools > Board.'"
#elif HOTENDS > 2 || E_STEPPERS > 2
  #error "STM32F4VET6 supports up to 2 hotends / E-steppers."
#endif

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME "Anet EX"
#endif

#define DEFAULT_MACHINE_NAME "AnetEX"

#define FLASH_EEPROM_EMULATION

//
// Servos
//
#define SERVO0_PIN         PC6
#define SERVO1_PIN         PC7

//
// Limit Switches
//
#define X_MIN_PIN          PB11
#define X_MAX_PIN          PC3
#define Y_MIN_PIN          PE15
#define Y_MAX_PIN          PD12
#define Z_MIN_PIN          PB10
#define Z_MAX_PIN          PD15

//
// Steppers
//
#define X_STEP_PIN         PC4
#define X_DIR_PIN          PE4
#define X_ENABLE_PIN       PE7

#define Y_STEP_PIN         PE5
#define Y_DIR_PIN          PE2
#define Y_ENABLE_PIN       PE6

#define Z_STEP_PIN         PD5
#define Z_DIR_PIN          PD3
#define Z_ENABLE_PIN       PD6

#define E0_STEP_PIN        PD7
#define E0_DIR_PIN         PD0
#define E0_ENABLE_PIN      PB9

#define E1_STEP_PIN        PE0
#define E1_DIR_PIN         PE1
#define E1_ENABLE_PIN      PB8

//
// Temperature Sensors
//
#define TEMP_0_PIN         PA3  // T0
#define TEMP_1_PIN         PA4  // T1
#define TEMP_BED_PIN       PA5  // TB
#define TEMP_CHAMBER_PIN   PB0  // TC

//
// Heaters / Fans
//
#define HEATER_0_PIN       PA2  // Heater0
#define HEATER_1_PIN       PA6  // Heater1
#define HEATER_BED_PIN     PA1  // Hotbed

#define FAN_PIN            PA0  // Fan0
#define FAN1_PIN           PE11 // Fan1
#define FAN2_PIN           PE13 // Fan2
#define FAN3_PIN           PE14 // Fan3

//
// Misc. Functions
//
#define SDSS               PB12
#define KILL_PIN           PB1

//
// LCD / Controller
//
#define SD_DETECT_PIN      PA15

#define BEEPER_PIN         PA8
#define BTN_ENC            PC8
#define BTN_EN1            PA11
#define BTN_EN2            PD10

#define DOGLCD_CS          PD8
#define DOGLCD_A0          PD9

#define LCD_RESET_PIN	     PD11
#define NO_LCD_REINIT      // Suppress LCD re-initialization

#if ENABLED(FYSETC_MINI_12864_2_1)
  #define NEOPIXEL_PIN     PC9
#endif

#if HAS_GRAPHICAL_LCD
  #define BOARD_ST7920_DELAY_1 DELAY_NS(96)
  #define BOARD_ST7920_DELAY_2 DELAY_NS(48)
  #define BOARD_ST7920_DELAY_3 DELAY_NS(715)
#endif
