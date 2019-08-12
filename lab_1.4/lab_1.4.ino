#include <stdlib.h>
#include "pitches.h"

const int MELODY[] = {NOTE_E4, NOTE_E4, NOTE_E4,
                      NOTE_E4, NOTE_E4, NOTE_E4,
                      NOTE_E4, NOTE_G4, NOTE_A3, NOTE_B3,
                      NOTE_E4,
                      NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
                      NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4,
                      NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4,
                      NOTE_D4, NOTE_G4};
const int DURATIONS[] = {4, 4, 2,
                         4, 4, 2,
                         4, 4, 4, 4,
                         1,
                         4, 4, 4, 4,
                         4, 4, 4, 4,
                         4, 4, 4, 4,
                         2, 2};

void setup() {
  for (int i = 0; i < sizeof(MELODY)/sizeof(int); i++) {
    int duration = 1000/DURATIONS[i];
    tone(8, MELODY[i], duration);
    delay(duration * 1.3);
    // noTone(8);
  }
}

void loop() {
}
