#!/usr/bin/python

# Beaglebone PINS: http://beagleboard.org/Support/bone101
# FIX : https://github.com/adafruit/adafruit-beaglebone-io-python/issues/34

import sys
import time
import serial

import Adafruit_BBIO.UART as UART
import Adafruit_BBIO.GPIO as GPIO

try:
    import tty, termios
except ImportError:
	# Probably Windows.
	try:
		import msvcrt
	except ImportError:
		raise ImportError('getch not available')
	else:
		getch = msvcrt.getch
else:
	def getch():
		fd = sys.stdin.fileno()
		old_settings = termios.tcgetattr(fd)
		try:
			tty.setraw(fd)
			ch = sys.stdin.read(1)
		finally:
			termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

		if ch == "q":
			exit(0)

		return ch

serial_baudrate = 230400
serial_port = "/dev/ttyO1"

ser = serial.Serial(serial_port, serial_baudrate)
ser.close()

print

led_pin = "P8_10"
GPIO.setup(led_pin, GPIO.OUT)
GPIO.output(led_pin, GPIO.LOW)
print "GPIO only run with ROOT"
print "Using", led_pin, "as reset pin"


rst_pin = "P8_9"
GPIO.setup(rst_pin, GPIO.OUT)
GPIO.output(rst_pin, GPIO.LOW)
print "GPIO only run with ROOT"
print "Using", rst_pin, "as reset pin"


print
print "Serial port:",  serial_port
print "Baudrate:", serial_baudrate
print "Hit q to quit"
#print "Please RESET arduino nano now!"
print "Automatic Arduino RESET"
print

# Reset arduino to start again
GPIO.output(rst_pin, GPIO.HIGH)
time.sleep(0.5)

# Turn of led when arduino is ready
GPIO.output(led_pin, GPIO.HIGH)

ser.open()

if not ser.isOpen():
	exit()

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
GPIO.cleanup()
