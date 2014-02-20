
/* 
** RawCar.h - Library for Raw car behavior.
** Created by Leandro S. Heck, October, 2 2012
*/

#ifndef RawCar_h
#define RawCar_h

#include "Motor.h"
#include "Arduino.h"

#define RAWCAR_DIR_FORWARD  0
#define RAWCAR_DIR_BACKWARD 1
#define RAWCAR_SIDE_LEFT    2
#define RAWCAR_SIDE_RIGHT   3
#define RAWCAR_STOPPED      4

class RawCar
{
	public:
		RawCar(int ml_enable_pin, int ml_pole_a_pin, int ml_pole_b_pin, int mr_enable_pin, int mr_pole_a_pin, int mr_pole_b_pin);
		void stop();
		void run(int direction);
		void turn(int side);
		void set_speed(int speed);

		void set_speed_percentual(float speed);
		void speed_incr(bool do_increment);
		int get_speed();
		float get_speed_percentual();
		int get_direction();


	private:
		Motor *motor_l;
		Motor *motor_r;

		int speed;
		int direction;
};

#endif