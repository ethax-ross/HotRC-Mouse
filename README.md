Rewrites [the default sketch](https://github.com/MrBaddeley/FullScaleMouse-) for Mr Baddeley's mouse droid to work with the HotRC DS600 remote and receiver. Channels 3-6 on the receiver are used to control sounds and should be plugged into pins 3-6 on the Nano (the sound assigned to channel 3 will loop by default):

CH3 (UP on remote) - play first sound copied to SD card (I use the loop sound - by default the first sound, when played, will repeat). 
CH6 (RIGHT on remote) - play second sound copied to SD card. 
CH4 (DOWN on remote) - play third sound copied to SD card. 
CH5 (LEFT on remote) - play fourth sound copied to SD card.

The HotRC remote seems to only activate channel 6 when pressed, whereas channels 3-5 are sticky (press once to go HIGH and again to go LOW). The code deals with this so they all just behave the same (play the sound once when pressed and enable looping if channel 3).
