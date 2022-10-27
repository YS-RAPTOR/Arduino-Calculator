#pragma once

#include <EEPROM.h>

#include "Arduino.h"
#include "config.h"

struct Password {
    public:
        // Constructor/ Initializers
        Password(void (*StateChange)(byte));
        void begin();

        // Run Function when changing state to password. Prints the prompt to change password
        void ChangePassword();
        // Runs in the loop. Accepts input from the Serial
        void AcceptInput();

    private:
        // Stores the userInput password and the password stored in the EEPROM
        String inputPassword;
        String password;

        // Stores the state change function
        void (*StateChange)(byte);

        // Check EEPROM for password and read it
        void CheckMemory();

        // Set the password in the EEPROM
        void SetPassword();

        // Accept the password from the Serial in the beginning
        void EnterPassword();
};