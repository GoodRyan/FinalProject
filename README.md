FinalProject
============


Required - Output GPS stream to terminal.

B - Parse GPS data into something usable by the vehicle and output data.

A - Vehicle moves after being given data provided by GPS.


18 April - Researched various GPS devices and picked one to order.

22 April - GPS arrives. I experiment with various ports to bring the UART data in, but find that I will need to manually interpret the data due to the configuration of the FPGA.

23 April - Research various RC vehicles and decide that the F150 RC truck will be the best for my purpose, as it has a truck bed that will nicely seat my FPGA.

24 April - I looked at the master UCF file and found the the port labeled R57 is really at location T3. I connected my GPS to this port along with VCC and ground. Unfortunately I did not realize that this port does not handle UART properly, and thus is not converting the input into ASCII. This has resulted in me not getting any output onto the terminal as I desired, even though I'm just running an infinite loop pulling data from T3 and outputting to terminal.

Next, I decide to take a look at the logic analyzer (LA). I power the GPS through the FPGA and connect the TX and ground signals to the LA. I then connect the ground of the FPGA to the LA ground as well. From there I was able to adjust the sampling rate and determine the start and stop bits of the gps. Next I'll need to figure out how to determine what it's saying by converting the binary to ASCII.

28 April - I've once again set up the logic analyzer. I found the clock cycle time to be 102 micro seconds, as it is a 9600 baud frequency device. 1/9600 = 104 micro seconds. For this reason, I set the sampling period to 10 micro seconds to ensure that I am not cutting any cycles off. The signal appears to be active low, as it's default state is high. Every 832 milli seconds the gps takes a reading and then outputs the data it received to the TX port. After a long analysis I have determined that each 8 bit ascii character is proceeded by a start bit (0) and then signals its end with a 1. The ascii characters are also transimitted completely backwards, which I was able to determine after noticing that strings of binary were starting with '1' which is impossible for binary. After going through and manually interpretting some of the ascii output, I have found that the general format is as follows: $GPRMC,,V(lots of commas)N*53  $GPRMC(lots of commas) N*30. 

Next I will need to get the gps signal into my project. To accomplish this I will use the all purpose JB inputs. Looking at the master UCF file, I discover that JB(0) is at location T3, so I will use this as my GPS input. At this point I'm having trouble implementing a one bit input into my project. I found out the problem was I was using quotation marks in my MPD file instead of apostraphes, making the software believe it should expect a multi-bit input. Now i'm getting another error where it is not allowing me to use location T3, as it cannot be packed into a single IOB component. I discovered that I was using the same location pin twice from previous experimentation. I fixed that issue by setting the locations correctly, and now I need to write my C program to interpret the incoming data, convert it to ASCII and output it to the terminal.

29 April - I start writing my C code by creating an unsigned char to store binary strings. Then, I put a temporary binary string 0b01000001 or "A" to test if I can send binary to the FPGA and generate ascii. This doesn't work. I test out sending "A". That doesn't work either. Next I try hex, 0x41. This doesn't work either. Not good. So I try reverting to code I know works. Receive a byte from the terminal and print it back. This doesn't work. At this point it has to be hardware related. 

30 April - I resolved the problem by checking that the correct ELF file was being used, and finding that it wasn't. However, this lead to another problem where occasionally the FPGA would take countrol of my mouse and begin exiting programs whenever I wrote to the UART port. I spent three hours attempting to resolve this issue, but in the end I decided that the best course of action was to re-install Xilinx and re-follow the instructions for lab 4b. Once that is done, we will see if the problem persists.
