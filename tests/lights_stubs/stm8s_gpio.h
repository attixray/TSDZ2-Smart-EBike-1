#ifndef TEST_STM8S_GPIO_H
#define TEST_STM8S_GPIO_H
/* Host-only GPIO capture for tests/host_lights.c. */
#define GPIOD 0
#define GPIO_PIN_4 16
#define GPIO_MODE_OUT_PP_LOW_SLOW 0
static unsigned char lamp_output;
#define GPIO_Init(port, pin, mode) ((void)(lamp_output = 0))
#define GPIO_WriteHigh(port, pin) ((void)(lamp_output = 1))
#define GPIO_WriteLow(port, pin) ((void)(lamp_output = 0))
#endif
