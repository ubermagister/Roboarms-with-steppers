
#include <Preferences.h>
#include <FastAccelStepper.h>
#include "Stepper.h"
#include "kiihdyttaja.h"
#include <string>
using namespace std;



//esp pinnit, muutettavissa vaihtamalla pin numerot
#define DIR 4   // gpio0 dir
#define STEP 5  // gpio1 step
#define MS1 6  // gpio2 ms1
#define MS2 7   // gpio3 ms2

#define M2DIR 0  // gpio1 step
#define M2STEP 1  // gpio2 ms1
#define M2S1 2  // gpio3 ms2
#define M2S2 3   // gpio2 ms1


Preferences p;
Preferences q;
bool turn1=false;
bool turn2=false;
unsigned long previousMillis = 0; 
unsigned long currentMillis = millis(); 
unsigned long nolla=0;




void index1(bool x){
  unsigned count1=p.getUInt("counter", 0);
  Serial.printf("received index1; %u\n",count1);
  if(count1>1559){
  count1=count1 % 1600;
  }
  if(x){


    if (count1==0){
    count1=1599;
      }else{
        count1--;
            }
      }else{
        if (count1==1599){
          count1=0;
        }else{
          count1++;
        }
      }
      Serial.printf("sent index1; %u\n",count1);
p.putUInt("counter",count1);
}

void index2(bool x){
  unsigned count2=q.getUInt("counter", 0);
    Serial.printf("received index2; %u\n",count2);
    if(count2>1559){
  count2=count2 % 1600;
  }
  if(x){
    if (count2==0){
    count2=1599;
      }else{
        count2--;
            }
      }else{
        if (count2==1599){
          count2=0;
        }else{
          count2++;
        }
      }
      Serial.printf("sent index2; %u\n",count2);
q.putUInt("counter",count2);
}


void setup() {
    Serial.begin(115200);
    while (!Serial);

  p.begin("test-1", false);
  q.begin("test-2", false);

  unsigned int counter1 = p.getUInt("counter", 0);
  unsigned int counter2 = q.getUInt("counter", 0);



    pinMode(DIR, OUTPUT);
    pinMode(STEP, OUTPUT);
    pinMode(MS1, OUTPUT);
    pinMode(MS2, OUTPUT);

    pinMode(M2DIR, OUTPUT);
    pinMode(M2STEP, OUTPUT);
    pinMode(M2S1, OUTPUT);
    pinMode(M2S2, OUTPUT);   
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(MS1, LOW);
    digitalWrite(MS2, LOW);
    digitalWrite(M2S1, LOW);
    digitalWrite(M2S2, LOW);


Serial.printf("end of startup\n available commands: zero, scan <tilt> <pan> <interval in milliseconds>, shutdown");

}

void Startup(unsigned int c1,unsigned int c2){
if (c1>0){
  turn1=!turn1;
  digitalWrite(DIR,turn1);
  for(int u=0;u<c1;u++){
    digitalWrite(STEP,HIGH);
    delayMicroseconds(100);
    digitalWrite(STEP,LOW);
    delayMicroseconds(100);  
        }
turn1=!turn1;
digitalWrite(DIR,turn1);

}else{
  Serial.printf("Motor1 already zeroed");
  delay(1000);
  }
c1=0;
p.putUInt("counter", c1);
Serial.printf("Motor1 zeroed, Please wait");
delay(1000);

if (c2>0){
turn2=!turn2;
digitalWrite(M2DIR,turn2);
for(int y=0;y<c2;y++){
  digitalWrite(M2STEP,HIGH);
  delayMicroseconds(100);
  digitalWrite(M2STEP,LOW);
  delayMicroseconds(100);  
}
turn2=!turn2;
digitalWrite(M2DIR,turn2);
}else{
 Serial.printf("Motor1 already zeroed");
 delay(1000); 
}
c2=0;
q.putUInt("counter", c2);
Serial.printf("Both motors zeroed, Finishing Setup");
delay(1000);
}



void loop() { 
   
if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n'); 

        if (command == "zero") {
            Stepper steppi; 
            steppi.Zero();
            Serial.printf("both motors at 0...");
        } else if (command.startsWith("scan")) {
            
            int anglex, angley, interval;
            sscanf(command.c_str(), "scan %d %d %d", &anglex, &angley, &interval);
            Stepper steppi;
            steppi.Scan(anglex, angley, interval);
            Serial.printf("Scanned with angles: %d, %d and interval: %d\n", anglex, angley, interval);
        }
        else if (command == "shutdown") {
            Stepper steppi;
            steppi.Shutdown();
            Serial.printf("Shutting down...");
        
        } else {
            Serial.printf("Unknown command. Available commands: zero, scan <angleX> <angleY> <interval>, shutdown");
        }
}
}