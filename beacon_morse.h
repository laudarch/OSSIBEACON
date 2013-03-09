/*
 * morse.h
 *
 *  Created on: 2012. 12. 19.
 *      Author: OSSI
 */

#ifndef BEACON_MORSE_H_
#define BEACON_MORSE_H_

#include "ossi_beacon.h"
#include "adf7012.h"

enum paramMorseSendStatus
{
	MORSE_STAND_BY = 0,
	MORSE_SENDING = 1
};

//#define MAX_DATA_SIZE 59

void morse_setSendFlag(void);
void morse_clearSendFlag(void);

//void morse_set_WPM(void);

void morse_init(void);
uint8_t morse_getStatus(void);
void morse_send(uint8_t* bytes);
void morse_stop(void);

#endif /* BEACON_MORSE_H_ */
