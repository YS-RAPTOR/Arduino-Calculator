#include "Password.h"

// Constructor/ Initializers

Password::Password(void (*StateChange)(byte)) : StateChange(StateChange) {
}

void Password::begin() {
    CheckMemory();
    EnterPassword();
}

void Password::ChangePassword() {
    Serial.print("Set the new password: ");
}

void Password::AcceptInput() {
    // Check if there is an input in the Serial and store it in the password Variable
    if (Serial.available()) {
        password = Serial.readString();
        password.trim();
        Serial.println(password);
        // Set the password in the EEPROM
        SetPassword();
        Serial.println("New password created!");
        StateChange(0);
    }
}

// Check EEPROM for password and read it
void Password::CheckMemory() {
    // Check if the EEPROM is empty
    if (EEPROM.read(0) == 255)
        // If it is empty, set the password to the default password
        password = DEFAULT_PASSWORD;
    else {
        // If it is not empty, read the password from the EEPROM
        for (int i = 0;; i++) {
            if (EEPROM.read(i) == 255) return;
            password += char(EEPROM.read(i));
        }
        password.trim();
    }
}

void Password::SetPassword() {
    // Set the password in the EEPROM
    for (int i = 0; i < password.length(); i++) EEPROM.update(i, password[i]);
    // Add a null character at the end of the password
    EEPROM.update(password.length(), 255);
}

// Accept the password from the Serial in the beginning of the sketch
void Password::EnterPassword() {
    while (true) {
        Serial.print("Please enter the password : ");

        // Stuck in the loop until input from the Serial is available
        while (Serial.available() == 0) {
        }

        inputPassword = Serial.readString();
        Serial.println(inputPassword);
        inputPassword.trim();

        // Check if the input password is correct
        if (inputPassword == password) {
            Serial.println("Access granted!");
            return;
        } else {
            Serial.println("Incorrect Password!");
        }
    }
}
