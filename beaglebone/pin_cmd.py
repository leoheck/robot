#!/usr/bin/python

# Beaglebone PINS: http://beagleboard.org/Support/bone101
# FIX : https://github.com/adafruit/adafruit-beaglebone-io-python/issues/34

import sys
import time
import serial
import datetime
import re

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

print
print "Run as a root"
print "Hit q to quit"
print "Please reseting arduino nano now!"
print 

pin = "P8_10"
GPIO.setup(pin, GPIO.OUT)
print "Using", pin, "pin"

while True:
	print "\n#> Hit 1/2 to turn led on/off ", 
	key = getch()
	print key
	if key == "1":
		print "#> on"
		GPIO.output(pin, GPIO.LOW)

	elif key == "2":
		print "#> off"
		GPIO.output(pin, GPIO.HIGH)

	else:
		continue

GPIO.cleanup()
