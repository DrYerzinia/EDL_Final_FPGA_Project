/*
 * kiss.c
 *
 *  Created on: Nov 18, 2019
 *      Author: DrYerzinia
 */

#include "kiss.h"

void kiss_send_packet(kiss_t * kiss, const uint8_t * data, size_t len){

	kiss_start(kiss);
	kiss_send_data(kiss, data, len);
	kiss_end(kiss);

}

void kiss_start(kiss_t * kiss){

	kiss->state = KISS_STATE__NORMAL;
	kiss->send(KISS_SYMBOLS__FEND);

}

void kiss_send_data(kiss_t * kiss, const uint8_t * data, size_t len){

	while(len > 0){

		switch( kiss->state ){

			case KISS_STATE__NORMAL:
				{

					len--;

					uint8_t next_symbol = (*data++);
					switch( next_symbol ){
						case KISS_SYMBOLS__FEND:
							kiss->state = KISS_STATE__END;
							kiss->send(KISS_SYMBOLS__FESC);
							break;
						case KISS_SYMBOLS__FESC:
							kiss->state = KISS_STATE__ESC;
							kiss->send(KISS_SYMBOLS__FESC);
							break;
						default:
							kiss->send(next_symbol);
							break;
					}
				}
				break;

			case KISS_STATE__ESC:
				kiss->state = KISS_STATE__NORMAL;
				kiss->send(KISS_SYMBOLS__TFESC);
				break;

			case KISS_STATE__END:
				kiss->state = KISS_STATE__NORMAL;
				kiss->send(KISS_SYMBOLS__TFEND);
				break;

		}

	}

}

void kiss_end(kiss_t * kiss){

	kiss->state = KISS_STATE__NORMAL;
	kiss->send(KISS_SYMBOLS__FEND);

}

uint16_t kiss_rx_byte(kiss_t * kiss, uint8_t next_symbol){

	switch( kiss->rx_state ){

		case KISS_STATE__NORMAL:
			{

				switch( next_symbol ){

					case KISS_SYMBOLS__FEND:
						{

							uint16_t len = kiss->rx_buffer_position;

							kiss->rx_state = KISS_STATE__NORMAL;
							kiss->rx_buffer_position = 0;

							if(len > 0){
								return len;
							}

						}

						break;

					case KISS_SYMBOLS__FESC:
						kiss->rx_state = KISS_STATE__ESC;
						break;

					default:
						kiss->rx_buffer[kiss->rx_buffer_position++] = next_symbol;
						break;

				}
			}
			break;

		case KISS_STATE__ESC:
			switch( next_symbol ){
				case KISS_SYMBOLS__TFEND:
					kiss->rx_buffer[kiss->rx_buffer_position++] = KISS_SYMBOLS__FEND;
					break;

				case KISS_SYMBOLS__TFESC:
					kiss->rx_buffer[kiss->rx_buffer_position++] = KISS_SYMBOLS__FEND;
					break;

				default:
					// State machine hurt itself in confusion
					break;
			}
			kiss->rx_state = KISS_STATE__NORMAL;
			break;

	}

	return 0;

}
