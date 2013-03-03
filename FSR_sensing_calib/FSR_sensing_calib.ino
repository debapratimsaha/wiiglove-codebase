int outPin = 13;
int inPin = 3;
int calib_val = 0;

int calibrate_sensor(void);

void setup ()
{
  Serial.begin(9600);
  calib_val=calibrate_sensor();
  
  pinMode(outPin,OUTPUT);
  pinMode(inPin,INPUT);
  
  Serial.println("Going out of setup");
}

int counter=0;
void loop()
{
  long unsigned int val_read;
  double val;
  
  val_read = analogRead(inPin);
  val = val_read*1023/calib_val;  //check this signal processing

  if (int(val)>400){
    digitalWrite(outPin,HIGH);
  }else{
    digitalWrite(outPin,LOW);   
  } 

  if (counter==10){
  Serial.println(int(val));
  counter = 0;
  }
  counter = counter+1;
}

int calibrate_sensor()
{
  int val[2]={0},cal=0;
  Serial.println("Press the sensor 2 times when prompted\n"); 
  Serial.println("Press#1\n");
  while (val[0]<20){
    val[0]=analogRead(inPin);
    delay (100);
  }
  while (analogRead(inPin)>20){}
  
  Serial.println(val[0]);
 
  Serial.println("Press#2\n");
  while (val[1]<20){
    val[1]=analogRead(inPin);
    delay (100);
  }
  while (analogRead(inPin)>20){}
  
  Serial.println(val[1]);
  cal = (val[0]+val[1])/2;
  
  Serial.println("Calibration Done, \n"); 
  Serial.println(cal);
  Serial.println("Touch again to proceed\n");
  while (analogRead(inPin)<20){}
  
  return (cal);
}

