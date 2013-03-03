// importing the processing serial class
import processing.serial.*;
//importing the minim class
import ddf.minim.*;

Minim minim;
AudioPlayer witch;
//AudioPlayer haunted;
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
  witch = minim.loadFile("witch.wav", 2048);
//  haunted = minim.loadFile("haunted.wav", 2048);

  
  //waveform = new WaveformRenderer();
  // see the example Recordable >> addListener for more about this
  //groove.addListener(waveform);
}

void keyPressed()
{
  if ( key == 'p' ) {witch.play();witch.loop();}
  if ( key == 's' ) witch.pause();
}

void draw()
{
  background(0);
  // see waveform.pde for an explanation of how this works
  //waveform.draw();
  
  while(port.available() > 0){
        value = port.read();

//        switch((int)random(1,3)){       
        /*case 1:*/  if (value=='P') {witch.play();delay(4000);witch.loop();}
                 else if(value=='S') /*if (welcome.isPlaying())*/witch.pause();
        //case 2:  if (value=='P') {haunted.play();delay(4000);haunted.loop();}
        //         else if(value=='S') /*if (welcome.isPlaying())*/haunted.pause();
//        }
  }
   
   println(value);
}

void stop()
{
  // always close Minim audio classes when you are done with them
  witch.close();
//  haunted.close();
  // always stop Minim before exiting.
  minim.stop();
  
  super.stop();
}
