// Arduino PINS definition file 
// Leandro Sehnem Heck


// DC Motors using H-Bridge (3 pins each)
// Specs: http://www.ebay.com/itm/L298N-Dual-H-Bridge-DC-stepper-Motor-Driver-Controller-module-Board-for-Arduino-/201037238860
//--------------------------------------------------------------------

// MOTOR 1
#define M1_ENABLE_PIN  5
#define M1_TERM_A_PIN 11
#define M1_TERM_B_PIN 12

// MOTOR 2
#define M2_ENABLE_PIN  6
#define M2_TERM_A_PIN 10
#define M2_TERM_B_PIN  8


// Ultrasonic HC-SR04 sensor (2 pins each)
// Specs: http://users.ece.utexas.edu/~valvano/Datasheets/HCSR04b.pdf
//--------------------------------------------------------------------

// ULTRASONIC 1
#define US1_TRIG -1
#define US1_ECHO -1

// ULTRASONIC 2
#define US2_TRIG -1
#define US2_ECHO -1

// ULTRASONIC 3
#define US3_TRIG -1
#define US3_ECHO -1


// Speed measuring module HC-020K
// Specs: http://www.ebay.com/itm/HC-020K-Double-Speed-Measuring-Sensor-Module-with-Photoelectric-Encoders-Kit-/350851366249
//--------------------------------------------------------------------

// ENCODER MOTOR 1
#define SPEED_MESURE_M1 -1

// ENCODER MOTOR 2
#define SPEED_MESURE_M2 -1
