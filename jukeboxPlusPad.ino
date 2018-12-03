/*
 * MP3_Play_Test.ino
 * A quick start example for Grove-Serial MP3 Player V2.0
 * Note: The MP3 chip of Grove-Serial MP3 Player V2.0 is different from Grove-Serial MP3 Player V1.0
 * Description: This demo let you can send instruction 1-8 to control the Grove-Serial MP3 Player, via the serial port.
 *
 * Copyright (c) 2015 seeed technology inc.
 * Author     : Wuruibin
 * Created Time: Dec 2015
 * Modified Time:
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * KEYPAD mapping
 * Pins : X1234567X (vu de face)

2 : R1 PIN6
7 : R2 PIN11
6 : R3 PIN10
4 : R4 PIN8

3 : C1 PIN7
1 : C2 PIN5
5 : C3 PIN9
 */

// http://wiki.seeedstudio.com/Grove-MP3_v2.0/

// Careful with the Grove MP3: if you plug the mini-jack completely the channels will conflict and the sound will be outright bad. Just leave a few millimeters and it will be fine.

#include <SoftwareSerial.h>
#include <MP3Player_KT403A.h>
#include <Keypad.h>



// Note: You must define a SoftwareSerial class object that the name must be mp3, 
//       but you can change the pin number according to the actual situation.
SoftwareSerial mp3(2, 3);


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {6, 11, 10, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 5, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

bool paused = false;

void setup(){
    mp3.begin(9600);
    delay(100);

    SelectPlayerDevice(0x02);       // Select SD card as the player device.
    SetVolume(0x1E);                // Set the volume, the range is 0x00 to 0x1E.

    Serial.begin(9600);
}


void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
    switch (key) {
      case '0':
        SpecifyMusicPlay(1);    
        break;
      case '1':
        SpecifyMusicPlay(2);    
        break;
      case '2':
        SpecifyMusicPlay(3);    
        break;
      case '3':
        SpecifyMusicPlay(4);            
        break;
      case '4':
        SpecifyMusicPlay(5);    
        break;
      case '5':
        SpecifyMusicPlay(6);    
        break;
      case '6':
        SpecifyMusicPlay(7);    
        break;
      case '7':
        SpecifyMusicPlay(8);      
        break;
      case '8':
        SpecifyMusicPlay(9);       
        break;
      case '9':
        SpecifyMusicPlay(10);            
        break;
      case '*':
        SpecifyMusicPlay(11);        
        break;
      case '#':
        if (paused) {
          PlayResume();
          paused = false;
        } else {
          PlayPause();
          paused = true;
        }        
        break;
  
      default:    
        break;
    }
    
  }
}
