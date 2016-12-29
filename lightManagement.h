#include <algorithm>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>

class TimeBasedNoise {
  private:
    double series[256];
    long timeStep;
  public:
    TimeBasedNoise( long newTimeStep );
    double getAtTime( long time );
};

TimeBasedNoise::TimeBasedNoise( long newTimeStep ){
  this->timeStep = newTimeStep;
  for ( int i=0;i<256;i++){
    this->series[i] = (rand() % 10000 )/5000.0 -1.0;
  }
  for ( int i=0;i<256;i++){
    double a = this->series[i] + this->series[i] + this->series[(i+255)%256] + this->series[(i+1)%256];
    this->series[i] = a * 0.25;
  }
};

double TimeBasedNoise::getAtTime( long time ){
  long steps = time % (timeStep*256);
  int index  = steps / timeStep;
  double offset = (double)(steps % timeStep)/timeStep;
  double startValue = this->series[index];
  double endValue = this->series[(index + 1) % 256];
  double difference = (endValue-startValue)*offset;
  return startValue + difference;
};

class SineBasedNoise {
  private:
    long timeStep;
    long endpoint;
    long dawn;
  public:
    SineBasedNoise(long newTimeStep, long endpoint  );
    double getAtTime( long time );
};

SineBasedNoise::SineBasedNoise( long newTimeStep, long endpoint ){
  this->timeStep = newTimeStep;
  this->endpoint = endpoint; 
};

double SineBasedNoise::getAtTime( long time ){
  long timeDelta = time - this->endpoint;
  double radians = ((double)timeDelta/(double)timeStep)*6.28;
  return sin(radians);
};

//gap between data points & inverse speed of change - ideally prime numbers, and non dividers
TimeBasedNoise redSeasonal( 104709 );  //what was this again?
TimeBasedNoise redRapid(93787); //cloud cover, repeat every 26 hours ish (nearest prime number)
SineBasedNoise overallSeasonal(31557600, 11834100); //specify y-intercept yearly, y intercept half way through spring
SineBasedNoise moonlightCycle(2544476,1240919); // one lunar month cycle, y-intercept at half moon offset by unix-time stamp defecit
SineBasedNoise dayNightCycle(86164, dawnVPin); // 1 earth rotation - y-intercept = dawn from app
SineBasedNoise moonOrbitCycle(2332800, 874800); //orbit length, y-intercept = 3/8ths in - changing depending on moonrise time?

double getMoonBrightness( long t ){  //if the moon is in the sky add its brightness
  if ( moonOrbitCycle.getAtTime(t) > 0 ){
    return moonlightCycle.getAtTime(t);
  }else{
    return 0.0;
  }
}

double max(double a,double b){
  if ( a > b ) return a;
  return b;
}

double min(double a,double b){
  if ( a < b ) return a;
  return b;
}

double getSkylightBrightness( long t ){
  return min( 1.0 , max( 0.01 /*stars*/ , 
             std::max( (dayNightCycle.getAtTime(t) * 1.4 ), (getMoonBrightness(t) * 0.2) /* full moon power */ ) ) );
}

double getDayStarPower( long t ){
  return overallSeasonal.getAtTime(t)*0.5 + redSeasonal.getAtTime(t)*0.4 + redRapid.getAtTime(t)*0.1;
}

double getOverallBrightnessAtTime( long t ){
  return getSkylightBrightness( t ) * ( 0.8 + getDayStarPower(t)*0.2 );
};
             
double sunsetFactor( long t ){
  double dayBright = dayNightCycle.getAtTime(t);
  if ( abs(dayBright) < 0.1 ){
    return 0.1 - abs(dayBright);
  }else{
    return 0.0;
  }
}
             
double getRedBrightnessAtTime( long t ){ //to include sunrise/sunset red spike
  return min(1.0,max(0.0,getOverallBrightnessAtTime(t) * 0.9 + redRapid.getAtTime(t)*0.1 + sunsetFactor(t)));
};

long getTime (){
  return 1000 /*demo mode*/ *(((year()-1970)*31557600) + (month()*2629800) + (day()*86164) + (hour()*3600) + (minute()*60) + second());
  // TODO: Do this properly and not like a muppet, months are differnt lengths.
}  
             
void setLightLevels(){
  long nowSeconds = getTime();
  Serial.printf("lights: %i %i %i\n", nowSeconds, (int)(100*getRedBrightnessAtTime(nowSeconds)), (int)(100*getOverallBrightnessAtTime(nowSeconds)));  
  digitalWrite (LED1PIN, getRedBrightnessAtTime(nowSeconds));
  digitalWrite (LED2PIN, getOverallBrightnessAtTime(nowSeconds));
  digitalWrite (LED3PIN, getOverallBrightnessAtTime(nowSeconds));  
};
