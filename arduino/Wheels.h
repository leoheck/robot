
/*
** RawCar.h - Library for Raw car behavior.
** Created by Leandro S. Heck, October, 2 2012
*/

#ifndef Wheels_h
#define Wheels_h

#include "Arduino.h"
#include "Motor.h"

enum MoveDirectionT
{
	Forward,
	Backward,
	Left,
	Right,
	None
};

class Wheels
{
	public:

		Wheels(int ml_enable_pin, int ml_term_a_pin, int ml_term_b_pin, int mr_enable_pin, int mr_term_a_pin, int mr_term_b_pin);
		void stop();
		void move(int direction, int angle);
		void turn(MotorDirT side);

		void set_speed_l(int speed);
		void set_speed_r(int speed);
		void set_speed(int speed);

		void set_speed_percentual(float speed);

		void incr_speed_l(int incr);
		void incr_speed_r(int incr);
		void incr_speed(int incr);

		int get_speed_l();
		int get_speed_r();

		float get_speed_percent_l();
		float get_speed_percent_r();

		int get_dir_l();
		int get_dir_r();
		int get_dir();


	private:

		Motor *motor_l;
		Motor *motor_r;

		MoveDirectionT direction;
		int speed;
};

#endif