//*************************************************************************//
//* Sarcuino 
//* Version: Beta 0.19
//* By Nicholas Ward, Michael Gurevich, Miguel Ortiz, Javier Jaimovich
//*   and Brennon Bortz
//* Last modified by: Brennon Bortz
//* Date: 11 July 2012
//*************************************************************************//

#define SAMPLE_PERIOD 10        // Sample Period in Milliseconds 
                                // N.B. The arduino can sample all pins at 500Hz 
                                // This however causes serious burstiness
                                // Default is 100Hz (Same as HID devices)
                                // This avoids burstiness for most applications,
                                // Only change this if you really need a faster SR.
                                // Choose number of analog inputs to enable (0=OFF, 1=ON)
int setPins[] = {0, 0, 1, 1, 1, 0}; // Set no of analog pins e.g. {1, 0, 1, 1, 0, 0} enables pins 0, 2 and 3.
//*************--0--1--2--3--4--5
                            
// FOR REALTIME CONTROL (lower latency and burstiness)                               
// To avoid data being buffered and sent in blocks of 4KB you should insure that
// ((ANALOG_INPUTS_ENABLED * 2) + 3) * ((1/SAMPLE_PERIOD)*1000) < 3875
// This is a limitation of the ftdi usb driver
// Further details and possible solutions can be found here
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1170939903/15
// Default Sampling frequency is 100Hz (every 10ms)

//**************************************************************************//
//** Variables for data polling
//**
int analogPin, digitalPin;    // Counters for poll loop
int analogData;            // outgoing ADC value
byte x = 0; //byte to store digital status
byte y = 0; //same as above to store remaining digital pins status


const int triggerPin = 11;      // the number of the LED pin

int triggerState = LOW;
unsigned long triggerOnMillis = 0;
unsigned long triggerOffMillis = 0;
int triggerOn = 1;

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long triggerOffInterval = 21;           // interval at which to blink (milliseconds)
long triggerOnInterval = 100;
long initInterval = 5000;

//**************************************************************************//
//** Setup
//**
void setup() {

  //setup serial baudrate for USB connection
  Serial.begin(57600); 
             
  //enable digital pullups. All digital pins are set high
  //and will only output change when connected to ground
  for(digitalPin=2;digitalPin<14;++digitalPin) 
       {
        pinMode(digitalPin, INPUT);     //Setpin up for input
        digitalWrite(digitalPin, HIGH); //enable internal pullups
       }

  pinMode(triggerPin, OUTPUT);
}


//**************************************************************************//
//** Main Loop. 
//** Millis is an interrupt driven timer that begins to increment every ms once the
//** arduino starts. If millis modded with sample period is 0 then the correct sampling
//** period has passed and its time to sample again.
void loop() {

unsigned long now = millis();

long periodCheck = now % SAMPLE_PERIOD;

if (periodCheck == 0)
  {
    SampleAndSend();
  }
  
  if (now > initInterval && triggerOnMillis == 0) {
    digitalWrite(triggerPin, HIGH);
    triggerOnMillis = now;
  } else {
    if (now - triggerOnMillis > triggerOnInterval) {
      digitalWrite(triggerPin, LOW);
      pinMode(triggerPin, INPUT);
    }
  }
/*  
  if (now > initInterval) {
    if (triggerState == HIGH) {
      // Note time that we first enter this branch
      if (triggerOnMillis == 0)
        triggerOnMillis = now;
      
      // If 100ms have passed
      if (now - triggerOnMillis > triggerOnInterval) {
        triggerState = LOW;
        triggerOnMillis = 0;
      }
    } else {
      
      // Note time that we first enter this branch
      if (triggerOffMillis == 0) {
        triggerOffMillis = now;
        triggerState = LOW;
        digitalWrite(triggerPin, triggerState);
        // Serial.println("pulling low");
      }
      
      // If 20ms have passed
      if (now - triggerOffMillis > triggerOffInterval) {
        // Pull up trigger
        triggerState = HIGH;
        digitalWrite(triggerPin, triggerState);
        // Serial.println("pulling high");
        // Reset triggerOffMillis
        triggerOffMillis = 0;
      }
    }
  }
  */
}

//**************************************************************************//
//** SampleAndSend
//** This function is called by the main loop and does the actual work of
//** reading the input pins and sending the data via serial

void SampleAndSend()
{
  // Shift digital pin port D by 2 to avoid TX and RX pins
  // (more info: http://www.arduino.cc/en/Reference/PortManipulation)
  x = PIND >> 2;
  Serial.write((byte) x);
  
  // Read remaining digital pins
  y = PINB;
  Serial.write((byte) y);
  
  for (analogPin = 0; analogPin < 6; analogPin++) {
    if (setPins[analogPin]==1) {
      analogData = analogRead(analogPin); // Read current analog pin value
      Serial.write((byte) (analogData >> 7)); // shift high bits into output byte
      Serial.write((byte) (analogData % 128)); // mod by 128 for the small byte
    }
    else {
      Serial.write((byte) 0); // Send 0 to output
      Serial.write((byte) 0); // 
    }
  }     
        
  Serial.write((byte) 255); // end of packet signifier
} 


