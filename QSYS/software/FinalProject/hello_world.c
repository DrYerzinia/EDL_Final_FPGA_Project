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

#define IMAGE_WIDTH  640
#define IMAGE_HEIGHT 480
#define IMAGE_SIZE   ( IMAGE_HEIGHT * IMAGE_WIDTH )

volatile uint32_t * image_data = 0x06000000;

int main()
{

	printf("Hello from Nios II!\n");

	uint32_t i;
	for (i = 0; i < IMAGE_SIZE; i++) {

		printf("%06X ", image_data[i]);

		if(i % 20 == 19){
			printf("\n");
		}

	}

	return 0;

}
