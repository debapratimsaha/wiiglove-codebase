/*******************************************************************
Code written with help from the following link -
http://my.safaribooksonline.com/book/hobbies/9781449399368/..
..serial-communications/logging_arduino_data_to_a_file_on_yo

This code saves data received from Arduino COM Port and writes into a
a file with fileName=(Current Date and Time). Pressing any key saves 
the file into the same directory as the processing sketch.
*********************************************************************/

import processing.serial.*;

PrintWriter output;
DateFormat fnameFormat= new SimpleDateFormat("yyMMdd_HHmm");
String fileName;

Serial myPort;
char HEADER = 'H';

void setup(){
  size(200, 200);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 115200);
  println("Connected to Port -->" + myPort);
  
  Date now = new Date();
  fileName = fnameFormat.format(now);
  output = createWriter(fileName + ".txt");
}

void draw(){
  int val;
  while ( myPort.available() > 0)  {
    if (myPort.read() == HEADER){
      for (int i=0;i<600;i++){
        val = readArduinoData();
        println(val);
        output.println(val);
      }
    }
  }
}

void keyPressed() {
  output.flush(); // Writes the remaining data to the file
  output.close(); // Finishes the file
  exit();         // Stops the program
}

int readArduinoData(){
  int value,lo_val,hi_val;
  value = myPort.read()<<2;
//  println("lower byte ="+lo_val);
//  println("high value =" +hi_val);
  
//  value = hi_val*256+lo_val;
  
  return value;
}
