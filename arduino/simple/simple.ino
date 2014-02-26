
// Simple sketch to test: serial comunication, motor and sensors connection
// Leandro Sehnem Heck

// Motor 1 pins
#define M1_EN_PIN  5
#define M1_A1_PIN 11
#define M1_A2_PIN 12

// Motor 2 pins
#define M2_EN_PIN  6
#define M2_A1_PIN 10
#define M2_A2_PIN  8

// Encoder 1
#define ENC1_PIN 3

// Encoder 2
#define ENC2_PIN 9

// Ultrasonic 1 (using analog pins)
#define US1_TRIG 14
#define US1_ECHO 15

// Ultrasonic 2 (using analog pins)
#define US2_TRIG 16
#define US2_ECHO 17

// Ultrasonic 3 (using analog pins)
#define US3_TRIG 18
#define US3_ECHO 19

// Keyboard key codes
// http://www.theasciicode.com.ar/
#define key_1 49
#define key_2 50
#define key_3 51
#define key_4 52
#define key_5 53
#define key_6 54
#define key_w 119
#define key_a 97
#define key_s 115
#define key_d 100
#define key_x 120
#define key_c 99
#define key_v 118
#define key_q 113
#define key_z 90
#define key_space 32
#define key_minus 45
#define key_equal 61

// Arrows (just last value of 3)
#define key_arrow_up   65
#define key_arrow_down 66
#define key_arrow_left 68
#define key_arrow_righ 67

// Robot commands
#define cmd_move_left     key_a
#define cmd_move_forward  key_w
#define cmd_move_right    key_d
#define cmd_move_backward key_s
#define cmd_break         key_space
#define cmd_decr_speed    key_minus
#define cmd_incr_speed    key_equal
#define cmd_read_us1      key_1
#define cmd_read_us2      key_2
#define cmd_read_us3      key_3
#define cmd_read_enc1     key_4
#define cmd_read_enc2     key_5
#define cmd_verbosity     key_v
#define cmd_debug         key_x

// M1 initial conditions
int m1_speed = 115;
bool m1_a1 = LOW;
bool m1_a2 = LOW;

// M2 initial conditions
int m2_speed = 115;
bool m2_a1 = LOW;
bool m2_a2 = LOW;

int serial_command = 0;
int verbosity = 1;

void setup()
{
	// Configure Motor 1 pins
	pinMode(M1_EN_PIN, OUTPUT);
	pinMode(M1_A1_PIN, OUTPUT);
	pinMode(M1_A2_PIN, OUTPUT);

	// Configure Motor 2 pins
	pinMode(M2_EN_PIN, OUTPUT);
	pinMode(M2_A1_PIN, OUTPUT);
	pinMode(M2_A2_PIN, OUTPUT);

	// // Configure Encoder 1
	// pinMode(ENC1_PIN, INPUT);

	// // Configure Encoder 2
	// pinMode(ENC2_PIN, INPUT);

	// // Configure Ultrasonic 1
	// pinMode(US1_ECHO, INPUT);
	// pinMode(US1_TRIG, OUTPUT);

	// // Configure Ultrasonic 2
	// pinMode(US2_ECHO, INPUT);
	// pinMode(US2_TRIG, OUTPUT);

	// // Configure Ultrasonic 3
	// pinMode(US3_ECHO, INPUT);
	// pinMode(US3_TRIG, OUTPUT);

	// Initialization Motor 1 pins
	analogWrite(M1_EN_PIN, m1_speed);
	digitalWrite(M1_A1_PIN, m1_a1);
	digitalWrite(M1_A2_PIN, m1_a2);

	// Initialization Motor 1 pins
	analogWrite(M2_EN_PIN, m2_speed);
	digitalWrite(M2_A1_PIN, m2_a1);
	digitalWrite(M2_A2_PIN, m2_a2);

	// Serial configuration
	Serial.begin(115200);
	Serial.println("[ARDUINO] Robot ready!");
	Serial.println("[ARDUINO] Hit 'v' key to change verbosity level.");
	Serial.print("[ARDUINO] Initial verbosity: ");
	Serial.println(verbosity);
}

void loop()
{
	// Para cada commando serial
	while(Serial.available() > 0)
	{
		serial_command = Serial.read();

		if(verbosity >= 2) {
			Serial.print("[ARDUINO] Received command: ");
			Serial.println(serial_command, DEC);
		}

		// Decodifica os valores
		switch(serial_command)
		{
			case key_arrow_up:
			case cmd_move_forward: {
				move_forward();
				break;
			}

			case key_arrow_down:
			case cmd_move_backward: {
				move_backward();
				break;
			}

			case key_arrow_left:
			case cmd_move_left: {
				turn_left();
				break;
			}

			case key_arrow_righ:
			case cmd_move_right: {
				turn_right();
				break;
			}

			case cmd_break: {
				break_action();
				break;
			}

			case cmd_decr_speed: {
				speed_down();
				break;
			}

			case cmd_incr_speed: {
				speed_up();
				break;
			}

			case cmd_read_us1: {
				read_ultrasonic(1);
				break;
			}

			case cmd_read_us2: {
				read_ultrasonic(2);
				break;
			}

			case cmd_read_us3: {
				read_ultrasonic(3);
				break;
			}

			case cmd_read_enc1: {
				read_encoder(1);
				break;
			}

			case cmd_read_enc2: {
				read_encoder(2);
				break;
			}

			case cmd_debug: {
				read_motors();
				read_ultrasonic(1);
				Serial.println("");
				read_ultrasonic(2);
				Serial.println("");
				read_ultrasonic(3);
				Serial.println("");
				read_encoder(1);
				Serial.println("");
				read_encoder(2);
				break;
			}

			case cmd_verbosity: {
				toggle_verbosity();
				break;
			}

			default:
			{
				Serial.println("[ARDUINO] Command not Implemented");
			}
		}
	}
}

void move_forward()
{
	if(verbosity >= 1) {
		Serial.println("[ARDUINO] Moving forward...");
	}

	m1_a1 = HIGH;
	m1_a2 = LOW;
	m2_a1 = HIGH;
	m2_a2 = LOW;

	digitalWrite(M1_A1_PIN, m1_a1);
	digitalWrite(M1_A2_PIN, m1_a2);
	digitalWrite(M2_A1_PIN, m2_a1);
	digitalWrite(M2_A2_PIN, m2_a2);
}

void move_backward()
{
	if(verbosity >= 1) {
		Serial.println("[ARDUINO] Moving backward...");
	}

	m1_a1 = LOW;
	m1_a2 = HIGH;
	m2_a1 = LOW;
	m2_a2 = HIGH;

	digitalWrite(M1_A1_PIN, m1_a1);
	digitalWrite(M1_A2_PIN, m1_a2);
	digitalWrite(M2_A1_PIN, m2_a1);
	digitalWrite(M2_A2_PIN, m2_a2);
}

void turn_left()
{
	if(verbosity >= 1) {
		Serial.println("[ARDUINO] Turing left");
	}

	m1_a1 = HIGH;
	m1_a2 = LOW;
	m2_a1 = LOW;
	m2_a2 = LOW;

	digitalWrite(M1_A1_PIN, m1_a1);
	digitalWrite(M1_A2_PIN, m1_a2);
	digitalWrite(M2_A1_PIN, m2_a1);
	digitalWrite(M2_A2_PIN, m2_a2);
}

void turn_right()
{
	if(verbosity >= 1) {
		Serial.println("[ARDUINO] Turning right");
	}

	m1_a1 = LOW;
	m1_a2 = LOW;
	m2_a1 = HIGH;
	m2_a2 = LOW;

	digitalWrite(M1_A1_PIN, m1_a1);
	digitalWrite(M1_A2_PIN, m1_a2);
	digitalWrite(M2_A1_PIN, m2_a1);
	digitalWrite(M2_A2_PIN, m2_a2);
}

void break_action()
{
	if(verbosity >= 1) {
		Serial.println("[ARDUINO] Breaking");
	}

	m1_a1 = LOW;
	m1_a2 = LOW;
	m2_a1 = LOW;
	m2_a2 = LOW;

	digitalWrite(M1_A1_PIN, m1_a1);
	digitalWrite(M1_A2_PIN, m1_a2);
	digitalWrite(M2_A1_PIN, m2_a1);
	digitalWrite(M2_A2_PIN, m2_a2);
}

void speed_up()
{
	if(m1_speed < 255)
	{
		m1_speed = m1_speed + 1;
		m2_speed = m2_speed + 1;
		if(m1_speed < 0) m1_speed = 0;
		if(m2_speed < 0) m2_speed = 0;
		if(verbosity >= 1) {
			Serial.print("[ARDUINO] Increasing speed: ");
			Serial.print(((float)m1_speed * 100) / 255);
			Serial.print("% [");
			Serial.print(m1_speed);
			Serial.println("]");
		}
		analogWrite(M1_EN_PIN, m1_speed);
		analogWrite(M2_EN_PIN, m2_speed);
	}
}

void speed_down()
{
	if(m1_speed > 0)
	{
		m1_speed = m1_speed - 1;
		m2_speed = m2_speed - 1;
		if(m1_speed < 0) m1_speed = 0;
		if(m2_speed < 0) m2_speed = 0;
		if(verbosity >= 1) {
			Serial.print("[ARDUINO] Decreasing speed: ");
			Serial.print(((float) m1_speed * 100) / 255);
			Serial.print("% [");
			Serial.print(m1_speed);
			Serial.println("]");
		}
		analogWrite(M1_EN_PIN, m1_speed);
		analogWrite(M2_EN_PIN, m2_speed);
	}
}


void read_ultrasonic(int ultrasonic_id)
{
	if(verbosity >= 1) {
		Serial.print("[ARDUINO] Reading ultrasonic ");
		Serial.println(ultrasonic_id);
	}

	Serial.println("[ARDUINO] TODO: Implement this function!!");
}

void read_encoder(int encoder_id)
{
	if(verbosity >= 1) {
		Serial.print("[ARDUINO] Reading encode ");
		Serial.println(encoder_id);
	}

	Serial.println("[ARDUINO] TODO: Implement this function!!");
}


// Show motor pin states
void read_motors()
{
	if(verbosity >= 1) {
		Serial.println("[ARDUINO] Debug");
		Serial.println("");
	}

	Serial.print("[ARDUINO] M1 EN: ");
	Serial.println(m1_speed);
	Serial.print("[ARDUINO] M1 A1: ");
	Serial.println(m1_a1);
	Serial.print("[ARDUINO] M1 A2: ");
	Serial.println(m1_a2);
	Serial.println("");
	Serial.print("[ARDUINO] M2 EN: ");
	Serial.println(m2_speed);
	Serial.print("[ARDUINO] M2 A1: ");
	Serial.println(m2_a1);
	Serial.print("[ARDUINO] M2 A2: ");
	Serial.println(m2_a2);
	Serial.println("");
}

void toggle_verbosity()
{
	// Rotate verbosity level
	switch(verbosity) {
		case 0: {
			verbosity = 1;
			break;
		}
		case 1: {
			verbosity = 2;
			break;
		}
		case 2: {
			verbosity = 0;
			break;
		}
	}

	Serial.print("[ARDUINO] Verbosity level: ");
	Serial.println(verbosity);
}