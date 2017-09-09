/** 
 *  Code to control Phill
 */
#include <CurieBLE.h>

#define LED 6 //connect LED to digital pin 6
#define SPK 7 //connect speaker to digital pin 7
#define BTN 2 //connect pushbutton to digital pin 2

/* =========================Bluetooth variables========================= */
BLEPeripheral blePeripheral; // create peripheral instance
BLEService ledService("19B10010-E8F2-537E-4F6C-D104768A1214"); // create service
BLECharCharacteristic ledCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);


int length = 4;         /* the number of notes */
char notes[] = "cdeg";
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 60;
int state = 2;  // 0 means alarm off, 1 means alarm set, 2 means alarm on
int count = 0;
unsigned long currTime;

void setup() {                
  // initialize the digital pin2 as an output.
  pinMode(LED, OUTPUT);
  pinMode(SPK, OUTPUT);  
  pinMode(BTN, INPUT);

  blePeripheral.setLocalName("Phil1");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(ledCharacteristic);
  ledCharacteristic.setValue(0);
  blePeripheral.begin();
  Serial.println("Bluetooth device active, waiting for connections...");

  currTime = millis();
}


void loop() {

  
  if (state == 0) {
    // Check for alarm being scheduled
    blePeripheral.poll();
    if(ledCharacteristic.written()) {
      currTime = millis();
      state = 1;
    }
  } else if (state == 1) {
    if (millis() > currTime + 5000) {
            state = 2;
    }
  } else if(state == 2) {
      alarm();
      if(digitalRead(BTN) == HIGH) {
        state = 0;
      }
  }
  else {
    
  }
}

// start/stop alarm sequence
void alarm() {
  flash(250);
  if (count % 20 == 0)
    playSong();
  count = count + 1;

}

// flash the LED in an alarming manner
void flash(int timeOn) {
    digitalWrite(LED, HIGH);
    delay(timeOn);
    digitalWrite(LED, LOW);
    delay(timeOn);
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

