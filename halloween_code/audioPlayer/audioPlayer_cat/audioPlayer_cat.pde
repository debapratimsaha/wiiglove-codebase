// importing the processing serial class
import processing.serial.*;
//importing the minim class
import ddf.minim.*;

Minim minim;
AudioPlayer cat;
Serial port;
int value = 0;
//WaveformRenderer waveform;

void setup()
{
  size(512, 200, P3D);
  
   println(Serial.list());
  // set size and framerate
  //size(xWidth, yHeight); frameRate(fr);
  // establish serial port connection      
  port = new Serial(this, Serial.list()[1], 9600);

  minim = new Minim(this);
  cat = minim.loadFile("cat.wav", 2048);
  
  //waveform = new WaveformRenderer();
  // see the example Recordable >> addListener for more about this
  //groove.addListener(waveform);
}

void keyPressed()
{
  if ( key == 'p' ) {cat.play();cat.loop();}
  if ( key == 's' ) cat.pause();
}

void draw()
{
  background(0);
  // see waveform.pde for an explanation of how this works
  //waveform.draw();
  
  while(port.available() > 0){
        value = port.read();
       
        if (value=='P') {cat.play();delay(1000);cat.loop();}
        else if(value=='S') /*if (welcome.isPlaying())*/cat.pause();
  }
   
   println(value);
}

void stop()
{
  // always close Minim audio classes when you are done with them
  cat.close();
  // always stop Minim before exiting.
  minim.stop();
  
  super.stop();
}
