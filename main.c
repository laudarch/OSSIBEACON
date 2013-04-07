/*
 * main.c
 */

#include "ossi_beacon.h"

void beacon_dataReceive(void);
void beacon_dataProcessing(void);
void beacon_dataSend(void);

void main(void)
{
	beacon_init();
	beacon_taskSchedulePeriod(10);

	while(1)
	{

		// Enter LPM3, interrupts enabled
		__bis_SR_register(LPM3_bits + GIE);

		// beacon wakes up after receiving data from OBC
		beacon_taskSchedule();


	}
}
/*
void beacon_dataReceive(void) // uart related handler
{
	// gps
	if (uart_rxReady())
	{
		uart_clearRxFlag();
		// uart_get_byte() only works after uart ISR
		// TODO:check possibility of error!!!
		if(gps_updateData(uart_getByte()))
		{
			// if all the gps data we want are received
			gps_setReadyFlag();
			return;
		}
	}
	else
	{
		return;
	}
}

void beacon_dataProcessing(void)
{
	//gps
	// gps
	if (gps_isReady())
	{
		gps_clearReadyFlag();
		// process gps data
		// make packet from i2c and gps data

		gps_makePacket();
		// ready to send morse code
		morse_init();
	}
	else
	{
		return;
	}
}

void beacon_dataSend(void) // timer0 related handler
{
	if(morse_getStatus())
	{
		// clear the flag
		morse_clearSendFlag();
		morse_send(gps_getStream());
	}
	else
	{
		return;
	}

}
*/
