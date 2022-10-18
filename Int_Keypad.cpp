#include "Int_Keypad.h"

Int_Keypad::Int_Keypad(byte rowPins[NO_OF_ROWS], byte colPins[NO_OF_COLS], char keys[NO_OF_ROWS * NO_OF_COLS], bool* keyPressed, char* key) {
    memcpy(this->rowPins, rowPins, NO_OF_ROWS);
    memcpy(this->colPins, colPins, NO_OF_COLS);
    memcpy(this->keys, keys, NO_OF_ROWS * NO_OF_COLS);
    this->keyPressed = keyPressed;
    this->key = key;
}

void Int_Keypad::begin() {
    for (byte i = 0; i < NO_OF_ROWS; i++) {
        pinMode(rowPins[i], INPUT_PULLUP);
    }
    for (byte i = 0; i < NO_OF_COLS; i++) {
        pinMode(colPins[i], OUTPUT);
        digitalWrite(colPins[i], LOW);
    }
}

void Int_Keypad::Enable() {
    attachInterrupt(digitalPinToInterrupt(rowPins[0]), Int_Keypad::row1, FALLING);
    attachInterrupt(digitalPinToInterrupt(rowPins[1]), Int_Keypad::row2, FALLING);
    attachInterrupt(digitalPinToInterrupt(rowPins[2]), Int_Keypad::row3, FALLING);
    attachInterrupt(digitalPinToInterrupt(rowPins[3]), Int_Keypad::row4, FALLING);
}

void Int_Keypad::Disable() {
    detachInterrupt(digitalPinToInterrupt(rowPins[0]));
    detachInterrupt(digitalPinToInterrupt(rowPins[1]));
    detachInterrupt(digitalPinToInterrupt(rowPins[2]));
    detachInterrupt(digitalPinToInterrupt(rowPins[3]));
}

void Int_Keypad::row1() {
    // detaching the interrupt to prevent the interrupt being called again causing an infinite loop
    detachInterrupt(digitalPinToInterrupt(Keypad.rowPins[0]));
    // It loops through each column and finds at which column does the row go HIGH
    for (byte i = 0; i < NO_OF_COLS; i++) {
        digitalWrite(Keypad.colPins[i], HIGH);         // sets the column as HIGH
        if (digitalRead(Keypad.rowPins[0]) == HIGH) {  // if the row becomes HIGH, it will accept the input
            *Keypad.key = Keypad.keys[i];
            *Keypad.keyPressed = true;
        }
        digitalWrite(Keypad.colPins[i], LOW);  // sets the column as LOW
    }
    attachInterrupt(digitalPinToInterrupt(Keypad.rowPins[0]), row1, FALLING);  // putting the interrupt back up
}
void Int_Keypad::row2() {
    // Is similar to Function Row1. Instead of using rowPins[0] using rowPins[1] and key = keys[i + NO_OF_COLS] (to make it move down by no. of columns)
    detachInterrupt(digitalPinToInterrupt(Keypad.rowPins[1]));
    for (byte i = 0; i < NO_OF_COLS; i++) {
        digitalWrite(Keypad.colPins[i], HIGH);
        if (digitalRead(Keypad.rowPins[1]) == HIGH) {
            *Keypad.key = Keypad.keys[NO_OF_COLS + i];
            *Keypad.keyPressed = true;
        }
        digitalWrite(Keypad.colPins[i], LOW);
    }
    attachInterrupt(digitalPinToInterrupt(Keypad.rowPins[1]), row2, FALLING);
}
void Int_Keypad::row3() {
    // Is similar to Function Row1. Instead of using rowPins[0] using rowPins[2] and key = keys[i + NO_OF_COLS * 2] (to make it move down twice by no. of columns)
    detachInterrupt(digitalPinToInterrupt(Keypad.rowPins[2]));
    for (byte i = 0; i < NO_OF_COLS; i++) {
        digitalWrite(Keypad.colPins[i], HIGH);
        if (digitalRead(Keypad.rowPins[2]) == HIGH) {
            *Keypad.key = Keypad.keys[NO_OF_COLS * 2 + i];
            *Keypad.keyPressed = true;
        }
        digitalWrite(Keypad.colPins[i], LOW);
    }
    attachInterrupt(digitalPinToInterrupt(Keypad.rowPins[2]), row3, FALLING);
}
void Int_Keypad::row4() {
    // Is similar to Function Row1. Instead of using rowPins[0] using rowPins[2] and key = keys[i + NO_OF_COLS * 3] (to make it move down three times by no. of columns)
    detachInterrupt(digitalPinToInterrupt(Keypad.rowPins[3]));
    for (byte i = 0; i < NO_OF_COLS; i++) {
        digitalWrite(Keypad.colPins[i], HIGH);
        if (digitalRead(Keypad.rowPins[3]) == HIGH) {
            *Keypad.key = Keypad.keys[NO_OF_COLS * 3 + i];
            *Keypad.keyPressed = true;
        }
        digitalWrite(Keypad.colPins[i], LOW);
    }
    attachInterrupt(digitalPinToInterrupt(Keypad.rowPins[3]), row4, FALLING);
}