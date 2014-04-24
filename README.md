FinalProject
============


Required - Output GPS data to terminal

B - Interface remote control car with FPGA to allow car movement

A - Car moves after being given data provided by GPS


24 April - I looked at the master UCF file and found the the port labeled R57 is really at location T3. I connected my GPS to this port along with VCC and ground. Unfortunately I did not realize that this port does not handle UART properly, and thus is not converting the input into ASCII. This has resulted in me not getting any output onto the terminal as I desired, even though I'm just running an infinite loop pulling data from T3 and outputting to terminal.

Next, I decide to take a look at the logic analyzer (LA). I power the GPS through the FPGA and connect the TX and ground signals to the LA. I then connect the ground of the FPGA to the LA ground as well. From there I was able to adjust the sampling rate and determine the start and stop bits of the gps. Next I'll need to figure out how to determine what it's saying by converting the binary to ASCII.
