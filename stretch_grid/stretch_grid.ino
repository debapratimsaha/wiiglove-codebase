int outPin = 13;
int inPin0 = 0;        //Right
int inPin1 = 1;        //Down
int inPin2 = 2;        //Left
int inPin3 = 3;        //Up


int meanPos[4];

void setup ()
{
  pinMode(outPin,OUTPUT);
  pinMode(inPin0,INPUT);
  pinMode(inPin1,INPUT);
  pinMode(inPin2,INPUT);
  pinMode(inPin3,INPUT);
  
  meanPos[0]= analogRead(inPin0);
  meanPos[1]= analogRead(inPin1);
  meanPos[2]= analogRead(inPin2);
  meanPos[3]= analogRead(inPin3);

//  for(i=0;i<4;i++)
//    meanPos[i]= analogRead(inPin[i]);

  Serial.begin(9600);
}


void loop()
{
  int i,val_read[4][2],relative_movement[4],abs_movement[4];
  
  val_read[0][0] = analogRead(inPin0);
  val_read[1][0] = analogRead(inPin1);
  val_read[2][0] = analogRead(inPin2);
  val_read[3][0] = analogRead(inPin3);
//  for(i=0;i<4;i++)
//    val_read[i][0]= analogRead(inPin[i]);

//  delay (50);

  val_read[0][1] = analogRead(inPin0);
  val_read[1][1] = analogRead(inPin1);
  val_read[2][1] = analogRead(inPin2);
  val_read[3][1] = analogRead(inPin3);
//  for(i=0;i<4;i++)
//    val_read[i][1]= analogRead(inPin[i]);
      
//  relative_movement[0] = val_read[0][1]-val_read[0][0];
//  relative_movement[1] = val_read[1][1]-val_read[1][0];
//  relative_movement[2] = val_read[2][1]-val_read[2][0];
//  relative_movement[3] = val_read[3][1]-val_read[3][0];
  for(i=0;i<4;i++)
    relative_movement[i] = val_read[i][1]-val_read[i][0];
  
//  abs_movement[0] = val_read[0][1] - meanPos[0];
//  abs_movement[1] = val_read[1][1] - meanPos[1];
//  abs_movement[2] = val_read[2][1] - meanPos[2];
//  abs_movement[3] = val_read[3][1] - meanPos[3];
  for(i=0;i<4;i++)
    abs_movement[i] = val_read[i][1] - meanPos[i];

  if (abs(relative_movement[0]) > 2  || abs(abs_movement[0])>20)
    Serial.println("Reached Right\n");
  
  if (abs(relative_movement[1]) > 2  || abs(abs_movement[1])>20)
    Serial.println("Reached Down\n");
    
  if (abs(relative_movement[2]) > 2  || abs(abs_movement[2])>20)
    Serial.println("Reached Left\n");
  
  if (abs(relative_movement[3]) > 2  || abs(abs_movement[3])>20)
    Serial.println("Reached Up\n");
 
}

