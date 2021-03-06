FinalProject
============

Introduction
============

The purpose of this lab was to create a vehicle that took coordinate inputs, and drove itself to those coordinates using a GPS. Unfortunately, the lab ended up revolving around the GPS as it was far more difficult to implement that I had expected. This is due to the fact that the Spartan6 can only interpret 9600 Baud signals when they come in through the UART port. Since I was unable to utilize this port, I had to pass it into a general port and interpret the signal myself.

Implementation/Test/Debug
===============

Required - Output GPS stream to terminal.

B - Parse and output GPS data to terminal.

A - Vehicle moves after being given data provided by GPS.


18 April - Researched various GPS devices and picked one to order.

22 April - GPS arrives. I experiment with various ports to bring the UART data in, but find that I will need to manually interpret the data due to the configuration of the FPGA.

23 April - Research various RC vehicles and decide that the F150 RC truck will be the best for my purpose, as it has a truck bed that will nicely seat my FPGA.

24 April - I looked at the master UCF file and found the the port labeled R57 is really at location T3. I connected my GPS to this port along with VCC and ground. Unfortunately I did not realize that this port does not handle UART properly, and thus is not converting the input into ASCII. This has resulted in me not getting any output onto the terminal as I desired, even though I'm just running an infinite loop pulling data from T3 and outputting to terminal.

Next, I decide to take a look at the logic analyzer (LA). I power the GPS through the FPGA and connect the TX and ground signals to the LA. I then connect the ground of the FPGA to the LA ground as well. From there I was able to adjust the sampling rate and determine the start and stop bits of the gps. Next I'll need to figure out how to determine what it's saying by converting the binary to ASCII.

28 April - I've once again set up the logic analyzer. I found the clock cycle time to be 102 micro seconds, as it is a 9600 baud frequency device. 1/9600 = 104 micro seconds. For this reason, I set the sampling period to 10 micro seconds to ensure that I am not cutting any cycles off. The signal appears to be active low, as it's default state is high. Every 832 milli seconds the gps takes a reading and then outputs the data it received to the TX port. After a long analysis I have determined that each 8 bit ascii character is proceeded by a start bit (0) and then signals its end with a 1. The ascii characters are also transimitted completely backwards, which I was able to determine after noticing that strings of binary were starting with '1' which is impossible for binary. After going through and manually interpretting some of the ascii output, I have found that the general format is as follows: $GPRMC,,V(lots of commas)N*53  $GPRMC(lots of commas) N*30. 

Next I will need to get the gps signal into my project. To accomplish this I will use the all purpose JB inputs. Looking at the master UCF file, I discover that JB(0) is at location T3, so I will use this as my GPS input. At this point I'm having trouble implementing a one bit input into my project. I found out the problem was I was using quotation marks in my MPD file instead of apostraphes, making the software believe it should expect a multi-bit input. Now i'm getting another error where it is not allowing me to use location T3, as it cannot be packed into a single IOB component. I discovered that I was using the same location pin twice from previous experimentation. I fixed that issue by setting the locations correctly, and now I need to write my C program to interpret the incoming data, convert it to ASCII and output it to the terminal.

29 April - I start writing my C code by creating an unsigned char to store binary strings. Then, I put a temporary binary string 0b01000001 or "A" to test if I can send binary to the FPGA and generate ascii. This doesn't work. I test out sending "A". That doesn't work either. Next I try hex, 0x41. This doesn't work either. Not good. So I try reverting to code I know works. Receive a byte from the terminal and print it back. This doesn't work. At this point it has to be hardware related. 

30 April - I resolved the problem by checking that the correct ELF file was being used, and finding that it wasn't. However, this lead to another problem where occasionally the FPGA would take countrol of my mouse and begin exiting programs whenever I wrote to the UART port. I spent three hours attempting to resolve this issue, but in the end I decided that the best course of action was to re-install Xilinx and re-follow the instructions for lab 4b. Once that is done, we will see if the problem persists. I'm still getting the mouse error. I'm not sure why the UART is controlling my mouse.

Out of curiosity, I decided to write a program that would only write to the FPGA when I pressed 1, and in response it would write a 2. Maybe I have to avoid flooding the UART before I have loaded the terminal? This seems to be the case. My conclusion is that if you flood UART before the terminal is loaded, is starts controlling I/O devices on your computer that you didn't intend for it to control. Interesting.

Next I'm going to try and pull data off of the JB port I attach my GPS to by "anding" bits together. This was succesful. Unfortnatly the clock doesn't line up with the GPS, so I'm pulling in a lot more 0's and 1's than I should be. To resolve this I'll need to create a delay between bit grabs. A lot of the online community said that their microblaze had a clock speed of 50MHz, which is 20 microseconds. Based on this, i used the "nop" assemply command 5 times to create a 100 microsecond delay between each bit print. Unfortunately this still does not look correct. On further inspection the clock pin is set to 100000 kHz, or 10 nanoseconds... multiplying this by 10000 yields 100 microseconds. I'll need a loop that counts to 10000. This caused the terminal to stall out, meaning it was far too much of a delay. Actually I forgot to include an increment. Maybe i'll use that instead of nop. It looks like post increment takes about 21 clock cycles. I'll have the counter increment to 10000/21 ~ 477. I rounded up to be safe. This seems to be way too fast.

Using time.h it looks like I can define 1000 clock cycles as one second. Nevermind, this doesn't work how I think it does.

1 May - In order to determine that ammount of time it takes to accomplish a while loop, I'm going to change some of my JB signals to outputs, and connect them to the logic annalyzer while the while loop outputs to one of the JB ports every time it exectutes. Through experimentation, I have determined that my bottom row are all outputs, determined by where i place the high bit in my XIL_OUT sequence. Through setting the output bit high, performing timer++ and then setting the output bit low I have found that it takes about 140 nano seconds to perform the timer++ operation. I have also found that it takes 22.5 micro seconds to count to 100 with an incrementing timer. It looks like once I count past a certain point I start getting very inconsistent results. Nevermind, now I'm getting inconsistent results no matter what I count to. I tried re-writing the code multiple times, and placing it into a seperate method, all to no avail. I'll look at it again tomorrow.

2 May - I realized the issue was that I wasn't sampling at a high enough rate. Now, by using two count to 230 functions, I am able to create a 106 micro second delay. Let's see if this works. It still looks like gibberish. Maybe the UART can't keep up? I hooked up my gps signal along with my delay signal to the logic analyzer and looked at them side by side. I was completely mid-understanding the problem. My C code can't keep up with the bits coming in through the UART. I'll need to re-write my decription algorithm in assembly, and see if that allows me to sample fast enough. I'm going to try increasing the clock speed. This didn't help much.

I checked the time it takes to store the data received and it is extremely fast. THus the main thing taking up time must be the if statements and ANDing of the bits. For this reason, I will store a portion of the GPS input into an array, and then parse and print it afterwards. This should fix the timing issue.

4 May - I'm having an issue where the data i'm pulling in only occurs during the inactive stage of the GPS receiver. I'll have to implemnt an "if" check that waits for the proper moment to pull data in. Fortunately, the rate at which I am pulling in bits now matches the rate at which they are being provided by the GPS. Now i'm struggling to write the program that will only pull in data when it is valid (when it's not just a long series of high bits). First I want to run a little test to see if i'm using the GPS port correctly. If the port I think I'm using goes high, 1's will be spit out to the terminal. The terminal reacted how I hoped it would, allowing me to move on. The code i'm writing now is broken up into a series of methods for simplification purposes. It should wait for a low bit, and then read data until it sees 8 high bits in series (signifying the end of a relevant bit stream). My approach isn't working out, so I review using pointers in C.

5 May - It looks lik my code is mostly working. It needs a longer delay however, and it exits at the wrong time. I can fix the exiting issue by resetting the high bit counter if the bits are not consecutive. After minor adjustments my timing is now dead on! Now I just need to ensure that my array is being filled as I want it to be. In order to determine this, I will experiment with a similar program in a C compiler. I installed TCC (tiny C compiler) and wrote some code in Notepad++. Unfortunately it looks like TCC won't let me write to memory. I found another compiler called "net beans" that I am going to try out.

6 May - I attempted to output the stored bits, but received nothing but high bits. I thought I could resolve the issue by anding the stored data, as the first 7 bits should be worthless. I received the same output which makes absolutely no sense.

7 May - I completely revised my approach in order to avoid having to pass arrays into functions, I am now able to read a valuable bit stream into the terminal. Now I just need to convert it to ascii. I figured out why ascii printing wasn't working. Instead of doing a bitwise "OR" I was doing a boolean "OR". The difference is | compared to ||. This has been remedied. Working B functionality.


Conclusion
==========

This lab made me much more comfortable using the logic analyzer. It will now be my go to tool whenver i need to figure out the nature of a digital signal. I also greatly improved my ability to use the C programming language to handle bits, and move them into the configuration I desire. If I were to change this lab, I would allow students to use all the tools that they have learned (arduino uno, etc) as this is supposed to be a mini-capstone.
