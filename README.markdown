AVR USART Hello Python
======================

A simple example of serial communications with an AVR Microcontroller from a 
Python script. 

The AVR firmware is in `main.c` and is setup for an `ATMEGA8` mcu running on an 
external 8 MHZ crystal. The `build` file is a simple shell script to build the 
`.hex` file using the `avr-gcc` tool chain.

The `RX` and `TX` pins of the AVR are converted to `RS232` (eg. using a `MAX232`
chip) and connected to a serial port or a USB port via a USB to Serial converter
(eg. using a `FT232` chip). 

The `hello.py` Python script can then send a command, `0x01`, for which the AVR
will respond with the string "Hello Python!".


        [micah@octopus usart_hello_python]$ ./hello.py
        AVR Said: "Hello Python!"
        0x48 0x65 0x6c 0x6c 0x6f 0x20 0x50 0x79 0x74 0x68 0x6f 0x6e 0x21
        

