//code help : http://www.arduino.cc/playground/Code/PIRsense

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime; 

int pirPin = 2;       //digital 2
int controlLED = 3;   //digital 3
int controlLED2 = 13;   //digital 3

void setup(){
 Serial.begin(9600);
 pinMode(pirPin, INPUT);
 pinMode(controlLED,OUTPUT);
 pinMode(controlLED2,OUTPUT);
 
 digitalWrite(pirPin, LOW);
 
 //calibrating sensor
 Serial.print("calibrating sensor ");
 for(int i = 0; i < calibrationTime; i++){
   Serial.print(".");
   delay(1000);
   }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}

void loop(){

  if(digitalRead(pirPin)==LOW){ //was motion detected
    //Serial.println("Motion Detected");
    delay(500);
    if(digitalRead(pirPin)==LOW){
      digitalWrite(controlLED,HIGH);
      digitalWrite(controlLED2,HIGH);
      Serial.write('P');
    }
  }else{
    digitalWrite(controlLED,LOW);
    digitalWrite(controlLED2,LOW);
    Serial.write('S');
    delay(500);
  }
  
  delay(50);

}

