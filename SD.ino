
int sparkpin = D5;
int rpmpin = D6;


  volatile unsigned long TimeStamp = 0;
  volatile unsigned long time1 = 0;
  volatile unsigned long time2 = 0;
  volatile unsigned long Oldtime1 = 0;
  volatile unsigned long Oldtime2 = 0;
  volatile unsigned long TempTime1 = 0;
  volatile unsigned long TempTime2 = 0;
  String AllResult = "";

void setup() {

  pinMode(rpmpin,INPUT);
  pinMode(sparkpin,INPUT);

  Serial.begin(115200);
  
  attachInterrupt(digitalPinToInterrupt(rpmpin), channel1, RISING); 
  attachInterrupt(digitalPinToInterrupt(sparkpin), channel2, RISING);
}

void loop() {
  AllResult = "";
  AllResult += micros();
  AllResult += ",";
  AllResult += TempTime1;
  AllResult += ",";
  AllResult += time1;
  AllResult += ",";
  AllResult += TempTime2;
  AllResult += ",";
  AllResult += time2;
  AllResult += ",0,0,0,0,0,0";    // Not sure if SimpleDyno is waiting for something to be returned, so adding it just in case.

  Serial.println (AllResult);
  Serial.flush();
  delay(1);
}

//Interrupt routine for RPM1 - Roller
ICACHE_RAM_ATTR void channel1()
{
  TempTime1 = micros();
  time1 = TempTime1-Oldtime1;
  Oldtime1 = TempTime1;
}

//Interrupt routine for RPM2 - Engine
ICACHE_RAM_ATTR void channel2()
{
if ((micros()-TempTime2)>4000)   //debounce signal. Take MAX RPM of engine and calculate time in micro seconds for full revolution: 
 {                              //   60 000 000/max_RPM  ->  60 000 000 / 15 000  = 4000
  TempTime2 = micros();
  time2 = TempTime2-Oldtime2;
  Oldtime2 = TempTime2;
  }
}
                        
