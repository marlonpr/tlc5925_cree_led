#include "tlc5925.h"
#include "soc/gpio_struct.h"
#include "soc/gpio_reg.h"
#include <string.h>

/* ================= GPIO MASKS ================= */

#define SIN_MASK    (1UL << TLC5925_PIN_SIN)
#define CLK_MASK    (1UL << TLC5925_PIN_SCLK)
#define XLAT_MASK   (1UL << TLC5925_PIN_XLAT)
#define BLANK_MASK  (1UL << TLC5925_PIN_BLANK)

/* Fast GPIO operations */
#define GPIO_SET(mask)  (GPIO.out_w1ts = (mask))
#define GPIO_CLR(mask)  (GPIO.out_w1tc = (mask))

/* ================= INTERNAL STATE ================= */

static uint16_t framebuffer[TLC5925_NUM_DRIVERS];

/* ================= FAST PULSES ================= */

static inline void clk_pulse(void)
{
    GPIO_SET(CLK_MASK);
    GPIO_CLR(CLK_MASK);
}

static inline void xlat_pulse(void)
{
    GPIO_SET(XLAT_MASK);
    GPIO_CLR(XLAT_MASK);
}

/* ================= DRIVER CORE ================= */

static void shift_framebuffer(void)
{
    GPIO_SET(BLANK_MASK);   // disable outputs

    for (int d = TLC5925_NUM_DRIVERS - 1; d >= 0; d--)
    {
        uint16_t data = framebuffer[d];

        for (int i = 15; i >= 0; i--)
        {
            if (data & (1 << i))
                GPIO_SET(SIN_MASK);
            else
                GPIO_CLR(SIN_MASK);

            clk_pulse();
        }
    }

    xlat_pulse();

    GPIO_CLR(BLANK_MASK);   // enable outputs
}

/* ================= PUBLIC API ================= */

void tlc5925_init(void)
{
    gpio_set_direction(TLC5925_PIN_SIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(TLC5925_PIN_SCLK, GPIO_MODE_OUTPUT);
    gpio_set_direction(TLC5925_PIN_XLAT, GPIO_MODE_OUTPUT);
    gpio_set_direction(TLC5925_PIN_BLANK, GPIO_MODE_OUTPUT);

    GPIO_CLR(SIN_MASK);
    GPIO_CLR(CLK_MASK);
    GPIO_CLR(XLAT_MASK);
    GPIO_CLR(BLANK_MASK);

    tlc5925_clear();
    tlc5925_update();
}

uint16_t tlc5925_channels(void)
{
    return TLC5925_NUM_DRIVERS * 16;
}

void tlc5925_clear(void)
{
    memset(framebuffer, 0, sizeof(framebuffer));
}

void tlc5925_set_channel(uint16_t channel, bool state)
{
    if (channel >= tlc5925_channels())
        return;

    uint16_t drv = channel / 16;
    uint16_t bit = channel % 16;

    if (state)
        framebuffer[drv] |= (1 << bit);
    else
        framebuffer[drv] &= ~(1 << bit);
}

void tlc5925_update(void)
{
    shift_framebuffer();
}