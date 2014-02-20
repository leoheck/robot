
/*
** Motor.h - Library for control DC motors.
** Created by Leandro S. Heck, October, 2 2012
*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

#define MOTOR_SPEED_MIN 0
#define MOTOR_SPEED_MAX 255

enum MotorDirT
{
	Left,
	Right,
	None
};

class Motor
{
	public:

		Motor(int enable_pin, int term_a_pin, int term_b_pin);
		void stop();
		void turn(MotorDirT direction);
		void set_speed(int speed);
		void set_speed_percent(float speed);
		void incr_speed(int incr);
		int get_speed();
		float get_speed_percent();
		int get_dir();

	private:

		int enable_pin;
		int term_a_pin;
		int term_b_pin;

		MotorDirT direction;
		int speed;
};

#endif
