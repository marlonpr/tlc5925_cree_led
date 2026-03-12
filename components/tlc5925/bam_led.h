#pragma once
#include <stdint.h>

void bam_init(uint16_t channels);

void bam_set(uint16_t ch, uint8_t value);

void bam_fill(uint8_t value);

void bam_swap(void);     // atomic frame swap

void bam_start(void);

void bam_clear(void);