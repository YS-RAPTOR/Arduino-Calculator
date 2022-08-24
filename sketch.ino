#include <Keypad.h>
#include <LiquidCrystal.h>

/* Code to Test Calculator Calculate Function */

// TODO Fix -+-+-+ Error
// TODO Fix - can be entered when off

#include "Calculator.h"

// Keypad initializing
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {9, 8, 7, 6};
byte colPins[KEYPAD_COLS] = {5, 4, 3, 2};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', '*'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '+'},
    {'o', '0', '.', '='}};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

LiquidCrystal lcd(14, 15, 13, 12, 11, 10);

Calculator calc;

void setup() {
    // Start serial monitor
    Serial.begin(9600);

    // lcd
    lcd.begin(16, 2);

    calc.begin(&lcd, &keypad);

    pinMode(16, OUTPUT);
    digitalWrite(16, HIGH);
    digitalWrite(16, LOW);
}

void loop() {
    calc.PollInput();
}