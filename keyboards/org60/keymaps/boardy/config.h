#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define TAPPING_TERM 250

#define TAP(keycode) register_code16(keycode); unregister_code16(keycode)

#endif

