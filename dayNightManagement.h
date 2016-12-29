char Date[16];
char Time[16];


void activetoday(){        // check if day schedule should run today and trigger it
  if(year() != 1970){
    Blynk.syncVirtual(V17); // sync timeinput widget    
  }
}

BLYNK_WRITE(V20) {
  sprintf(Date, "%02d/%02d/%04d",  day(), month(), year());
  sprintf(Time, "%02d:%02d:%02d", hour(), minute(), second());

  TimeInputParam t(param);
    if (t.hasStartTime()) // Process start time
    {
      Serial.println(String("Start: ") + t.getStartHour() + ":" + t.getStartMinute());
      long startseconds = ((t.getStartHour() * 3600) + (t.getStartMinute() * 60));
      long dawn = startseconds;
      Blynk.virtualWrite (dawnVPin, dawn);
    }
};
