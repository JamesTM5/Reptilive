#ifndef PINLIST_H
#define PINLIST_H
#include <Wire.h>
#include "Adafruit_MCP23017.h"

extern Adafruit_MCP23017 pinExtender;

//V1 = currentTime
//V2 = currentDate

#define powerLED 15

#define fan1 1
#define fan2 2
int fanLed1 = V40;
int fanLed2 = V41;

const int actualBaskingHumidity = V4;
const int targetBaskingHumidity = V16;

#define DHT1PIN D3
#define DHT2PIN D4
#define DHT3PIN D5
#define LED1PIN D6
#define LED2PIN D7
#define LED3PIN D8

#define UVRELAY2PIN 8
#define LIGHTSENSORPIN 2
int uvLed = V42;

#define SOIL1PIN 3
#define SOIL1POWER D0

#define WATERLEVEL1PIN 4

int dawnVPin = V81;

#define HEATRELAY1PIN 15 // TODO give actual value
int actualTemp = V3;
int targetTemp = V15;
int nightDrop = V13;

void pinExtenderSetup() {
  pinExtender.begin();
  pinExtender.pinMode (0, OUTPUT); //Fan1
  pinExtender.pinMode (1, OUTPUT); //Fan2
  pinExtender.pinMode (2, INPUT); //Photocell
//  pinExtender.pinMode (3, INPUT); //Soil Moisture Sensor
//  pinExtender.pinMode (4, OUTPUT); //Water Level Sensor
//  pinExtender.pinMode (5, OUTPUT);
//  pinExtender.pinMode (6, OUTPUT);
//  pinExtender.pinMode (7, OUTPUT);
//  pinExtender.pinMode (8, OUTPUT);
//  pinExtender.pinMode (9, OUTPUT);
//  pinExtender.pinMode (10, OUTPUT);
//  pinExtender.pinMode (11, OUTPUT);
//  pinExtender.pinMode (12, OUTPUT);
//  pinExtender.pinMode (13, OUTPUT);
//  pinExtender.pinMode (14, INPUT);
  pinExtender.pinMode (15, OUTPUT); //Power LED
}

#endif // PINLIST_H
