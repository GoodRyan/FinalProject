#include <xuartlite_l.h>
#include <xparameters.h>
#include <time.h>

void delay(unsigned char ammount){
	unsigned char timer = 0;
	while (timer < ammount){
	Xil_Out8(0x83000004, 0b11111111);
	timer++;
	}
}

unsigned char receive_data(unsigned char count, unsigned char size){
	unsigned char escape = 0;
	unsigned char escape_counter;
	unsigned char gps_input;
	unsigned char data[size];
	while(escape != 1){
		Xil_Out8(0x83000004, 0b11111111);
		gps_input = Xil_In8(0x83000000);
		data[count] = gps_input;
		count++;
		delay(222); //ensuring proper length
		delay(222);
		Xil_Out8(0x83000004, 0b00000000);
		if (gps_input == 0b00000001)	{
			escape_counter++;
		}
		if (escape_counter >= 8){
			escape = 1;
		}
	return count;
	}
}

void storage(unsigned int size){
	unsigned char count = 0;
	unsigned char gps_input;
	while(count < size){
		gps_input = Xil_In8(0x83000000);
		delay(222); //delays ensure a full bit is received
		delay(222);
		if (gps_input == 0b00000000){
			receive_data(count, size);
			}
		}

	}

int main(void)
{
  //unsigned char gps_input;
  //unsigned char and_char = 0b00000001;
  //unsigned char gps_output;
  unsigned char start;
  start = XUartLite_RecvByte(0x84000000);
  if (start == '1'){

	  while(1){
		  storage(500);
	  }

	  //gps_output = gps_input & and_char;
	  //if(gps_output == 0b00000001){
		//  XUartLite_SendByte(0x84000000, '1');
	  //}
	  //else{
		//  XUartLite_SendByte(0x84000000, '0');
	  //}

	  }
 return 0;
}


