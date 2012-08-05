#!/usr/bin/env python

# Uses pySerial to communicate with the AVR: http://pyserial.sourceforge.net/
import serial  

# The serial port that the AVR is connected to.
TTY_PORT = '/dev/ttyUSB1'

# The baud rate which must match the BAUD defined in main.c
BAUD = 9600

# Command to send to AVR
COMMAND_HELLO = 0x01

s = serial.Serial(TTY_PORT, BAUD, timeout=1)
s.write(chr(COMMAND_HELLO))
response = s.read(255)

# Print the response as a string as well as the HEX values of each byte.
print("AVR Said: \"%s\"" % response)
print("".join([("%#0.2x " % ord(char)) for char in response]))

s.close()

