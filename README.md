FinalProject
============


Required - Output GPS data to terminal

B - Interface remote control car with FPGA to allow car movement

A - Car moves after being given data provided by GPS


24 April - I looked at the master UCF file and found the the port labeled R57 is really at location T3. I connected my GPS to this port along with VCC and ground. Unfortunately I did not realize that this port does not handle UART properly, and thus is not converting the input into ASCII. This has resulted in me not getting any output onto the terminal as I desired, even though I'm just running an infinite loop pulling data from T3 and outputting to terminal.

Next, I decide to take a look at the logic analyzer (LA). I power the GPS through the FPGA and connect the TX and ground signals to the LA. I then connect the ground of the FPGA to the LA ground as well. From there I was able to adjust the sampling rate and determine the start and stop bits of the gps. Next I'll need to figure out how to determine what it's saying by converting the binary to ASCII.

28 April - I've once again set up the logic analyzer. I found the clock cycle time to be 102 micro seconds, as it is a 9600 baud frequency device. 1/9600 = 104 micro seconds. For this reason, I set the sampling period to 106 micro seconds to ensure that I am not cutting any cycles off. The signal appears to be active low, as it's default state is high. Every 832 milli seconds the gps takes a reading and then outputs the data it received to the TX port. After a long analysis I have determined that each 8 bit ascii character is proceeded by a start bit (0) and then signals its end with a 1. After going through and manually interpretting some of the ascii output, I have found that the general format is as follows: $GPRMC,,V(lots of commas)N*53
