#include "blynk.h"
#include "rtc.h"
#include "pinList.h"
#include "inRange.h"
#include "humidityControl.h"
#include "DHTSensorRead.h"
#include "photocell.h"
#include "soilMoisture.h"
#include "waterLevel.h"
#include "dayNightManagement.h"
#include "lightManagement.h"
#include "heatManagement.h"

Adafruit_MCP23017 pinExtender;

void setup() {

  wifiServerConnect();

  pinExtenderSetup();

  pinExtender.digitalWrite(powerLED, HIGH); //Turn on LED Power light

  rtc.begin();

  dht1.begin();
  dht2.begin();
  dht3.begin();

  pinMode (D0, OUTPUT);

  timer.setInterval(1000L, clockDisplay); //check every 1s what the time is
  timer.setInterval(2000L, fanManagement); //manage fans every 2 seconds
  timer.setInterval(2000L, readDhtSensors); //read sensor every 4 seconds
  timer.setInterval(2000L, readGroLightSensor); //check to turn on gro lights every 2 seconds
  timer.setInterval(6000L, readSoilMoistureSensor); //check soil humidity every 24 seconds
  timer.setInterval(1000L, readWaterLevelSensor); //check water level every 100ms.
  timer.setInterval(5000L,  setLightLevels); //update light settings every five seconds
  timer.setInterval(300L,   heatManagement); // write the heater change level every 300 ms
}

void loop() {
  if(Connected){
    Blynk.run();
  }
  
  timer.run();
}
