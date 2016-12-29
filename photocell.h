int photocellReading;
int photocellValue;

void readGroLightSensor() {
  photocellReading = pinExtender.digitalRead(LIGHTSENSORPIN);  
  //Serial.print("Photocell reading = ");
 // Serial.println(photocellReading);
  photocellValue = photocellReading;
  if (photocellValue == 1){//(inRange(photocellReading, 0, 100)){// && (nighttime = HIGH) && (daytime = LOW)) {
    pinExtender.digitalWrite(UVRELAY2PIN, HIGH);
    Blynk.virtualWrite(uvLed, HIGH); 
  }
  else {
    pinExtender.digitalWrite(UVRELAY2PIN, LOW);
    Blynk.virtualWrite(uvLed, LOW);     
  }
};
