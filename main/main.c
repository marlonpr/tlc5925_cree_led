#include "tlc5925.h"
#include "bam_led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    tlc5925_init();

    bam_init(tlc5925_channels());
    bam_start();

	while(1)
	{
	    /* STEP 1 */
	    bam_clear();
	
	    bam_set(0, 16);
	    //bam_set(1, 16);
	
	    bam_swap();
	    vTaskDelay(pdMS_TO_TICKS(300));
	
	

	}
}


/*
	    // STEP 2 //
	    bam_clear();
	
	    bam_set(3, 255);
	    bam_set(4, 16);
	
	    bam_swap();
	    vTaskDelay(pdMS_TO_TICKS(300));
	
	
	    // STEP 3 //
	    bam_clear();
	
	    bam_set(6, 255);
	    bam_set(7, 16);
	
	    bam_swap();
	    vTaskDelay(pdMS_TO_TICKS(300));
*/











/*
#include "tlc5925.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


// -------------------- DRAWING TASK (example counter) -------------------- //
void drawing_task(void *arg)
{
	while (1)
    {
        tlc5925_clear();        
        vTaskDelay(pdMS_TO_TICKS(300));        
        
        
		//======================== PIXEL 1 ===================================//
        tlc5925_set_channel(0, true);
        tlc5925_set_channel(1, true);
        
        tlc5925_set_channel(3, true);
        tlc5925_set_channel(4, true);
        //tlc5925_set_channel(2, true);
        tlc5925_update();
        vTaskDelay(pdMS_TO_TICKS(600));
        tlc5925_clear();
        
		//============================================================================//

        tlc5925_clear();
		vTaskDelay(pdMS_TO_TICKS(300));

		//======================== PIXEL 2 ===================================//


        tlc5925_set_channel(3, true);
        tlc5925_update();
        vTaskDelay(pdMS_TO_TICKS(300));

        tlc5925_clear();
        tlc5925_set_channel(4, true);
        tlc5925_update();
        vTaskDelay(pdMS_TO_TICKS(300));

        tlc5925_clear();
        tlc5925_set_channel(5, true);
        tlc5925_update();
        vTaskDelay(pdMS_TO_TICKS(300));

        
        //============================================================================//
    }   
    
		    
    
}

void app_main(void)
{
    tlc5925_init();    
    xTaskCreatePinnedToCore(drawing_task,"drawing_task",8192,NULL,1,NULL,0);

	while (1)
    {        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }    
    
}
*/