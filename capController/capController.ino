/** 
 *  Code to control Phill
 */

#define LED 6 //connect LED to digital pin 6
#define SPK 7 //connect speaker to digital pin 7
#define BTN 2 //connect pushbutton to digital pin 2

int length = 4;         /* the number of notes */
char notes[] = "cdeg";
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 60;
int alarmOn = 0;

void setup() {                
  // initialize the digital pin2 as an output.
  pinMode(LED, OUTPUT);
  pinMode(SPK, OUTPUT);  
  pinMode(BTN, INPUT);
}


void loop() {
  alarm(alarmOn);
}

// start/stop alarm sequence
void alarm(bool ON) {
  if(ON) {
    flash(250,10);
    playSong();
  }
}

// flash the LED in an alarming manner
void flash(int timeOn, int numFlash) {
  for (int i = 0; i < numFlash; i++) {
    digitalWrite(LED, HIGH);
    delay(timeOn);
    digitalWrite(LED, LOW);
    delay(timeOn);
  }
}

// play the note sequence
void playSong() {
    for(int i = 0; i < length; i++) {
        if(notes[i] == ' ') {
            delay(beats[i] * tempo);
        } else {
            playNote(notes[i], beats[i] * tempo);
        }
        delay(tempo / 2);    /* delay between notes */
    }
}

// play a given note for a given time
void playNote(char note, int duration) {
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

    // play the tone corresponding to the note name
    for (int i = 0; i < 8; i++) {
        if (names[i] == note) {
            playTone(tones[i], duration);
        }
    }
}

// play a given tone for a given time
void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(SPK, HIGH);
        delayMicroseconds(tone);
        digitalWrite(SPK, LOW);
        delayMicroseconds(tone);
    }
}

