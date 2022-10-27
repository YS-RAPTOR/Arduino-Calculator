#pragma once
#include "Arduino.h"
#include "config.h"

struct Int_Keypad {
    public:
        // Initializers and Constructors
        Int_Keypad(byte rowPins[NO_OF_ROWS], byte colPins[NO_OF_COLS], char keys[NO_OF_ROWS * NO_OF_COLS], bool* keyPressed, char* key);
        void begin();

        // Functions to enable and disable the keypad
        void Enable();
        void Disable();

        // Row Interrupts
        static void row1();
        static void row2();
        static void row3();
        static void row4();

    private:
        // Private Variables
        byte rowPins[NO_OF_ROWS];
        byte colPins[NO_OF_COLS];
        char keys[NO_OF_ROWS * NO_OF_COLS];
        bool* keyPressed;
        char* key;
};

// Promise that there is a variable called Keypad
extern Int_Keypad Keypad;