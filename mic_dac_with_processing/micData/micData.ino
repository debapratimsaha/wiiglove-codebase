/*********************************************************************
This code sends analog data from Port0 on Arduino Unto the serial port 
along with a header = 'H'. Processing sketch is used to log the data to
user computer.
*********************************************************************/
#define arraySize 600
int micInAmp = 0;
const char HEADER = 'H'; 
int adcData [arraySize];

void setup (){
  Serial.begin(115200) ;
  pinMode(micInAmp,INPUT);
  adcINIT();
}

void loop(){
  
  for (int i=0;i<arraySize;i++){
    adcData[i] = analogRead(micInAmp);  
  }

  Serial.write(HEADER);                     // send the header
  
  for (int i=0;i<arraySize;i++){
    Serial.write(highByte(adcData[i])<<6 + lowByte(adcData[i])>>2);                     // send the actual data
    delayMicroseconds(10000);
  }  
}

void adcINIT()
{
  // initialize 
  // set first write
  PORTD &= B10000011;          // set 2-6 as low
  PORTD |= B10000000;          // D5 high

  PORTB = B00011100;           // set 8-9 pins low, and 10-12 high
  delay(10);

  // write
  PORTB &= B11101111;          // CS low,  WR high, RD high
  PORTB &= B11100111;          // CS low,  WR low,  RD high
  PORTB |= B00001100;          // CS low,  WR high, RD high
  PORTB |= B00011100;          // CS high, WR high, RD high
  delay(10);

  // set second write
  PORTB |= B00000001;          // A0 high
  PORTD &= B00000011;          // set 2-7 as low
  PORTD |= B01000000;          // D4 high;
  delay(10);

  // write
  PORTB &= B11101111;          // CS low,  WR high, RD high
  PORTB &= B11100111;          // CS low,  WR low,  RD high
  PORTB |= B00001100;          // CS low,  WR high, RD high
  PORTB |= B00011100;          // CS high, WR high, RD high
  delay(10);
}
