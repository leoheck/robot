
// Teste: Controlando motores (do carrinho) pela porta serial com o teclado sem PWM
// Os pinos M1_EN_PIN e M2_EN_PIN podem ser ligados no VCC para reduzir pinos mas ai será 
// perdido o controle de velocidade.

// Motor pins
#define M1_EN_PIN  5 // Pino  1 da Ponte-H
#define M1_A1_PIN 11 // Pino  2 da Ponte-H
#define M1_A2_PIN 12 // Pino  7 da Ponte-H

#define M2_EN_PIN  6 // Pino 9 da Ponte-H
#define M2_A1_PIN 10 // Pino 10 da Ponte-H
#define M2_A2_PIN  8 // Pino 15 da Ponte-H

// Arrow keys
#define left_arrow  97//28
#define up_arrow    119//30
#define right_arrow 100//29
#define down_arrow  115//31
#define minus_key   60//45
#define plus_key    62//61
#define space_key   32
#define s_key       120//115

int serial_command = 0;

int m1_speed = 25;
bool m1_a1 = LOW;
bool m1_a2 = LOW;

int m2_speed = 25;
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
  Serial.println("");
  Serial.println("... RAW CAR READY ...");
  Serial.println("Use arrow keys to control and space to break");
  Serial.println("To increase/decrease speed use + and - signs");
}

void loop() 
{
  // Para cada commando serial
  while(Serial.available() > 0)
  {
    serial_command = Serial.read();

    // Decodifica os valores
    switch(serial_command)
    {
      // Move forward
    case up_arrow:
      {
        Serial.println("#> Forward");
        move_forward();
        break;
      }

      // Move backward
    case down_arrow:
      {
        Serial.println("#> Backward");
        move_backward();
        break;
      }

      // Turn left
    case left_arrow:
      {
        Serial.println("#> Left");
        turn_left();
        break;
      }

      // Turn right
    case right_arrow:
      {
        Serial.println("#> Right");
        turn_right();
        break;
      }

      // Break
    case space_key:
      {
        Serial.println("#> Stop");
        stop();
        break;
      }

    case minus_key:
      {
        speed_down();
        break;
      }

    case plus_key:
      {
        speed_up();
        break;
      }

    case s_key:
      {
        // Debug
        debug_motors();
      }

    default:
      {
      }
    }

    // Determine key codes
    //Serial.print("#> ");
    //Serial.println(serial_command , DEC);
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


