
/* 
** RawCar.h - Library for Raw car behavior.
** Created by Leandro S. Heck, October, 2 2012
*/

#include "RawCar.h"

RawCar::RawCar(int ml_enable_pin, int ml_pole_a_pin, int ml_pole_b_pin, int mr_enable_pin, int mr_pole_a_pin, int mr_pole_b_pin)
{
	// Instancia os dois motores
	motor_l = new Motor(ml_enable_pin, ml_pole_a_pin, ml_pole_b_pin);
	motor_r = new Motor(mr_enable_pin, mr_pole_a_pin, mr_pole_b_pin);

	// Initialize motor stopped
	motor_l->set_speed(MOTOR_SPEED_MAX);
	motor_r->set_speed(MOTOR_SPEED_MAX);
	stop();
}

void RawCar::stop()
{
	motor_l->stop();
	motor_r->stop();
}

void RawCar::run(int direction)
{
	motor_l->run(direction);
	motor_r->run(direction);
}

void RawCar::turn(int side)
{
	switch(side)
	{
		case RAWCAR_SIDE_LEFT:
			motor_l->run(RAWCAR_DIR_BACKWARD);
			motor_r->run(RAWCAR_DIR_FORWARD);
			break;

		case RAWCAR_SIDE_RIGHT:
			motor_l->run(RAWCAR_DIR_FORWARD);
			motor_r->run(RAWCAR_DIR_BACKWARD);
			break;

		default:
			stop();
	}
}

void RawCar::set_speed(int speed)
{
	motor_l->set_speed(speed);
	motor_r->set_speed(speed);
}

void RawCar::set_speed_percentual(float speed)
{
	motor_l->set_speed_percentual(speed);
	motor_r->set_speed_percentual(speed);
}

void RawCar::speed_incr(bool do_increment)
{
	motor_l->speed_incr(do_increment);
	motor_r->speed_incr(do_increment);
}

// Deve passar o motor, ou o carro pra uma velocidade mais ou menos

int RawCar::get_speed()
{
 	return motor_l->get_speed();
}

// Deve passar o motor, ou o carro pra uma velocidade mais ou menos

float RawCar::get_speed_percentual()
{
	return motor_l->get_speed_percentual();
}

int RawCar::get_direction()
{
	return motor_l->get_speed_percentual();
}
