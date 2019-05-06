
void setup() {

  Serial.begin(9600);
  
  brakeServo.attach(pinBrakeServo);
  brakeServo.write(servoRestPos);

  pinMode(pinEncoderA, INPUT);
  pinMode(pinEncoderB, INPUT);

  // Setup 50Hz main loop
  noInterrupts();
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1 = 53036; // 50 ms, 20 Hz
  TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler 64
  TIMSK1 |= (1 << TOIE1); // Enable Timer1 Overflow interrupt
  interrupts();

  attachInterrupt(digitalPinToInterrupt(pinEncoderA), encoder_ISR, CHANGE);

  for (int i = 0; i < numCounts; ++i) {
    encoderCounts[i] = 0;
    //    encoderWeights[numCounts - 1 - i] = pow(0.5, i + 1);
    encoderWeights[i] = 1.0 / numCounts;
  }
  //  encoderWeights[numCounts - 1 - (numCounts - 1)] *= 2.0;


  pinMode(pinMotorEnable, OUTPUT);
  pinMode(pinMotorDir1, OUTPUT);
  pinMode(pinMotorDir2, OUTPUT);

  digitalWrite(pinMotorDir1, HIGH);
  digitalWrite(pinMotorDir2, LOW);

  prevMicros = micros();
  currMicros = micros();

}
