#include "pinList.h"

int degreesToHeaterLevel(int degreeDelta) {
  // I'm off by 10 degrees, what difference do I apply to the heater?
  if (degreeDelta < 5) return 2;
  if (degreeDelta < 10) return 10;
  throw;
}

bool isSafeHeaterLevel(int heaterLevel) {
  const int MINLEVEL = 64;
  const int MAXLEVEL = 192;
  return (MINLEVEL <= heaterLevel) && (MAXLEVEL >= heaterLevel);
}

void heatManagement() {
  const int MIDLEVEL = 128;
  const int NONFATALLEVEL = MIDLEVEL;

  const int OutPin = HEATRELAY1PIN;
  const int delta = (int) (targetTemp - actualTemp); 
  int heaterLevel[] = {64, 32, 16, 8, 0};
  int heaterLevelNegative[] = {186, 223, 239, 247, 255};

  int localTargetTemp = targetTemp;
  
  if (nightDrop == HIGH) {
    localTargetTemp -= - nightDrop;
  }

  const int currentHeaterLevel = getCurrentHeaterLevel();
  const int desiredHeaterLevel = currentHeaterLevel - degreesToHeaterLevel(delta);

  if (isSafeHeaterLevel(desiredHeaterLevel)) {
    analogWrite(outPin, desiredHeaterLevel);
  }
  else {
    analogWrite(outPin, NONFATALLEVEL);
  }
};

