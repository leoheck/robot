
#include "VirtualWire.h"
#include "RawCar.h"

// Motor pins
#define M1_ENABLE_PIN  5 // Pino  1 da Ponte-H
#define M1_POLE_A_PIN 11 // Pino  2 da Ponte-H
#define M1_POLE_B_PIN 12 // Pino  7 da Ponte-H
#define M2_ENABLE_PIN  6 // Pino  9 da Ponte-H
#define M2_POLE_A_PIN 10 // Pino 10 da Ponte-H
#define M2_POLE_B_PIN  8 // Pino 15 da Ponte-H

// Keyboard codes 
#define left_arrow  28
#define up_arrow    30
#define right_arrow 29
#define down_arrow  31
#define minus_key   45
#define plus_key    61
#define space_key   32
#define c_key       99
#define m_key       109
#define d_key       100
#define h_key       104
#define numpad_0    48
#define numpad_1    49
#define numpad_2    50
#define numpad_3    51
#define numpad_4    52
#define numpad_5    53
#define numpad_6    54
#define numpad_7    55
#define numpad_8    56
#define numpad_9    57

#define CONTINUOUS_MODE 0
#define MANUAL_MODE     1

int motors_on_sense_pin = 4;
int serial_command;
int operational_mode = MANUAL_MODE;

RawCar car(M1_ENABLE_PIN, M1_POLE_A_PIN, M1_POLE_B_PIN, M2_ENABLE_PIN, M2_POLE_A_PIN, M2_POLE_B_PIN);

void setup()
{
	Serial.begin(230400);
	Serial.println(" ");
	Serial.println(" ");
	Serial.println(" ");
	Serial.println("+-----------------------------------------------------------+");
	Serial.println("|                       RAW CAR READY                       |");
	Serial.println("+-----------------------------------------------------------+");
	show_commands();

	// Configura o modulo RF
	vw_set_rx_pin(3);
	vw_setup(2000);
	vw_rx_start();


	// Pino para verificar se os motor esta ligado
	//pinMode(motors_on_sense_pin, INPUT);
}

void loop() 
{
	uint8_t rx_buffer [VW_MAX_MESSAGE_LEN];
	uint8_t buflen = VW_MAX_MESSAGE_LEN;

	/*// Ligue o motor do carro para começar
	if(not digitalRead(motors_on_sense_pin))
	{
		Serial.println(" ");
		Serial.println("#> WARNING: Motors are off!");
		Serial.println("#> Turn the car on to continue");
		Serial.println(" ");
		while(not digitalRead(motors_on_sense_pin)){};
		Serial.println("#> Car is ON!");
		Serial.println(" ");
	}*/

    if (vw_get_message(rx_buffer, &buflen)) // Non-blocking
	//while(Serial.available() > 0)
	{
		//serial_command = Serial.read();

		switch(rx_buffer[0])
		//switch(serial_command)
		{
			case up_arrow:
				Serial.println("#> Forward");
				car.run(RAWCAR_DIR_FORWARD);
				break;

			case down_arrow:
				Serial.println("#> Backward");
				car.run(RAWCAR_DIR_BACKWARD);
				break;

			case left_arrow:
				Serial.println("#> Left");
				car.turn(RAWCAR_SIDE_LEFT);
				break;

			case right_arrow:
				Serial.println("#> Right");
				car.turn(RAWCAR_SIDE_RIGHT);
				break;

			case space_key:
				Serial.println("#> Stop");
				car.stop();
				break;

			case numpad_8:
			case plus_key:
				Serial.print("#> Increasing car speed: ");
				car.speed_incr(MOTOR_SPEED_INCR);
				Serial.print(car.get_speed_percentual());
				Serial.println("%");
				break;

			case numpad_2:
			case minus_key:
				Serial.print("#> Decreasing car speed: ");
				car.speed_incr(MOTOR_SPEED_DECR);
				Serial.print(car.get_speed_percentual());
				Serial.println("%");
				break;

			case numpad_4:
			case numpad_5:
			case numpad_6:
			case numpad_0:
				Serial.print("#> Equalising speeds: ");
				//car.speed_incr(MOTOR_SPEED_DECR);
				Serial.print(car.get_speed_percentual());
				Serial.println("%");
				Serial.println("NOT IMPLEMENTED YET");
				break;

			case numpad_7:
				Serial.print("#> Decreasing motors L speed: ");
				//car.speed_incr(MOTOR_SPEED_DECR);
				Serial.print(car.get_speed_percentual());
				Serial.println("%");
				Serial.println("NOT IMPLEMENTED YET");
				break;
			case numpad_1:
				Serial.print("#> Decreasing motors L speed: ");
				//car.speed_incr(MOTOR_SPEED_DECR);
				Serial.print(car.get_speed_percentual());
				Serial.println("%");
				Serial.println("NOT IMPLEMENTED YET");
				break;

			case numpad_9:
				Serial.print("#> Decreasing motors R speed: ");
				//car.speed_incr(MOTOR_SPEED_DECR);
				Serial.print(car.get_speed_percentual());
				Serial.println("%");
				Serial.println("NOT IMPLEMENTED YET");
				break;
			case numpad_3:
				Serial.print("#> Decreasing motors R speed: ");
				//car.speed_incr(MOTOR_SPEED_DECR);
				Serial.print(car.get_speed_percentual());
				Serial.println("%");
				Serial.println("NOT IMPLEMENTED YET");
				break;

			case c_key:
				if(operational_mode == MANUAL_MODE)
				{
					Serial.println("#> Chanting operational mode to CONTINUOUS ");
					operational_mode = CONTINUOUS_MODE;
				}
				break;

			case m_key:
				if(operational_mode == CONTINUOUS_MODE)
				{
					Serial.println("#> Chanting operational mode to MANUAL ");
					operational_mode = MANUAL_MODE;
				}
				break;

			case d_key:
				show_debug();
				break;

			case h_key:
				show_commands();
				break;
		}

		// Se o modo de operacao for manual, para o carro após cada comando
		if(operational_mode == MANUAL_MODE)
		{
			delay(30);
			car.stop();
		}

		// Determine key codes
		//Serial.print("#> ");
		//Serial.println(serial_command , DEC);
	}
}

void show_debug()
{
	Serial.println("");

	// Mostra o modo de controle
	Serial.print("#> Operational mode: ");
	if(operational_mode == MANUAL_MODE) Serial.println("MANUAL");
	else Serial.println("CONTINUOUS");

	// Mostra a direcao
	Serial.print("#> Movement: ");
	//switch(car.get_direction())
	switch(1)
	{
		case RAWCAR_DIR_FORWARD:
			Serial.println("Running FORWARD");
			break;
		case RAWCAR_DIR_BACKWARD:
			Serial.println("Running BACKWARD");
			break;
		case RAWCAR_SIDE_LEFT:
			Serial.println("Turning LEFT");
			break;
		case RAWCAR_SIDE_RIGHT:
			Serial.println("Turning RIGHT");
			break;
		case RAWCAR_STOPPED:
			Serial.println("Stopped");
			break;
	}

	// Mostra a velocidade de ambos os motores
	Serial.print("#> Speed motor L: ");
	Serial.print("[SPEED]%, (PWM:");
	Serial.println("[SPEED])");
	Serial.print("#> Speed motor R: ");
	Serial.print("[SPEED]%, (PWM:");
	Serial.println("[SPEED])");

	Serial.println("");
}

void show_commands()
{
	Serial.println("");
	Serial.println("#> Commands");
	Serial.println("   ^ : Move forward");
	Serial.println("   ! : Move backward");
	Serial.println("   < : Turn left");
	Serial.println("   > : Turn right");
	Serial.println("   + : Increase speed");
	Serial.println("   - : Decrease speed");
	Serial.println("   d : Show some debug information");
	Serial.println("   c : Set operational mode to continuous");
	Serial.println("   m : Set operational mode to manual");
	Serial.println("   h : Show help commands");
	Serial.println("");
}