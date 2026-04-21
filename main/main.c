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
    }
}









