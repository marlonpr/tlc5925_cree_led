idf_component_register(
	SRCS "tlc5925.c"
		 "bam_led.c"
	INCLUDE_DIRS "."
	REQUIRES  driver esp_driver_gpio esp_driver_ledc esp_timer nvs_flash 
)