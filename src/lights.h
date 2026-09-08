/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, 2018.
 *
 * Released under the GPL License, Version 3
 */

#ifndef LIGHTS_H_
#define LIGHTS_H_

#include <stdint.h>
#include "lights_profile.h"

void lights_init(void);
void lights_set_state(uint8_t ui8_state);
/* Call every 25 ms. Input changes restart the cycle with its ON phase. */
void lights_profile_update(uint8_t lights_on, uint8_t braking);

#endif /* LIGHTS_H_ */
