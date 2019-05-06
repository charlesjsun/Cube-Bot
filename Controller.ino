#include <ServoTimer2.h>

// ///////////////////////////////
// Encoder Variables and Constants
// ///////////////////////////////

#define pinEncoderA 3
#define pinEncoderB 4

#define portEncoderA PIND3
#define portEncoderB PIND4

//volatile unsigned long encoderTimePrev = 0;  // us
//volatile unsigned long encoderTimeCurr = 0;   // us

#define numCounts 4
volatile int encoderCounts[numCounts];
volatile float encoderWeights[numCounts];

volatile float wheelRPMPrev = 0; // rpm
volatile float wheelRPMRaw = 0; // rpm
volatile float wheelRPM = 0;    // rpm

#define encoderSpeedFilter 0.6 // percentage of the previous rpm to keep each update step
#define encoderCPR 22

//#define GR 1

// /////////////////////////////
// Motor Variables and Constants
// /////////////////////////////

#define pinMotorEnable 5
#define pinMotorDir1 12
#define pinMotorDir2 13

// ///////////////////////////
// Servo and Braking Variables
// ///////////////////////////

#define RPM_TO_BRAKE_FORWARD 2000
#define RPM_TO_BRAKE_BACKWARD 1500
#define servoRestPos 750
#define servoBrakePos 2250

#define pinBrakeServo 2
ServoTimer2 brakeServo;

// /////////////////////////////
// State Variables and Constants
// /////////////////////////////

#define STATE_IDLE '0'
#define STATE_CHARGING '1'
#define STATE_BALANCING '2'
#define STATE_RISING '3'
#define STATE_FLIP_FORWARD '4'
#define STATE_FLIP_BACKWARD '5'
#define STATE_BRAKING '6'
#define STATE_POTENTIOMETER '7'

volatile unsigned long prevMicros;
volatile unsigned long currMicros;
volatile char state = STATE_IDLE;
