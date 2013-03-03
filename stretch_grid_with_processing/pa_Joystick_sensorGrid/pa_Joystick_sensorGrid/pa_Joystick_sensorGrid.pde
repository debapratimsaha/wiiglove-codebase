/*
*  pa_Joystick
*  
*  A drawing program, the cursur is controlled by a joystick or two potentiometers.
*  Use keys to control the following functions:
*   'ENTER' to start/stop drawing
*   'BACKSPACE' to clear the screen
*   'C' to switch between red/green/blue as drawing colors
*   '+' and '-' to increase/decrease stroke weight
* 
*  This file is part of the Arduino meets Processing Project.
*  For more information visit http://www.arduino.cc.
*
*  copyleft 2005 by Melvin Ochsmann for Malm� University
*
*/

// importing the processing serial class
  import processing.serial.*;
// the display item draws background and grid
  DisplayItems di;
// definition of window size and framerate
  int xWidth = 512;
  int yHeight = 512;
  int fr = 24;
// attributes of the display
  boolean bck = true;
  boolean grid = false;
  boolean g_vert = true;
  boolean g_horiz = true;
  boolean g_values = false;
  boolean output = true;
// variables for serial connection, portname and baudrate have to be set 
  Serial port;
  //String portname = "/dev/cu.usbserial-1B1"; 
  int baudrate = 9600;
  int value = 0; 
// buffer and value variable for each value and boolean to switch between values
  String bufA="", bufB="", bufC="", bufD="";  
  boolean buf1,buf2;  // boolean switch to distinguish values
  int value1=255, value2=255;  // value1, value2 that then are passed on to xpos and ypos
// variables for drawing function
  int xpos, ypos;
  int prevX, prevY;
  boolean paint = false;
  int curCol = 1;
  int strWght = 1;
  
// lets user control DisplayItems properties, value output and drawing attributes
void keyPressed(){
  if (key == 'b' || key == 'B') bck=!bck;  // background black/white
  if (key == 'g' || key == 'G') grid=!grid;  // grid ON/OFF 
  if (key == 'v' || key == 'V') g_values=!g_values;  // grid values ON/IFF   
  if (key == 'o' || key == 'O') output=!output;   //turns value output ON/OFF
  if (keyCode == ENTER) paint=!paint; // enter turn paint ON/OFF
  if (keyCode == BACKSPACE) clear(); //backspace clears screen
  // + and - increase/decrease stroke weight 
  if (key == '+') { if(strWght == 5){strWght = 5;}else{strWght++;}}
  if (key == '-') { if(strWght == 1){strWght = 1;}else{strWght--;}}
  // c switches colors between red/blue/green
  if (key == 'c' || key == 'C') { curCol++; if(curCol > 3)curCol=1; }; 
}

void setup(){
  println(Serial.list());
  // set size and framerate
  size(xWidth, yHeight); frameRate(fr);
  // establish serial port connection      
  port = new Serial(this, Serial.list()[1], baudrate);
  println("Port --"+port);
  // create DisplayItems object
  di = new DisplayItems();
}

void clear(){
   background( (bck) ? (0) : (255) );
}

void drawLine(int x, int y, int px, int py){
   line(x, y, px, py);
}

void drawCursor(int x, int y){
  background(  (bck) ? (0) : (255) );
  stroke( (bck) ? (255) : (32) );
  strokeWeight(1);
  line(x-(width/128), y , x+(width/128), y );
  line(x, y-(width/128), x, y+(width/128) );
}

char serialCycle;
void serialEvent(int serial){
  if(serial!=10) {
    if (serial=='A') {buf1 = true; serialCycle='A';}
    if (serial=='B') {buf1 = false; serialCycle='B';}
    if (serial=='C') {buf2 = true; serialCycle='C';}
    if (serial=='D') {buf2 = false; serialCycle='D';} 
 
    if (serialCycle=='A')
      if (serial!='A') bufA += serial;
    if (serialCycle=='B')
      if (serial!='B') bufB += serial;
    if (serialCycle=='C')
      if (serial!='C') bufC += serial;
    if (serialCycle=='D')
      if (serial!='D') bufD += serial;
  }else{
    if (serialCycle=='A')
      {value1 = 255+int(bufA); bufA="";}
    if (serialCycle=='B')
      {value2 = 255+int(bufB); bufB="";}
    if (serialCycle=='C')
      {value1 = 255-int(bufC); bufC="";}
    if (serialCycle=='D')
      {value2 = 255-int(bufD); bufD="";}
  }
  
}

int counter = 0;
void startDrawing(){
  if (!paint)  { drawCursor( xpos, ypos ); }
  if (paint) { strokeWeight(strWght); drawLine( xpos, ypos, prevX, prevY ); }
}

void draw(){
// set previous x and y position to current x and y position
  prevX=xpos;
  prevY=ypos;
// listen to serial port and trigger serial event     
  while(port.available() > 0){
        value = port.read();
        serialEvent(value);
   }
// read values 1 and 2 and transform in x and y position
//  xpos = constrain(((value1-100)*(width+100))/width , 0, width );
//  ypos = constrain(((value2-100)*(height+100))/height , 0, height );
  xpos = constrain(value1 , 0, width );
  ypos = constrain(value2 , 0, height );
// paint background if paint is false                        
  if(!paint) di.drawBack();
// set color if paint is true
  if(paint){
    switch(curCol){
        case 1: stroke(255, 0, 0); break;
        case 2: stroke(0, 255, 0); break;
        case 3: stroke(0, 0, 255); break;
        }
   }
    // begin drawing and drawItems
   startDrawing();
   di.drawItems();
   if (output) println("xpos: "+xpos+" - ypos: "+ypos);
   if (output) println("value1: "+value1+" - value2: "+value2);
}
