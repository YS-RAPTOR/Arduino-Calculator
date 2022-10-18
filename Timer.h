#pragma once

#include <LiquidCrystal.h>
#include <RTClib.h>
#include <Wire.h>

#include "Arduino.h"
#include "config.h"

static const DateTime ReferenceDate(2000, 1, 1, 0, 0, 0);

struct Timer {
    public:
        // Constructor/ Initializers
        Timer(bool* keyPressed, char* key, bool* power, void (*StateChange)(byte), LiquidCrystal* lcd);
        void begin();

        // Run Function when changing state to calculator
        void EnterTimer();

        // Runs in a TimerInterrupt
        void Update();

        // Public Input Function. Runs in the Loop
        void AcceptInput();

        // Updates Timer String. Runs in the Loop
        void UpdateTimerString();

    private:
        // Input Variables
        bool* keyPressed;
        char* key;
        void (*StateChange)(byte);

        RTC_DS1307 rtc;
        LiquidCrystal* lcd;
        bool* power;

        unsigned long startTime = 0;
        unsigned long setTime = 0;
        unsigned long remainingTime = 0;
        byte temp;
        String timerString = "00:00:00";
        byte state = 0;  // State 0 : Stopped, State 1 : Active, State 2 : Set
        byte cursorPosition = 0;

        // Input Functions
        void KeyCheck();

        // Output Functions
        void InsertKey();
        void MoveLeft();
        void MoveRight();
        void ToggleDisplay();
        void DisplayInstructions();

        // Functions for Working with Timer
        void Reset();
        void Set();
        void Start();
        void Stop();
};