/*
 * gps.c
 *
 *  Created on: May 4, 2014
 *      Author: C15Ryan.Good
 */
#include "gps.h"

void delay(unsigned char ammount){
	unsigned char timer = 0;
	while (timer < ammount){
	Xil_Out8(0x83000004, 0b11111111);
	timer++;
	}
}


void receive_data(unsigned char count, int size, unsigned char *data[]){

	unsigned char escape = 0;
	unsigned char escape_counter = 0;
	unsigned char gps_input;

	while(escape != 1 && count < size){
		Xil_Out8(0x83000004, 0b11111111);
		gps_input = Xil_In8(0x83000000);
		*data[count] = gps_input;
		count++;
		delay(222); //ensuring proper delay between bit reception
		delay(222);
		Xil_Out8(0x83000004, 0b00000000);

		//logic for when to stop collecting data (8 high bits in series)
		if (gps_input == 0b00000001)	{
			escape_counter++;
		}
		if (escape_counter >= 8){
			escape = 1;
		}

	}
}


void storage(int size, unsigned char *data[]){
	unsigned char gps_input;
	unsigned char count = 0;
		gps_input = Xil_In8(0x83000000);
		delay(222); //delays ensure a full bit is received
		delay(222);
		if (gps_input == 0b00000000){
			//some values included for initialization purposes before recursion begins
			receive_data(count, size, &data[1]);
	}
}
