#include "Menu.h"

Menu::Menu(void (*StateChange)(byte)) : StateChange(StateChange) {
}

void Menu::DisplayMenu() {
    Serial.println("-------------------------------------------");
    Serial.println("Please select one of the options provided: ");
    Serial.println("1 - Change the default password");
    Serial.println("2 - Open timer");
    Serial.println("3 - Open calculator");
    Serial.println("-------------------------------------------");

    Serial.print("Option selected : ");
}

void Menu::AcceptInput() {
    if (Serial.available()) {
        option = Serial.parseInt();
        Serial.read();
        Serial.flush();
        Serial.println(option);
        CheckOption();
    }
}

void Menu::CheckOption() {
    switch (option) {
        case 1:
            Serial.println("Option 1 is selected");
            StateChange(1);
            break;
        case 2:
            Serial.println("Option 2 is selected");
            StateChange(2);
            break;
        case 3:
            Serial.println("Option 3 is selected");
            StateChange(3);
            break;
        default:
            Serial.println("Invalid Option!");
            break;
    }
}
