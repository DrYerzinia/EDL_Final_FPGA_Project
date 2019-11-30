/*
 * kiss.h
 *
 *  Created on: Nov 18, 2019
 *      Author: DrYerzinia
 */

#ifndef KISS_H_
#define KISS_H_

#include <stdint.h>
#include <stddef.h>

typedef void (*send_byte)(uint8_t byte);

typedef enum {

	KISS_SYMBOLS__FEND  = 0xC0,
	KISS_SYMBOLS__FESC  = 0xDB,
	KISS_SYMBOLS__TFEND = 0xDC,
	KISS_SYMBOLS__TFESC = 0xDD

} kiss_symbols_e;

typedef enum {

	KISS_STATE__NORMAL,
	KISS_STATE__ESC,
	KISS_STATE__END

} kiss_state_e;

typedef struct {

	kiss_state_e  state;
	send_byte 	  send;

	kiss_state_e  rx_state;
	uint8_t *     rx_buffer;
	uint16_t	  rx_buffer_position;

} kiss_t;

void kiss_send_packet(kiss_t * kiss, const uint8_t * data, size_t len);

void kiss_start(kiss_t * kiss);
void kiss_send_data(kiss_t * kiss, const uint8_t * data, size_t len);
void kiss_end(kiss_t * kiss);

uint16_t kiss_rx_byte(kiss_t * kiss, uint8_t next_symbol);

#endif /* KISS_H_ */
