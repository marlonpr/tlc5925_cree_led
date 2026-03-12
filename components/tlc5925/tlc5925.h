#ifndef TLC5925_H
#define TLC5925_H

#include <stdint.h>
#include <stdbool.h>
#include "driver/gpio.h"

/* ================= USER CONFIG ================= */

#define TLC5925_NUM_DRIVERS   1

#define TLC5925_PIN_SIN       GPIO_NUM_23
#define TLC5925_PIN_SCLK      GPIO_NUM_2
#define TLC5925_PIN_XLAT      GPIO_NUM_5
#define TLC5925_PIN_BLANK     GPIO_NUM_4

/* ================= API ================= */

void tlc5925_init(void);

void tlc5925_clear(void);

void tlc5925_set_channel(uint16_t channel, bool state);

void tlc5925_update(void);

uint16_t tlc5925_channels(void);

#endif