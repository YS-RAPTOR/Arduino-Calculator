#pragma once
#include "Arduino.h"
#include "config.h"

struct Int_Keypad {
    public:
        Int_Keypad(byte rowPins[NO_OF_ROWS], byte colPins[NO_OF_COLS], char keys[NO_OF_ROWS * NO_OF_COLS], bool* keyPressed, char* key);
        void begin();
        void Enable();
        void Disable();

        static void row1();
        static void row2();
        static void row3();
        static void row4();

    private:
        byte rowPins[NO_OF_ROWS];
        byte colPins[NO_OF_COLS];
        char keys[NO_OF_ROWS * NO_OF_COLS];
        bool* keyPressed;
        char* key;
};

extern Int_Keypad Keypad;