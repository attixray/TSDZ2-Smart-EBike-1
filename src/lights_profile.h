#ifndef LIGHTS_PROFILE_H_
#define LIGHTS_PROFILE_H_

/* Four independent light profiles. Separate from JavaConfigurator's config.h.
 * Frequency: 1..2400 flashes/minute; duty: 0..100 percent.
 * 0% = always off, 100% = always on, regardless of frequency.
 * Switching edges are quantized to the 25 ms controller tick.
 */
#define LIGHTS_OFF_NO_BRAKE_FLASHES_PER_MINUTE 90
#define LIGHTS_OFF_NO_BRAKE_DUTY_PERCENT 0
#define LIGHTS_OFF_BRAKE_FLASHES_PER_MINUTE 90
#define LIGHTS_OFF_BRAKE_DUTY_PERCENT 100
#define LIGHTS_ON_NO_BRAKE_FLASHES_PER_MINUTE 90
#define LIGHTS_ON_NO_BRAKE_DUTY_PERCENT 100
#define LIGHTS_ON_BRAKE_FLASHES_PER_MINUTE 120
#define LIGHTS_ON_BRAKE_DUTY_PERCENT 80

#define LIGHTS_PROFILE_VALID(f, d) ((f) >= 1 && (f) <= 2400 && (d) >= 0 && (d) <= 100)
#if !LIGHTS_PROFILE_VALID(LIGHTS_OFF_NO_BRAKE_FLASHES_PER_MINUTE, LIGHTS_OFF_NO_BRAKE_DUTY_PERCENT) || \
    !LIGHTS_PROFILE_VALID(LIGHTS_OFF_BRAKE_FLASHES_PER_MINUTE, LIGHTS_OFF_BRAKE_DUTY_PERCENT) || \
    !LIGHTS_PROFILE_VALID(LIGHTS_ON_NO_BRAKE_FLASHES_PER_MINUTE, LIGHTS_ON_NO_BRAKE_DUTY_PERCENT) || \
    !LIGHTS_PROFILE_VALID(LIGHTS_ON_BRAKE_FLASHES_PER_MINUTE, LIGHTS_ON_BRAKE_DUTY_PERCENT)
#error Invalid light profile frequency or duty
#endif
#endif
