
void fanManagement()
{
  if(actualBaskingHumidity >= (targetBaskingHumidity + 10)) 
    {
      pinExtender.digitalWrite(fan1, HIGH);
      pinExtender.digitalWrite(fan2, HIGH);
      Blynk.virtualWrite(fanLed1, HIGH);
      Blynk.virtualWrite(fanLed2, HIGH);   
 //     Serial.printf("Both Fans on to bring down humidity\n");  
    }
 else if(inRange(actualBaskingHumidity, (targetBaskingHumidity + 5), (targetBaskingHumidity - 5))) 
    {
      pinExtender.digitalWrite(fan1, HIGH);
      pinExtender.digitalWrite(fan2, LOW);
      Blynk.virtualWrite(fanLed1, HIGH);
      Blynk.virtualWrite(fanLed2, LOW);   
//      Serial.printf("One Fan on to bring down humidity\n");  
    }
 else if (actualBaskingHumidity <= (targetBaskingHumidity - 5))
    { 
      pinExtender.digitalWrite(fan1, LOW);
      pinExtender.digitalWrite(fan2, LOW);
      Blynk.virtualWrite(fanLed1, LOW);
      Blynk.virtualWrite(fanLed2, LOW);   
 //     Serial.printf("Both Fans off to bring up humidity\n");  
    }
 else
 {
  //make no change
 //     Serial.print("No change in fan state");  
 }
}
