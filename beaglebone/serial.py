#!/usr/bin/python

# FIX : https://github.com/adafruit/adafruit-beaglebone-io-python/issues/34

import Adafruit_BBIO.UART as UART
import serial


ser = serial.Serial('/dev/ttyS1', 19200, timeout=1)
UART.setup("UART1")

ser = serial.Serial("/dev/ttyO1", 9600)
ser.open()

if ser.isOpen():
	print "Serial is open!"
    ser.write("Hello World!")

ser.close()



# Eventually, you'll want to clean up, but leave this commented for now,
# as it doesn't work yet
#UART.cleanup()