#!/usr/bin/python

# FIX : https://github.com/adafruit/adafruit-beaglebone-io-python/issues/34

import Adafruit_BBIO.UART as UART
import serial
import time

ser = serial.Serial("/dev/ttyO1", 9600)
ser.close()

incr = 0

ser.open()

if ser.isOpen():
	print ser.readline().strip('\n')
	print ser.readline().strip('\n')
	print ser.readline().strip('\n')
	ser.write("x") # print debug
	print ser.readline().strip('\n')
	print ser.readline().strip('\n')
	print ser.readline().strip('\n')
	print ser.readline().strip('\n')
	print ser.readline().strip('\n')
	print ser.readline().strip('\n')

ser.close()


# Eventually, you'll want to clean up, but leave this commented for now,
# as it doesn't work yet
#UART.cleanup()
