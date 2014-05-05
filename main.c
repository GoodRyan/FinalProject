#include <xuartlite_l.h>
#include <xparameters.h>
#include <time.h>
#include "gps.h"

int main(void)
{

  //unsigned char and_char = 0b00000001;
  unsigned char start;
  int size = 500;
  unsigned char *data[size];
  start = XUartLite_RecvByte(0x84000000);
  if (start == '1'){

	  while(1){
		  storage(size, &data[1]);
	  }

	  //if(gps_output == 0b00000001){
		//  XUartLite_SendByte(0x84000000, '1');
	  //}
	  //else{
		//  XUartLite_SendByte(0x84000000, '0');
	  //}

	  }
 return 0;
}


