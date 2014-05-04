#include <xuartlite_l.h>
#include <xparameters.h>
#include <time.h>

void storage(unsigned int size){
	unsigned char data[size];
	unsigned char count = 0;
	unsigned char gps_input;
	while(count < size){
		Xil_Out8(0x83000004, 0b11111111);
		gps_input = Xil_In8(0x83000000);
		data[count] = gps_input;
		count ++;
		Xil_Out8(0x83000004, 0b00000000);
	}
}

void count(unsigned char ammount){
	unsigned char timer = 0;
	while (timer < ammount){
	Xil_Out8(0x83000004, 0b11111111);
	timer++;
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
	  storage (500);


	  //gps_output = gps_input & and_char;
	  //if(gps_output == 0b00000001){
		//  XUartLite_SendByte(0x84000000, '1');
	  //}
	  //else{
		//  XUartLite_SendByte(0x84000000, '0');
	  //}

	  }
}
 return 0;
}


