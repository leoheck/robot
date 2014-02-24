#!/usr/bin/python

# Beaglebone PINS: http://beagleboard.org/Support/bone101
# FIX : https://github.com/adafruit/adafruit-beaglebone-io-python/issues/34

import time
import Adafruit_BBIO.GPIO as GPIO

GPIO.cleanup()

pin = "P8_10"
GPIO.setup(pin, GPIO.OUT)

print "Run as a ROOT"
print "Using", pin, "pin"

while True:

	print "#> on"
	GPIO.output(pin, GPIO.LOW)
	time.sleep(0.5)	

	print "#> off"
	GPIO.output(pin, GPIO.HIGH)
	time.sleep(0.5)	

GPIO.cleanup()
