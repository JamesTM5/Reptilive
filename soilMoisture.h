void pollSoilSensor () {
  int soilSignalState;
  int soilMoistureValue;
  soilSignalState = pinExtender.digitalRead(SOIL1PIN);
  soilMoistureValue = soilSignalState;
  if (soilSignalState = 1) {
    Blynk.virtualWrite(V9, "High");
  }
  else {
    Blynk.virtualWrite(V9, "Low");
  }
//  Serial.print ("Soil Moisture Value = ");
 // Serial.print(soilMoistureValue);
//  Serial.print("\n");
  digitalWrite (SOIL1POWER, LOW);
}

void readSoilMoistureSensor () {
  digitalWrite (SOIL1POWER, HIGH);
 int timerId = timer.setTimeout(100L, pollSoilSensor);
}
