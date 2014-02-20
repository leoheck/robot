
/* 
** Motor.h - Library for control DC motors.
** Created by Leandro S. Heck, October, 2 2012
*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

#define MOTOR_DIRECTION_FORWARD 0 
#define MOTOR_DIRECTION_BACKWARD 1

#define MOTOR_SPEED_MIN 0 
#define MOTOR_SPEED_MAX 255

#define MOTOR_SPEED_DECR 0
#define MOTOR_SPEED_INCR 1 

class Motor
{
	public:
		Motor(int enable_pin, int cmd_a_pin, int cmd_b_pin);
		void stop();
		void run(bool direction);
		void set_speed(int speed);
		void set_speed_percentual(float speed);
		void speed_incr(bool do_increment);
		int get_speed();
		float get_speed_percentual();
		int get_direction();

	private:
		int enable_pin;
		int cmd_a_pin;
		int cmd_b_pin;
		int speed;
		int direction;
};

#endif
