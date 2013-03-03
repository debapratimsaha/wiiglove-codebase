int outPin = 13;
int inPin = 3;

void setup ()
{
  Serial.begin(9600);
  pinMode(outPin,OUTPUT);
  pinMode(inPin,INPUT);
}

void loop()
{
  long unsigned int val_read;
  double val;
  
  val = analogRead(inPin);

  if (int(val)>200){
    digitalWrite(outPin,HIGH);
  }else{
    digitalWrite(outPin,LOW);  
  } 

  Serial.println(int(val));
//  delay (1000);
}
