#!/usr/bin/python
# -*- coding: utf-8 -*-

# Beaglebone PINS: http://beagleboard.org/Support/bone101
# FIX : https://github.com/adafruit/adafruit-beaglebone-io-python/issues/34

import os
import sys
import time
import serial

# if not root... kick out
# if not os.geteuid()==0:
# 	sys.exit("\nMust have ROOT powers to use GPIO\n")

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
		return ch

serial_baudrate = 115200
serial_port = "/dev/ttyUSB0"

print
print "Serial port:",  serial_port
print "Baudrate:", serial_baudrate
print "Arduino reseting, please wait..."

ser = serial.Serial(port=serial_port, baudrate=serial_baudrate)

if not ser.isOpen():
	exit(1)

print "Hit 'q' to quit"
print

msg = ""

while True:

	# Faz uma leitura se tiver dados
	while ser.inWaiting() > 0:
		msg += ser.read()
		if "\r\n" in msg:
			print msg,
			msg = ""

	# Caso contrario espera um comando
	else:

		ser.flush();

		print "\n#> ",
		key = getch()

		# Workaround to arrow keys
		if key == '\x1b': # Testa se é ESQ
			key = getch()
			if key == '[':
				key = getch()

		print key

		if key == "q":
			ser.close()
			print "#> Quitting, bye :)"
			exit(0)

		ser.write(key)
		time.sleep(0.1) # espera um tempo se nao nao funciona