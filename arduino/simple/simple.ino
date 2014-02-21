
// Teste simples para controle pela porta serial

// Motor pins
#define M1_EN_PIN  5 // Pino  1 da Ponte-H
#define M1_A1_PIN 11 // Pino  2 da Ponte-H
#define M1_A2_PIN 12 // Pino  7 da Ponte-H
#define M2_EN_PIN  6 // Pino 9 da Ponte-H
#define M2_A1_PIN 10 // Pino 10 da Ponte-H
#define M2_A2_PIN  8 // Pino 15 da Ponte-H

// Keyboard key codes (hex)
// http://www.theasciicode.com.ar/
#define w_key 119
#define a_key 97
#define s_key 115
#define d_key 100
#define x_key 120
#define c_key 99
#define v_key 118
#define q_key 113
#define space 32
#define minus 60
#define equal 61

// Robot commands
#define left_cmd  a_key
#define up_cmd    w_key
#define right_cmd d_key
#define down_cmd  s_key
#define stop_cmd  space
#define debug_cmd x_key
#define decr_speed_cmd minus
#define incr_speed_cmd equal

int serial_command = 0;

// M1 initial conditions
int m1_speed = 50;
bool m1_a1 = LOW;
bool m1_a2 = LOW;

// M2 initial conditions
int m2_speed = 50;
bool m2_a1 = LOW;
bool m2_a2 = LOW;

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

	// Initialization Motor 1 pins
	analogWrite(M1_EN_PIN, m1_speed);
	digitalWrite(M1_A1_PIN, m1_a1);
	digitalWrite(M1_A2_PIN, m1_a2);

	// Initialization Motor 1 pins
	analogWrite(M2_EN_PIN, m2_speed);
	digitalWrite(M2_A1_PIN, m2_a1);
	digitalWrite(M2_A2_PIN, m2_a2);

	// Serial configuration
	Serial.begin(230400);
	Serial.println("[ARDUINO] Robot ready!");
}

void loop()
{
  // Para cada commando serial
  while(Serial.available() > 0)
  {
  	serial_command = Serial.read();
  	Serial.print("[ARDUINO] Received command: ")
    Serial.println(serial_command , DEC);

    // Decodifica os valores
    switch(serial_command)
    {
      // Move forward
    case up_cmd:
      {
        Serial.println("#> Forward");
        move_forward();
        break;
      }

      // Move backward
    case down_cmd:
      {
        Serial.println("#> Backward");
        move_backward();
        break;
      }

      // Turn left
    case left_cmd:
      {
        Serial.println("#> Left");
        turn_left();
        break;
      }

      // Turn right
    case right_cmd:
      {
        Serial.println("#> Right");
        turn_right();
        break;
      }

      // Break
    case stop_cmd:
      {
        Serial.println("#> Stop");
        stop();
        break;
      }

    case decr_speed_cmd:
      {
        speed_down();
        break;
      }

    case incr_speed_cmd:
      {
        speed_up();
        break;
      }

    case debug_cmd:
	{
		debug_motors();
		break;
	}
  }
}

// Show motor pin states
void debug_motors()
{
	Serial.println("");
	Serial.print("   M1 EN: ");
	Serial.println(m1_speed);
	Serial.print("   M1 A1: ");
	Serial.println(m1_a1);
	Serial.print("   M1 A2: ");
	Serial.println(m1_a2);
	Serial.println("");
	Serial.print("   M2 EN: ");
	Serial.println(m2_speed);
	Serial.print("   M2 A1: ");
	Serial.println(m2_a1);
	Serial.print("   M2 A2: ");
	Serial.println(m2_a2);
	Serial.println("");
}

void move_forward()
{
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
	m1_a1 = LOW;
	m1_a2 = LOW;
	m2_a1 = HIGH;
	m2_a2 = LOW;

	digitalWrite(M1_A1_PIN, m1_a1);
	digitalWrite(M1_A2_PIN, m1_a2);
	digitalWrite(M2_A1_PIN, m2_a1);
	digitalWrite(M2_A2_PIN, m2_a2);
}

void stop()
{
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
		Serial.print("#> Increasing speed: ");
		Serial.print(((float)m1_speed * 100) / 255);
		Serial.print("% [");
		Serial.print(m1_speed);
		Serial.println("]");
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
		Serial.print("#> Decreasing speed: ");
		Serial.print(((float) m1_speed * 100) / 255);
		Serial.print("% [");
		Serial.print(m1_speed);
		Serial.println("]");
		analogWrite(M1_EN_PIN, m1_speed);
		analogWrite(M2_EN_PIN, m2_speed);
	}
}