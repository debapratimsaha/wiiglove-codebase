// two variables for each input pin to read and store the values 
  int inPin3 = 3;          //mic in

  int micIn;

void setup() {   

// declaration of pins modes    
  pinMode(inPin3, INPUT);
  
// set up the mean position
  micIn = analogRead(inPin3);

// begin sending over serial port
   Serial.begin(9600);
}

void loop() 
{
  int i,val_read[4][2],relative_movement[4],abs_movement[4];
  
// read the values of the analog pins and store them in variables
  val_read[0][0] = analogRead(inPin0);
  val_read[1][0] = analogRead(inPin1);
  val_read[2][0] = analogRead(inPin2);
  val_read[3][0] = analogRead(inPin3);

// read the 2nd set of values of the analog pins and store them in variables
  val_read[0][1] = analogRead(inPin0);
  val_read[1][1] = analogRead(inPin1);
  val_read[2][1] = analogRead(inPin2);
  val_read[3][1] = analogRead(inPin3);

  for(i=0;i<4;i++)
    relative_movement[i] = val_read[i][1]-val_read[i][0];
    
  for(i=0;i<4;i++)
    abs_movement[i] = val_read[i][1] - meanPos[i];
    
// print out the variables preceeded by their IDs and followed by a carriage return 
   if (abs(relative_movement[0]) > 2  || abs(abs_movement[0])>20)
      { Serial.write(id_1); Serial.write(constrain(abs_movement[0],0,255)/*map(abs_movement[0],1900,2300,0,255)*/);  Serial.write(10);}
 
   if (abs(relative_movement[1]) > 2  || abs(abs_movement[1])>20)   
      { Serial.write(id_2); Serial.write(constrain(abs_movement[1],0,255)/*map(abs_movement[1],1900,2300,0,255)*/);  Serial.write(10);}
      
   if (abs(relative_movement[2]) > 2  || abs(abs_movement[2])>20)      
      { Serial.write(id_3); Serial.write(constrain(abs_movement[2],0,255)/*map(abs_movement[2],1900,2300,0,255)*/);  Serial.write(10);}
        
   if (abs(relative_movement[3]) > 2  || abs(abs_movement[3])>20)
      { Serial.write(id_4); Serial.write(constrain(abs_movement[3],0,255)/*map(abs_movement[3],1900,2300,0,255)*/);  Serial.write(10);}
}

