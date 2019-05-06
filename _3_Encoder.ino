
void getWheelRPM() {
  wheelRPMPrev = wheelRPM;

  float averageCounts = 0;
  for (int i = 0; i < numCounts; ++i) {
    averageCounts += encoderCounts[i] * encoderWeights[i];
  }

  wheelRPMRaw = averageCounts / (float) (currMicros - prevMicros) * 1000000.0 / encoderCPR * 60; // / GR;
  wheelRPM = (1 - encoderSpeedFilter) * wheelRPMRaw + encoderSpeedFilter * wheelRPMPrev;

  // Shift encoder values back;
  for (int i = numCounts - 1; i > 0; --i) {
    encoderCounts[i] = encoderCounts[i - 1];
  }
  encoderCounts[0] = 0;
}

void encoder_ISR() {
  if ((PIND & (1 << portEncoderA)) >> portEncoderA == (PIND & (1 << portEncoderB)) >> portEncoderB) {
    encoderCounts[0]++;
  } else {
    encoderCounts[0]--;
  }
}
