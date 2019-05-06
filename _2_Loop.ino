
void loop() {
  //  calculateRPM();
  //  noInterrupts();
  //  Serial.println(wheelRPM);
  //  interrupts();
  //  delay(50);

  if (Serial.available() > 0) {
    char newState = Serial.read();
    if (newState != '\n') {
      state = newState;
      Serial.print("State: ");
      Serial.println(state);
    }
  }
  
  switch (state) {

    case STATE_BALANCING:
      //idk lol
      Serial.println("balancing");
      break;
    
    case STATE_RISING:
      // Do something here, like delay
//      delay(500);
//      state = STATE_BALANCING;
      Serial.println("rising");
      break;
    
    case STATE_CHARGING:
      Serial.println("charging");
      break;

    case STATE_BRAKING:
      analogWrite(pinMotorEnable, 0);
      digitalWrite(pinMotorDir1, LOW);
      digitalWrite(pinMotorDir2, LOW);
      brakeServo.write(servoBrakePos);
      Serial.println("braking");
      break;

    case STATE_IDLE:
      // Set motor to 0
      analogWrite(pinMotorEnable, 0);
      digitalWrite(pinMotorDir1, LOW);
      digitalWrite(pinMotorDir2, LOW);
      brakeServo.write(servoRestPos);
      Serial.println("idling");
      break;

    case STATE_FLIP_FORWARD:
      if (abs(wheelRPM) < RPM_TO_BRAKE_FORWARD) {
        digitalWrite(pinMotorDir1, LOW);
        digitalWrite(pinMotorDir2, HIGH);
        analogWrite(pinMotorEnable, 255);
      } else {
        state = STATE_BRAKING;
      }
      Serial.println(wheelRPM);
      break;

    case STATE_FLIP_BACKWARD:
      if (abs(wheelRPM) < RPM_TO_BRAKE_BACKWARD) {
        digitalWrite(pinMotorDir1, HIGH);
        digitalWrite(pinMotorDir2, LOW);
        analogWrite(pinMotorEnable, 255);
      } else {
        state = STATE_BRAKING;
      }
      Serial.println(wheelRPM);
      break;

    case STATE_POTENTIOMETER:
      int potValue = analogRead(A0); // Read potentiometer value
      int pwmOutput = map(potValue, 0, 1023, -255 , 255); // Map the potentiometer value from 0 to 255
    
      if (pwmOutput < 0) {
        digitalWrite(pinMotorDir1, LOW);
        digitalWrite(pinMotorDir2, HIGH);
      } else {
        digitalWrite(pinMotorDir1, HIGH);
        digitalWrite(pinMotorDir2, LOW);
      }
      Serial.print(wheelRPM);
      Serial.print(" ");
      Serial.print(pwmOutput);
      Serial.println();
      analogWrite(pinMotorEnable, abs(pwmOutput)); // Send PWM signal to L298N Enable pin
//      Serial.println("flip charging");
      break;
    
    
      
    default:
      // Set motor to 0
      analogWrite(pinMotorEnable, 0);
      digitalWrite(pinMotorDir1, LOW);
      digitalWrite(pinMotorDir2, LOW);
      brakeServo.write(servoRestPos);
      Serial.println("idling");
      break;
  }
//  Serial.println("loop");
  delay(50);
}

//
// Main state update loop using a 20 Hz interrupt 50 ms delta time
//
ISR(TIMER1_OVF_vect) {
  
  prevMicros = currMicros;
  currMicros = micros();

//  Serial.print("Update Delta: ");
//  Serial.println(currMicros - prevMicros);

  getWheelRPM();
  getIMUValues();

//  if (state == STATE_BALANCING) {
//    // balance calculations
//  
//  } else if (state == STATE_CHARGING) {
//
//    if (wheelRPM > RPM_TO_BRAKE) {
//      // Set rpm to 0
//      // brake
//      state = STATE_RISING;
//    }
//    
//  } else if (state == STATE_IDLE) {
//    // idle
//  
//  }

  TCNT1 = 53150;
}
