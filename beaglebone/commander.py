#!/usr/bin/python

# FIX : https://github.com/adafruit/adafruit-beaglebone-io-python/issues/34

import Adafruit_BBIO.UART as UART
import serial
import time

serial_baudrate = 230400
serial_port = "/dev/ttyO1"

ser = serial.Serial(serial_port, serial_baudrate)
ser.close()

print
print "Serial port:",  serial_port
print "Baudrate:", serial_baudrate
print 

ser.open()
if ser.isOpen():
	print ser.readline().strip('\n')
	
	ser.write("x") # print debug
	print
	print "Sending debug command"
	print ser.readline().strip('\n')
	print ser.readline().strip('\n')
	print ser.readline().strip('\n')
	print ser.readline().strip('\n')
	print ser.readline().strip('\n')


ser.close()


# Eventually, you'll want to clean up, but leave this commented for now,
# as it doesn't work yet
#UART.cleanup()
