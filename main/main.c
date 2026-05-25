#include "tlc5925.h"
#include "bam_led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    tlc5925_init();

    bam_init(tlc5925_channels());
    bam_start();

    while (1)
    {	
		//==================== 2 channel color =============================//		
		bam_clear();
		vTaskDelay(pdMS_TO_TICKS(500));	
		// Channel 0-1
		bam_fill(0);
		bam_set(0, 255);
		bam_set(1, 16);
		bam_swap();
		vTaskDelay(pdMS_TO_TICKS(500));		
			
		bam_clear();
		vTaskDelay(pdMS_TO_TICKS(500));	
		// Channel 1-0
		bam_fill(0);
		bam_set(1, 255);
		bam_set(0, 255);
		bam_swap();
		vTaskDelay(pdMS_TO_TICKS(500));
		
		bam_clear();
		vTaskDelay(pdMS_TO_TICKS(500));		        
		// Channel 1-2
		bam_fill(0);
		bam_set(1, 255);
		bam_set(2, 255);
		bam_swap();
		vTaskDelay(pdMS_TO_TICKS(500));
		
		bam_clear();
		vTaskDelay(pdMS_TO_TICKS(500));		        
		// Channel 2-1
		bam_fill(0);
		bam_set(2, 255);
		bam_set(1, 64);
		bam_swap();
		vTaskDelay(pdMS_TO_TICKS(500));		
		
		bam_clear();
		vTaskDelay(pdMS_TO_TICKS(500));		
		// Channel 0-2
		bam_fill(0);
		bam_set(0, 255);
		bam_set(2, 255);
		bam_swap();
		vTaskDelay(pdMS_TO_TICKS(500));	
		
		bam_clear();
		vTaskDelay(pdMS_TO_TICKS(500));		        
		// Channel 2-0
		bam_fill(0);
		bam_set(2, 255);
		bam_set(0, 16);
		bam_swap();
		vTaskDelay(pdMS_TO_TICKS(500));
    }
}



/*
#include "tlc5925.h"
#include "bam_led.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"

#define DIP0 GPIO_NUM_25   // bit 0
#define DIP1 GPIO_NUM_26   // bit 1
#define DIP2 GPIO_NUM_12   // bit 2
#define DIP3 GPIO_NUM_14  // bit 3

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;

//   DIP binary value -> color

  // 0000 = off
  // 0001 = red  	12 mA
  // 0010 = green	12.58 mA 
  // 0011 = blue	13.6 mA
  // 1011 = white	36.3 mA
  
  // ...
//
static const rgb_t color_table[16] =
{
    {  0,   0,   0},   // 0000 OFF
    {255,   0,   0},   // 0001 RED
    {  0, 255,   0},   // 0010 GREEN
    {  0,   0, 255},   // 0011 BLUE

    {255, 255,   0},   // 0100 YELLOW
    {  0, 255, 255},   // 0101 CYAN
    {255,   0, 255},   // 0110 MAGENTA
    {255, 255, 255},   // 0111 WHITE

    {255,  16,   0},   // 1000 ORANGE
    {255,  64,   0},   // 1001 AMBER
    {255,   0,  16},   // 1010 RED + small BLUE
    { 16,   0, 255},   // 1011 BLUE + small RED

    {  0, 255,  64},   // 1100 GREEN-CYAN
    { 64, 255,   0},   // 1101 LIME
    { 64,   0, 255},   // 1110 VIOLET
    {255, 128, 255},   // 1111 PINK
};

static void dip_init(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask =
            (1ULL << DIP0) |
            (1ULL << DIP1) |
            (1ULL << DIP2) |
            (1ULL << DIP3),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&io_conf);
}

static uint8_t dip_read_value(void)
{
    uint8_t value = 0;

    //
      // DIP switch wiring assumed:

      // GPIO ---- DIP ---- GND

      // OFF = input pulled HIGH = 0
       //ON  = input LOW         = 1

      // That is why the logic is inverted.
    //

    if (gpio_get_level(DIP0) == 0) value |= (1 << 0);
    if (gpio_get_level(DIP1) == 0) value |= (1 << 1);
    if (gpio_get_level(DIP2) == 0) value |= (1 << 2);
    if (gpio_get_level(DIP3) == 0) value |= (1 << 3);

    return value;
}

static void apply_rgb(rgb_t color)
{
    bam_fill(0);

    bam_set(0, color.r);   // R
    bam_set(1, color.g);   // G
    bam_set(2, color.b);   // B

    bam_swap();
}

void app_main(void)
{
    tlc5925_init();

    bam_init(tlc5925_channels());
    bam_start();

    dip_init();

    uint8_t last_dip = 0xFF;

    while (1)
    {
        uint8_t dip = dip_read_value();

        if (dip != last_dip)
        {
            last_dip = dip;

            rgb_t color = color_table[dip];
            apply_rgb(color);
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}



*/














/*


*/







/*
//==================== 1 channel color =============================//
bam_clear();
vTaskDelay(pdMS_TO_TICKS(500));

// Channel 0
bam_fill(0);
bam_set(0, 255);
bam_swap();
vTaskDelay(pdMS_TO_TICKS(500));


bam_clear();
vTaskDelay(pdMS_TO_TICKS(500));

// Channel 1
bam_fill(0);
bam_set(1, 255);
bam_swap();
vTaskDelay(pdMS_TO_TICKS(500));

bam_clear();
vTaskDelay(pdMS_TO_TICKS(500));
        
// Channel 2
bam_fill(0);
bam_set(2, 255);
bam_swap();
vTaskDelay(pdMS_TO_TICKS(500));
*/