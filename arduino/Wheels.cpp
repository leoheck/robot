
/*
** Wheels.h - Library for Raw car behavior.
** Created by Leandro S. Heck, October, 2 2012
*/

#include "Wheels.h"

Wheels::Wheels(int ml_enable_pin, int ml_term_a_pin, int ml_term_b_pin, int mr_enable_pin, int mr_term_a_pin, int mr_term_b_pin)
{
	// Instancia os dois motores
	motor_l = new Motor(ml_enable_pin, ml_term_a_pin, ml_term_b_pin);
	motor_r = new Motor(mr_enable_pin, mr_term_a_pin, mr_term_b_pin);

	// Initialize motor with half speed
	motor_l->set_speed(MOTOR_SPEED_MAX/2);
	motor_r->set_speed(MOTOR_SPEED_MAX/2);
	stop();
}

void Wheels::stop()
{
	motor_l->stop();
	motor_r->stop();
}

/* TODO: Dependendo do angulo ele vai anda para frente ou para tras pendendo pra direita ou esquerda
**
*/

void Wheels::move(int direction, int angle)
{
	motor_l->move(direction);
	motor_r->move(direction);
}

void Wheels::turn(MotorDirT side)
{
	switch(side)
	{
		case RAWCAR_SIDE_LEFT:
			motor_l->move(Lefft);
			motor_r->move(RAWCAR_DIR_FORWARD);
			break;

		case RAWCAR_SIDE_RIGHT:
			motor_l->move(RAWCAR_DIR_FORWARD);
			motor_r->move(RAWCAR_DIR_BACKWARD);
			break;

		default:
			stop();
	}
}

void Wheels::set_speed_l(int speed)
{
	motor_l->set_speed(speed);
}

void Wheels::set_speed_r(int speed)
{
	motor_r->set_speed(speed);
}

void Wheels::set_speed(int speed)
{
	set_speed_l(speed);
	set_speed_r(speed);
}

void Wheels::set_speed_percentual(float speed)
{
	motor_l->set_speed_percentual(speed);
	motor_r->set_speed_percentual(speed);
}

void Wheels::incr_speed_l(int incr)
{
	motor_l->incr_speed(incr);
}

void Wheels::incr_speed_r(int incr)
{
	motor_r->incr_speed(incr);
}

void Wheels::incr_speed(int incr)
{
	incr_speed_l(incr);
	incr_speed_r(incr);
}


// Deve passar o motor, ou o carro pra uma velocidade mais ou menos

int Wheels::get_speed_l()
{
 	return motor_l->get_speed();
}

int Wheels::get_speed_r()
{
 	return motor_r->get_speed();
}

// Deve passar o motor, ou o carro pra uma velocidade mais ou menos

float Wheels::get_speed_percent_l()
{
	return motor_l->get_speed_percent();
}

float Wheels::get_speed_percent_r()
{
	return motor_r->get_speed_percent();
}

int Wheels::get_dir_l()
{
	return motor_l->get_dir();
}

int Wheels::get_dir_r()
{
	return motor_r->get_dir();
}

int Wheels::get_dir()
{
	return direction;
}