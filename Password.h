#pragma once

#include <EEPROM.h>

#include "Arduino.h"
#include "config.h"

struct Password {
    public:
        Password(void (*StateChange)(byte));
        void begin();
        void ChangePassword();
        void AcceptInput();

    private:
        String inputPassword;
        String password;

        void (*StateChange)(byte);

        void CheckMemory();
        void SetPassword();
        void EnterPassword();
};