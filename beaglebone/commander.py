#!/usr/bin/python

# Beaglebone PINS: http://beagleboard.org/Support/bone101
# FIX : https://github.com/adafruit/adafruit-beaglebone-io-python/issues/34

import sys
import time
import serial
import datetime
import re

import Adafruit_BBIO.UART as UART
import Adafruit_BBIO.GPIO as GPIO

try:
    import tty, termios
except ImportError:
    # Probably Windows.
    try:
        import msvcrt
    except ImportError:
        # FIXME what to do on other platforms?
        # Just give up here.
        raise ImportError('getch not available')
    else:
        getch = msvcrt.getch
else:
    def getch():
        """getch() -> key character

        Read a single keypress from stdin and return the resulting character. 
        Nothing is echoed to the console. This call will block if a keypress 
        is not already available, but will not wait for Enter to be pressed. 

        If the pressed key was a modifier key, nothing will be detected; if
        it were a special function key, it may return the first character of
        of an escape sequence, leaving additional characters in the buffer.
        """
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
	if ch == 'q':
		exit(1)
        return ch

serial_baudrate = 230400
serial_port = "/dev/ttyO1"

ser = serial.Serial(serial_port, serial_baudrate)
ser.close()

print
print "Serial port:",  serial_port
print "Baudrate:", serial_baudrate
print "Hit q to quit"
print "Please reseting arduino nano now!"
print 

ser.open()

if ser.isOpen():

	resp = ""
	while True:
        	while ser.inWaiting() > 0:
                	data = ser.read()
                	resp += data
                	if "\r\n" in resp:
				print resp,
                	       	resp = ""
				if ser.inWaiting() <= 0:
                	        	ser.flush();
					print "\n#> ", 
					key = getch()
					print key
                        		ser.write(key)

ser.close()

# Eventually, you'll want to clean up, but leave this commented for now,
# as it doesn't work yet
#UART.cleanup()
