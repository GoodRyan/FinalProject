#include "gps.h"

int main(void)
{

  //unsigned char and_char = 0b00000001;
  unsigned char start;
  unsigned char escape = 0;
  int count = 0;
  unsigned char escape_counter = 0;
  unsigned char bit;
  unsigned char gps_input;
  int size = 300;
  unsigned char data[size];
  unsigned char bit_tracker;
  unsigned char ascii;
  start = XUartLite_RecvByte(0x84000000);

  if (start == '1'){
	  while(1){
	  count = 0;
	  while(escape != 1 && count < size){
		  gps_input = Xil_In8(0x83000000);
		  delay(2); //delays ensure noise isn't accepted as a bit drop

		  //As soon as drop occurs, data collection can begin.
		  if (gps_input == 0b00000000){



////////////////////gather data//////////////////////////////
		  	while(escape != 1 && count < size){
		  		Xil_Out8(0x83000004, 0b10000000);//allow for tracking of time to complete storage of
		  										 //one bit.
		  		gps_input = Xil_In8(0x83000000);
		  		data[count] = gps_input; //dereference array to store one bit
		  		count++;
		  		delay(396); //ensuring proper delay between bit reception
		  		delay(396); //found these numbers through guess and check
		  		Xil_Out8(0x83000004, 0b00000000);//end tracking of bit (read on logic analyzer)

		  		//below logic for when to stop collecting data (8 high bits in series)
		  		if (gps_input == 0b00000001)	{
		  			escape_counter++;
		  		}
		  			else{
		  				escape_counter = 0;
		  			}
		  		if (escape_counter >= 8){
		  			escape = 1;
		  			escape_counter = 0;
		  		}
		  	}
			}
	  }



	  ///////////////////print data//////////////////////////////
	  	  count = 0;
	  	  escape = 0;
	  	  bit_tracker = 0;
	  	  while (count < size){
	  		    ascii = 0b11111111;
	  		  	while (bit_tracker < 10){
	  			bit = data[count];
	  			bit = 0b11111110 | bit;
	  			if (bit_tracker > 0 && bit_tracker < 9){
	  				bit = rotate_right(bit, 9-bit_tracker); //the bits come in backwards and must be rotated appropriately
	  				ascii = bit & ascii;
	  			}
	  			bit_tracker++;
	  			count++;
	  		  	}
	  		  	bit_tracker = 0;
	  			XUartLite_SendByte(0x84000000, ascii); //output ascii to terminal
	  		}
	  }
	  }

  return 0;
}

