/* 
 * File:   main.h
 * Author: Acer
 *
 * Created on 12 June, 2025, 7:15 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include "clcd.h"
#include "digital_keypad.h"
#include "timers.h"
#include "washing_machine.h"

#define washing_program_screen     0x01
#define water_level_screen         0x02
#define start_stop_screen          0x03
#define start_screen               0x04
#define pause                      0x05

#define reset_wash_program_screen  0x11
#define reset_nothing              0xFF

#define reset_water_level_screen   0x22
#define reset_start_stop_screen    0x33
#define reset_start_screen         0x44

#define buzzer_ddr                  TRISC1
#define fan_ddr                     TRISC2

#define buzzer                     RC1
#define fan                        RC2

#endif	/* MAIN_H */

