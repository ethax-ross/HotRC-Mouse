/*MSE Sound sketch
13th March 2021

Fork for use with the 6 channel HotRC DS600 remote/receiver. Pins D3-D6 on the Nano map to channels 3-6 on the RC receiver.

MrBaddeley printed droids - www.patreon.com/mrbaddeley www.facebook.com/groups/mrbaddeley
This sketch is to control the sound on the full scale MSE-6 Mouse Droid
This code is using a Nano, AltSoftserial on pins 8 and 9, and a DF Player. 

AltSoftSerial has sorted a few issues with interrupts out for me on the code, allowing me to accurately read all the inputs. 

Functions:

CH3 (UP on remote) - play first sound copied to SD card (I use the loop sound - by default the first sound, when played, will repeat).
CH6 (RIGHT on remote) - play second sound copied to SD card.
CH4 (DOWN on remote) - play third sound copied to SD card.
CH5 (LEFT on remote) - play fourth sound copied to SD card.

The code plays the first MP3 on boot.

Libraries used:

https://github.com/DFRobot/DFRobotDFPlayerMini
https://www.arduino.cc/reference/en/libraries/altsoftserial/

Not perfect, but should get people started. 
*/

#include "Arduino.h"  // Libraries for DFplayer and SerialSoftware
#include <AltSoftSerial.h>  // Load the AltSoftSerial library
#include "DFRobotDFPlayerMini.h"

AltSoftSerial altSerial;
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int sw3;  // To store data from the RC switches (channels 3-6). 
int sw4;
int sw5;
int sw6;

int sw3pin = 3;  // Set the Arduino pins for reading the RC
int sw4pin = 4;
int sw5pin = 5;
int sw6pin = 6;

int ch3PrevState = 0; // Set variables for the states of channels/switches
int ch3State = 0;
int ch4PrevState = 0;
int ch4State = 0;
int ch5PrevState = 0;
int ch5State = 0;
int ch6PrevState = 0;
int ch6State = 0;

void setup() {
    altSerial.begin(9600);
    Serial.begin(115200);  // Starts HW serial @ 115200, used for Serial monitor to diagnose

    Serial.println();
    Serial.println(F("DFRobot DFPlayer Mini Demo"));
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));  // Prints some starting messages.

    if (!myDFPlayer.begin(altSerial)) {  // Use softwareSerial to communicate with mp3 and checks link.
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1. Please recheck the connection!"));
        Serial.println(F("2. Please insert the SD card!"));
        while (true) {
            delay(0);  // Code to compatible with ESP8266 watch dog.
        }
    }
    Serial.println(F("DFPlayer Mini online."));

    myDFPlayer.volume(30);  // Set volume value. From 0 to 30
    myDFPlayer.loop(1);  // Play the first mp3 plays the first MP3 to indicate it's all working. 
}

void loop() {
    sw3 = pulseIn(sw3pin, HIGH);  // These read the status of the 4 switches
    sw4 = pulseIn(sw4pin, HIGH);
    sw5 = pulseIn(sw5pin, HIGH);
    sw6 = pulseIn(sw6pin, HIGH);

    Serial.print(sw3);  // Diagnostic serial prints
    Serial.print(" ");
    Serial.print(sw4);
    Serial.print(" ");
    Serial.print(sw5);
    Serial.print(" ");
    Serial.print(sw6);
    Serial.println(" ");

    // Update channel states based on switch readings.
    ch3State = (sw3 < 1500) ? 0 : 1;
    ch4State = (sw4 < 1500) ? 0 : 1;
    ch5State = (sw5 < 1500) ? 0 : 1;
    ch6State = (sw6 < 1500) ? 0 : 1;

    if (ch3State != ch3PrevState) {
      myDFPlayer.pause();
      myDFPlayer.loop(1);  // UP - play the first sound (looped).
      Serial.println("Playing 1 on loop");
      ch3PrevState = ch3State;
    }

    // Channel 6 works differently, it goes on when pressed then off when released.
    if (ch6State != ch6PrevState) {
      ch6PrevState = ch6State;
      if (ch6State == 1) {
        myDFPlayer.pause();
        myDFPlayer.disableLoop();
        myDFPlayer.play(2);  // RIGHT - play the second sound.
        Serial.println("Playing 2");
      }
    }

    if (ch4State != ch4PrevState) {
      myDFPlayer.pause();
      myDFPlayer.disableLoop();
      myDFPlayer.play(3);  // DOWN - play the third sound.
      Serial.println("Playing 3");
      ch4PrevState = ch4State;
    }

    if (ch5State != ch5PrevState) {
      myDFPlayer.pause();
      myDFPlayer.disableLoop();
      myDFPlayer.play(4);  // LEFT - play the fourth sound.
      Serial.println("Playing 4");
      ch5PrevState = ch5State;
    }
}