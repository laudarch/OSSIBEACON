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
//	beacon_taskSchedulePeriod(10);

	// test
//	morse_init();

	P3OUT &= ~PA_ON_PIN;
	/*

			P3OUT |= PA_ON_PIN;

//			volatile uint8_t i;
//			for (i = 0 ; i < 64; i++)
//			{
////			adf7012_findLockOnce(8, 1);
//			adf7012_initAllRegisters();
//			adf7012_setVCO(6, 0); // get VCO set values when PLL is locked from adf7012_lock();
//			printf("PA Level: %u\r\n",i);
//			printf("\r\n");
//			adf7012_setPALevel(i);
//			adf7012_OOK(1);
//			delay_ms(1500);
//			}


			adf7012_initAllRegisters();
			adf7012_setVCO(6, 0); // get VCO set values when PLL is locked from adf7012_lock();

			// best pa level = 35 ~ 36
			adf7012_setPALevel(35);
			adf7012_OOK(1);
*/


	while(1)
	{

		__bis_SR_register(LPM3_bits + GIE);
//		volatile uint8_t i;
//					for (i = 0 ; i < 64; i++)
//					{
//		//			adf7012_findLockOnce(8, 1);
//					adf7012_initAllRegisters();
//					adf7012_setVCO(6, 0); // get VCO set values when PLL is locked from adf7012_lock();
//					printf("PA Level: %u\r\n",i);
//					printf("\r\n");
//					// best pa level = 35 ~ 36
//					adf7012_setPALevel(i);
//					adf7012_OOK(1);
//					delay_ms(1500);
//					}


//		volatile uint8_t i,j;
//		adf7012_initAllRegisters();
//		adf7012_enable();
//		adf7012_writeAllRegisters();
//
//		for (i =0; i <15; i++)
//		{
//
//			for (j=0; j< 5; j++)
//			{
//				beacon_setExtWdtToggle();
//				adf7012_findLockOnce(i,j);
//			}
//		}





//		P3OUT |= PA_ON_PIN;
//		//adf7012_findLockOnce(5, 2);
//		adf7012_OOK(1);
//
//		delay_ms(1000);
//
//		adf7012_OOK(0);
//
//		P3OUT &= PA_ON_PIN;
//
//		delay_ms(1000);







		// Enter LPM3, interrupts enabled
//		__bis_SR_register(LPM3_bits + GIE);

		// beacon wakes up after receiving data from OBC
//		beacon_taskSchedule();







//		beacon_makePacket();
//		beacon_morseSend();

//		if(i2c_getSlaveRxDone())
//		{
//			i2c_setSlaveRxDone(0);
//			if(beaconData[2] == 0x03)
//			{
//				morse_init();
////				morse_send(hojunData);
//			}
//		}
//		beacon_dataReceive();
//		beacon_dataProcessing();
//		beacon_dataSend();
	}
}

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
