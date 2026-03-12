idf_component_register(
	SRCS "main.c"
	INCLUDE_DIRS "."
	REQUIRES  tlc5925 driver esp_driver_gpio	
)