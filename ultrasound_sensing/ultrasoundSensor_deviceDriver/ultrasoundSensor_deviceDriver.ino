int strobe =  11;
int brd_1  =  1;
int brd_2  =  2;

void setup(){
  pinMode(strobe, OUTPUT);
  pinMode(brd_1, INPUT);
  pinMode(brd_2, INPUT);
  
  delay(175);
}

void loop(){
  digitalWrite(strobe,HIGH);
  delay(99);
  digitalWrite(strobe,LOW);
  
  delay(21);
  
}


