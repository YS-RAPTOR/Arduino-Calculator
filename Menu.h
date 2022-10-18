#pragma once
#include "Arduino.h"
#include "config.h"

struct Menu {
    public:
        Menu(void (*StateChange)(byte));
        void DisplayMenu();
        void AcceptInput();

    private:
        void (*StateChange)(byte);
        byte option;
        void CheckOption();
};