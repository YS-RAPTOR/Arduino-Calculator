#pragma once
#include "Arduino.h"
#include "config.h"

struct Menu {
    public:
        // Constructor
        Menu(void (*StateChange)(byte));

        // Prints the menu to the Serial
        void DisplayMenu();

        // Public Input Function. Runs in the loop
        void AcceptInput();

    private:
        // State Change function
        void (*StateChange)(byte);
        // Stores the option made by user
        byte option;
        // Validates option and changes state
        void CheckOption();
};