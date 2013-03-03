int outPin = 13;
int inPin = 3;  

int meanPos;
int id_1 = 'A'; 

void setup ()
{
  pinMode(outPin,OUTPUT);
  pinMode(inPin,INPUT);
  delay (50); 
  meanPos= analogRead(inPin);
  
  Serial.begin(9600);
}


void loop()
{
  int val_read[2],relative_movement,abs_movement;
  
  val_read[0] = analogRead(inPin);
  delay (50);
  val_read[1] = analogRead(inPin);

  relative_movement = val_read[1]-val_read[0];

  abs_movement = val_read[1] - meanPos;

  if (abs(relative_movement) > 2  || abs(abs_movement)>20){
    //Serial.println("Reached \n");
    Serial.write(id_1); 
    //Serial.write(map(abs_movement,1900,2300,0,255));  
    //Serial.println(map(abs_movement,1900,2300,0,255));
    Serial.write(constrain(abs_movement,0,255));  
    Serial.write(10);
    //digitalWrite(outPin,HIGH);
  }

}

