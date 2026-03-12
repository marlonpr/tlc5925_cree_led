#include "bam_led.h"
#include "tlc5925.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_rom_sys.h"
#include <stdlib.h>
#include <string.h>

#define BAM_BITS 8
#define BAM_BASE_US 40   // ~100Hz refresh

static uint8_t *front_buffer; // displayed
static uint8_t *back_buffer;  // drawing

static uint16_t total_channels;

static volatile bool swap_requested = false;

/* ===================================================== */

static void bam_build_plane(uint8_t bit)
{
    tlc5925_clear();

    for(int ch=0; ch<total_channels; ch++)
    {
        if(front_buffer[ch] & (1 << bit))
            tlc5925_set_channel(ch, true);
    }

    tlc5925_update();
}

/* ===================================================== */

static void bam_task(void *arg)
{
    while(1)
    {
        for(uint8_t bit=0; bit<BAM_BITS; bit++)
        {
            bam_build_plane(bit);

            esp_rom_delay_us(BAM_BASE_US << bit);
        }

        /* swap only between full frames */
        if(swap_requested)
        {
            uint8_t *tmp = front_buffer;
            front_buffer = back_buffer;
            back_buffer = tmp;

            swap_requested = false;
        }
    }
}

/* ===================================================== */

void bam_init(uint16_t channels)
{
    total_channels = channels;

    front_buffer = calloc(channels, 1);
    back_buffer  = calloc(channels, 1);
}

/* write into DRAW buffer */
void bam_set(uint16_t ch, uint8_t value)
{
    if(ch >= total_channels) return;
    back_buffer[ch] = value;
}

void bam_fill(uint8_t value)
{
    memset(back_buffer, value, total_channels);
}

/* request atomic frame change */
void bam_swap(void)
{
    swap_requested = true;
}

void bam_clear(void)
{
    /* clear DRAW buffer */
    memset(back_buffer, 0, total_channels);

    /* request atomic swap */
    swap_requested = true;
}

void bam_start(void)
{
    xTaskCreatePinnedToCore(
        bam_task,
        "bam_task",
        4096,
        NULL,
        5,
        NULL,
        1);
}