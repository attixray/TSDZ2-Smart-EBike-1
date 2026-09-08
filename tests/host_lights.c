/* Compile with a host C compiler and -I tests/lights_stubs.
 * Exercises the actual lights.c implementation without motor hardware.
 * Assertions describe the supplied 90/0, 90/100, 90/100, 120/80 profile.
 */
#include <assert.h>
#include <stdio.h>
#include "../src/lights.c"

int main(void) {
    uint8_t state, from, to;
    unsigned int tick, previous, flashes, on_ticks;
    for (state = 0; state < 4; ++state) {
        lights_init();
        previous = flashes = on_ticks = 0;
        for (tick = 0; tick < 2400; ++tick) {
            lights_profile_update(state >> 1, state & 1);
            assert(lamp_output == (state == 3 ? tick % 20 < 16 : state != 0));
            if (lamp_output && !previous) ++flashes;
            on_ticks += lamp_output;
            previous = lamp_output;
        }
        if (state == 3) {
            assert(flashes == 120);
            assert(on_ticks == 1920); /* 48 seconds ON out of 60 = 80%. */
        }
    }
    /* Every state transition, including during the dark braking phase. */
    for (from = 0; from < 4; ++from) {
        for (to = 0; to < 4; ++to) {
            if (from == to) continue;
            for (tick = 0; tick < 20; ++tick) {
                unsigned int i;
                lights_init();
                for (i = 0; i <= tick; ++i)
                    lights_profile_update(from >> 1, from & 1);
                lights_profile_update(to >> 1, to & 1);
                assert(lamp_output == (to != 0));
            }
        }
    }
    /* Initialization resets an in-progress blink. */
    lights_init();
    for (tick = 0; tick < 18; ++tick) lights_profile_update(1, 1);
    assert(lamp_output == 0);
    lights_init();
    lights_profile_update(1, 1);
    assert(lamp_output == 1);
    puts("PASS: four states, 120 flashes/minute, 80% duty, all transitions, reset");
    return 0;
}
