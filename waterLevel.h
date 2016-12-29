void pollWaterLevelSensor () {
  int level = pinExtender.digitalRead(WATERLEVEL1PIN);
  if (level == 1) {
    Blynk.virtualWrite(V10, "High");
  }
  else if (level == 0) {
    Blynk.virtualWrite(V10, "Low");
  }
  else {
    Serial.print("Error reading Water level");
  }
  Serial.printf("Water Level %i", level);
  Serial.printf("\n");
  digitalWrite (SOIL1POWER, LOW);
};

void readWaterLevelSensor () {
    digitalWrite (SOIL1POWER, HIGH);
 int timerId = timer.setTimeout(100L, pollWaterLevelSensor);
}

