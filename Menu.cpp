#include "Menu.h"

// Constructor
Menu::Menu(void (*StateChange)(byte)) : StateChange(StateChange) {
}

void Menu::DisplayMenu() {
    // Print the Menu
    Serial.println("-------------------------------------------");
    Serial.println("Please select one of the options provided: ");
    Serial.println("1 - Change the default password");
    Serial.println("2 - Open timer");
    Serial.println("3 - Open calculator");
    Serial.println("-------------------------------------------");
}

void Menu::AcceptInput() {
    // Check if the Serial is available and read the Serial for the option
    if (Serial.available()) {
        option = Serial.parseInt();
        Serial.read();
        Serial.flush();
        CheckOption();
    }
}

void Menu::CheckOption() {
    // Check if the option is valid and change the state accordingly
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
