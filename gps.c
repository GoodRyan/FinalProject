/*
 * gps.c
 *
 *  Created on: May 4, 2014
 *      Author: C15Ryan.Good
 */
#include "gps.h"

void delay(int ammount){
	int timer = 0;
	while (timer < ammount){
	timer++;
	}
}


//void receive_data(int size, char *(data[])){




//	}
//}


//void storage(int size, char *(data[])){
//	unsigned char gps_input;
//		gps_input = Xil_In8(0x83000000);
//		delay(5); //delays ensure noise isn't accepted as a bit drop
//		if (gps_input == 0b00000000){
			//some values included for initialization purposes before recursion begins
//			receive_data(size, data);
//	}
//}


//void printStoredData(int size, char *(data[])){
//	int count = 0;
	//char bit;
	//char corrected_bit;
	//print the stored data
//	while (count < size){
	//	bit = *data[count];
	//	corrected_bit = 0b00000001 & bit;
		//print high if bit is high, low if bit is low
	//	if(corrected_bit == 0b00000001){
	///		Xil_Out8(0x83000004, 0b01000000);
	//		XUartLite_SendByte(0x84000000, '1');
	//	}
	//	else{
	//		Xil_Out8(0x83000004, 0b00000000);
	//		XUartLite_SendByte(0x84000000, '0');
//		}
//		count++;
//	}
//}
