/*
  Created by SENSORVN.COM, February 25, 2021.
  Wiring
  VCC -> 3.3V
  GND -> GND
  DV  -> GPIO5
  OUT1(D0) -> GPIO12
  OUT7(RST)-> GPIO14
  OUT8(CK) -> GPIO4
*/
const int DV = 5; 
const int D0 = 12; //OUT1
const int RST = 14;//OUT7
const int CK = 4;  //OUT8
byte data_ = 0;
byte data = 0;
byte flag = 0;
void ICACHE_RAM_ATTR handleInterrupt();
void ICACHE_RAM_ATTR handleInterruptData();

/* Function */
void resetSensor()
{
  digitalWrite(RST,HIGH);
  delayMicroseconds(500);
  digitalWrite(RST,LOW);
  delayMicroseconds(500);
}

void work()
{
  if(flag == 1)
  {
    detachInterrupt(digitalPinToInterrupt(DV));
    resetSensor();
    attachInterrupt(digitalPinToInterrupt(D0), handleInterruptData, FALLING);
    for(byte i=1;i<9;i++)
    { 
      data_ = i;
      digitalWrite(CK,LOW);
      delay(1);
      digitalWrite(CK,HIGH);
      delay(1);
    }
    detachInterrupt(digitalPinToInterrupt(D0));
    attachInterrupt(digitalPinToInterrupt(DV), handleInterrupt, RISING);
    resetSensor();
    flag = 0;
  }
}

/* Arduino Function */
void setup() 
{ 
  Serial.begin(115200);
  pinMode(DV,INPUT); 
  pinMode(D0,INPUT); 
  pinMode(RST,OUTPUT); 
  pinMode(CK,OUTPUT); 
  attachInterrupt(digitalPinToInterrupt(DV), handleInterrupt, RISING);
  resetSensor();
  Serial.println("Start.....");
} 

void loop() 
{ 
  work();
} 

void ICACHE_RAM_ATTR handleInterrupt() 
{ 
  flag = 1;
}

void ICACHE_RAM_ATTR handleInterruptData() 
{ 
  data = data_;
  Serial.println(data);
}
