/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <stdint.h>

#include "altera_avalon_pio_regs.h"
#include "system.h"

#define CAMERA_1_BASE 0x8001000

#define IMAGE_WIDTH  320
#define IMAGE_HEIGHT 480

#define IMAGE_SIZE   IMAGE_WIDTH * IMAGE_HEIGHT

uint32_t image_data[IMAGE_SIZE];

int main()
{

	printf("Hello from Nios II!\n");

	uint32_t camera_1_datain;
	uint32_t pixel_count = 0;

	// Wait for image start
	while(!(IORD_ALTERA_AVALON_PIO_DATA(CAMERA_1_BASE) & 0x02000000));

	while (1){

		// Wait for valid data
		camera_1_datain = IORD_ALTERA_AVALON_PIO_DATA(CAMERA_1_BASE);
		if(camera_1_datain & 0x01000000){

			image_data[pixel_count++] = camera_1_datain & 0x00FFFFFF;

			// Wait for invalid data
			while(IORD_ALTERA_AVALON_PIO_DATA(CAMERA_1_BASE) & 0x01000000);

		}

		// Once we get a full image end it
		if(pixel_count >= IMAGE_SIZE){
			break;
		}

	}

	uint32_t i;
	for(i = 0; i < IMAGE_SIZE / 20; i++){
		printf("%06X %06X %06X %06X %06X %06X %06X %06X %06X %06X %06X %06X %06X %06X %06X %06X %06X %06X %06X %06X\n",
				image_data[i*20 +  0], image_data[i*20 +  1], image_data[i*20 +  2], image_data[i*20 +  3], image_data[i*20 +  4],
				image_data[i*20 +  5], image_data[i*20 +  6], image_data[i*20 +  7], image_data[i*20 +  8], image_data[i*20 +  9],
				image_data[i*20 + 10], image_data[i*20 + 11], image_data[i*20 + 12], image_data[i*20 + 13], image_data[i*20 + 14],
				image_data[i*20 + 15], image_data[i*20 + 16], image_data[i*20 + 17], image_data[i*20 + 18], image_data[i*20 + 19]);
	}

	while(1);

	return 0;

}
