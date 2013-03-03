int inPin0 = 3;          
int outPin = 13;

void setup() {   

// declaration of pins modes    
  pinMode(inPin0, INPUT);
  pinMode(outPin, OUTPUT);

// begin sending over serial port
   Serial.begin(9600);
}

void loop() 
{
  int val_read;
  
// read the values of the analog pins and store them in variables
  val_read = analogRead(inPin0);
    
// print out the variables preceeded by their IDs and followed by a carriage return 
   if (val_read > 400)
      digitalWrite(outPin,HIGH);
   else 
      digitalWrite(outPin,LOW);
 }

