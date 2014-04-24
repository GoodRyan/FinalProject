#include <xuartlite_l.h>
#include <xparameters.h>
#include <xil_io.h>

unsigned char convert_upper_to_binary(unsigned char character){

	 if (character == '1'){
		 return 0b00010000;
	 }
	 else if (character == '2'){
		 return 0b00100000;
	 }
	 else if (character == '3'){
	 		 return 0b00110000;
	 }
	 else if (character == '4'){
	 		 return 0b01000000;
	 }
	 else if (character == '5'){
	 		 return 0b01010000;
	 }
	 else if (character == '6'){
	 		 return 0b01100000;
	 }
	 else if (character == '7'){
	 	 		 return 0b01110000;
	 }
	 else if (character == '8'){
	 	 		 return 0b10000000;
	 }
	 else if (character == '9'){
	 	 		 return 0b10010000;
	 }
	 else if (character == 'A'){
	 	 		 return 0b10100000;
	 }
	 else if (character == 'B'){
	 	 		 return 0b10110000;
	 }
	 else if (character == 'C'){
	 	 		 return 0b11000000;
	 }
	 else if (character == 'D'){
	 	 		 return 0b11010000;
	 }
	 else if (character == 'E'){
	 	 		 return 0b11100000;
	 }
	 else if (character == 'F'){
	 	 		 return 0b11110000;
	 }
	 else{
		 return 0b00000000;
	 }
}

unsigned char convert_lower_to_binary(unsigned char character){
	 if (character == '1'){
		 return 0b00000001;
	 }
	 else if (character == '2'){
		 return 0b00000010;
	 }
	 else if (character == '3'){
	 		 return 0b00000011;
	 }
	 else if (character == '4'){
	 		 return 0b00000100;
	 }
	 else if (character == '5'){
	 		 return 0b00000101;
	 }
	 else if (character == '6'){
	 		 return 0b00000110;
	 }
	 else if (character == '7'){
	 	 		 return 0b00000111;
	 }
	 else if (character == '8'){
	 	 		 return 0b00001000;
	 }
	 else if (character == '9'){
	 	 		 return 0b00001001;
	 }
	 else if (character == 'A'){
	 	 		 return 0b00001010;
	 }
	 else if (character == 'B'){
	 	 		 return 0b00001101;
	 }
	 else if (character == 'C'){
	 	 		 return 0b00001100;
	 }
	 else if (character == 'D'){
	 	 		 return 0b00001101;
	 }
	 else if (character == 'E'){
	 	 		 return 0b00001110;
	 }
	 else if (character == 'F'){
	 	 		 return 0b00001111;
	 }
	 else{
		 return 0b00000000;
	 }
}

int main(void)
{

 unsigned char input_character;
 unsigned char led_counter = 0;
 unsigned char upper_led;
 unsigned char lower_led;
 unsigned char full_led;
 unsigned char switch_input;
 unsigned char swt_counter;
 unsigned char upper_switches;
 unsigned char lower_switches;

 while (1)
 {
	 while(1){
		 input_character = XUartLite_RecvByte(0x84000000);
		 XUartLite_SendByte(0x84000000, input_character);
	 }
  input_character = XUartLite_RecvByte(0x84000000);
  if (input_character == 'l' && led_counter == 0){
	  led_counter += 1;
	  XUartLite_SendByte(0x84000000, input_character);
  }
  else if (input_character == 'e' && led_counter == 1){
	  led_counter += 1;
	  XUartLite_SendByte(0x84000000, input_character);
  }
  else if (input_character == 'd' && led_counter == 2){
	  led_counter += 1;
	  XUartLite_SendByte(0x84000000, input_character);
  }
  else if (input_character == 's' && swt_counter == 0){
	  swt_counter += 1;
	  XUartLite_SendByte(0x84000000, input_character);
  }
  else if (input_character == 'w' && swt_counter == 1){
  	  swt_counter += 1;
  	  XUartLite_SendByte(0x84000000, input_character);
    }
  else if (input_character == 't' && swt_counter == 2){
  	  swt_counter += 1;
  	  XUartLite_SendByte(0x84000000, input_character);
    }
  else{
	  led_counter = 0;
	  swt_counter = 0;
	  XUartLite_SendByte(0x84000000, input_character);
  }

  if (led_counter == 3){
	  XUartLite_SendByte(0x84000000, ' ');
	  input_character = XUartLite_RecvByte(0x84000000);
	  upper_led = convert_upper_to_binary(input_character);
	  XUartLite_SendByte(0x84000000, input_character);
	  input_character = XUartLite_RecvByte(0x84000000);
	  lower_led = convert_lower_to_binary(input_character);
	  XUartLite_SendByte(0x84000000, input_character);
	  full_led = upper_led + lower_led;
	  Xil_Out8(0x83000000, full_led);
	  led_counter = 0;

	  XUartLite_SendByte(0x84000000, 10);
	  XUartLite_SendByte(0x84000000, 13);
  }
  else if (swt_counter == 3){
	  switch_input = Xil_In8(0x83000004);
	  upper_switches = (switch_input & 0xf0)>>4;
	  lower_switches = switch_input & 0xf;

	  XUartLite_SendByte(0x84000000, ' ');

	  if(upper_switches <= 9){
		 XUartLite_SendByte(0x84000000, upper_switches+48);
	  }
	  else{
		 XUartLite_SendByte(0x84000000, upper_switches+55);
	  }

	  if(lower_switches <= 9){
	     XUartLite_SendByte(0x84000000, lower_switches+48);
	  }
	  else{
	  	 XUartLite_SendByte(0x84000000, lower_switches+55);
	  }
	  swt_counter = 0;

	  XUartLite_SendByte(0x84000000, 10);
	  XUartLite_SendByte(0x84000000, 13);

  }
 }
}

