
/*
** Motor.cpp - Library for control DC motors.
** Created by Leandro S. Heck, October, 2 2012
*/

#include "Motor.h"

/*
** Construtor instancia um motor a partir de seus pinos de controle
*/

Motor::Motor(int enable_pin, int term_a_pin, int term_b_pin)
{
	this->enable_pin = enable_pin;
	this->term_a_pin = term_a_pin;
	this->term_b_pin = term_b_pin;

	// Configure all pins as output
	pinMode(this->enable_pin, OUTPUT);
	pinMode(this->term_a_pin, OUTPUT);
	pinMode(this->term_b_pin, OUTPUT);

	// Inicializa o motor configurado com a velocidade maxima mas parado.
	stop();
	set_speed(MOTOR_SPEED_MAX);
}

/*
** Para parar o motor ambos os pinos de comando devem ter o mesmo valor.
*/

void Motor::stop()
{
	direction = None;
	digitalWrite(term_a_pin, LOW);
	digitalWrite(term_b_pin, LOW);
}

/*
** Para fazer o motor girar os pinos de comando devem ter valores diferentes.
** Dependendo desta combinação o motor gira para um lado ou para o outro.
** OBS.: Se o motor estiver configurado uma velocidade muito baixa ele não irá girar.
*/

void Motor::turn(MotorStateT direction)
{
	this->direction = direction;

	switch(this->direction)
	{
		case Left:
		{
			digitalWrite(term_a_pin, HIGH);
			digitalWrite(term_b_pin, LOW);
			break;
		}

		case Right:
		{
			digitalWrite(term_a_pin, LOW);
			digitalWrite(term_b_pin, HIGH);
			break;
		}

		default:
		{
			stop();
		}
	}
}

/*
** O ajuste de velocidade é feito através de PWM.
** Um valor de PWM entre 0 e 255 faz com que a tensão de alimentação seja controlada o que
** faz com que o motor aumente ou diminua a velocidade
*/

void Motor::set_speed(int speed)
{
//	this->speed = constrain(speed, MOTOR_SPEED_MIN, MOTOR_SPEED_MIN);
	this->speed = speed;
	analogWrite(enable_pin, this->speed);
}

/*
**
**
*/

void Motor::set_speed_percent(float speed)
{
	this->speed = (int) (speed / 100) * MOTOR_SPEED_MAX;
	analogWrite(enable_pin, this->speed);
}

/*
** Incrementa a velocidade com o valor passado
*/

void Motor::incr_speed(int incr)
{
	speed = speed + incr;
	if(speed > MOTOR_SPEED_MAX) speed = MOTOR_SPEED_MAX;
	else if(speed < MOTOR_SPEED_MIN) speed = MOTOR_SPEED_MIN;
	analogWrite(enable_pin, this->speed);
}

/*
**
**
*/

int Motor::get_speed()
{
	return speed;
}

/*
**
**
*/

float Motor::get_speed_percent()
{
	return ( (float) speed * 100) / MOTOR_SPEED_MAX;
}

/*
** O método get_direction retorna a direção em que o motor está girando.
** Se o motor estiver parado retorna -1
*/

int Motor::get_dir()
{
	return direction;
}
