/*
 * TongSheng TSDZ2 motor controller firmware/
 *
 * Copyright (C) Casainho, 2019.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include "pins.h"
#include "stm8s_gpio.h"
#include "lights.h"

static uint16_t lights_profile_phase = 0;
static uint8_t lights_profile_previous = 255;

void lights_profile_update(uint8_t lights_on, uint8_t braking) {
    /* 60000 ms/minute / 25 ms/tick = 2400 phase units per cycle.
     * Fractional accumulation avoids rounding each cycle's duration.
     */
    static const uint16_t frequency[4] = {
        LIGHTS_OFF_NO_BRAKE_FLASHES_PER_MINUTE,
        LIGHTS_OFF_BRAKE_FLASHES_PER_MINUTE,
        LIGHTS_ON_NO_BRAKE_FLASHES_PER_MINUTE,
        LIGHTS_ON_BRAKE_FLASHES_PER_MINUTE
    };
    static const uint16_t on_phase[4] = {
        LIGHTS_OFF_NO_BRAKE_DUTY_PERCENT * 24U,
        LIGHTS_OFF_BRAKE_DUTY_PERCENT * 24U,
        LIGHTS_ON_NO_BRAKE_DUTY_PERCENT * 24U,
        LIGHTS_ON_BRAKE_DUTY_PERCENT * 24U
    };
    uint8_t state = (lights_on ? 2U : 0U) | (braking ? 1U : 0U);
    if (state != lights_profile_previous) {
        lights_profile_phase = 0;
        lights_profile_previous = state;
    }
    lights_set_state(lights_profile_phase < on_phase[state]);
    lights_profile_phase += frequency[state];
    if (lights_profile_phase >= 2400U) {
        lights_profile_phase -= 2400U;
    }
}

void lights_init(void) {
    lights_profile_phase = 0;
    lights_profile_previous = 255;
    GPIO_Init(LIGHTS__PORT, LIGHTS__PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
}

void lights_set_state(uint8_t ui8_state) {
    if (ui8_state) {
        GPIO_WriteHigh(LIGHTS__PORT, LIGHTS__PIN);
    } else {
        GPIO_WriteLow(LIGHTS__PORT, LIGHTS__PIN);
    }
}
