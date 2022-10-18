#include "Password.h"

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
    if (Serial.available()) {
        password = Serial.readString();
        password.trim();
        Serial.println(password);
        SetPassword();
        Serial.println("New password created!");
        StateChange(0);
    }
}

void Password::CheckMemory() {
    if (EEPROM.read(0) == 255)
        password = DEFAULT_PASSWORD;
    else {
        for (int i = 0;; i++) {
            if (EEPROM.read(i) == 255) return;
            password += char(EEPROM.read(i));
        }
        password.trim();
    }
}

void Password::SetPassword() {
    for (int i = 0; i < password.length(); i++) EEPROM.update(i, password[i]);
    EEPROM.update(password.length(), 255);
}

void Password::EnterPassword() {
    while (true) {
        Serial.print("Please enter the password : ");

        while (Serial.available() == 0) {
        }

        inputPassword = Serial.readString();
        Serial.println(inputPassword);
        inputPassword.trim();

        if (inputPassword == password) {
            Serial.println("Access granted!");
            return;
        } else {
            Serial.println("Incorrect Password!");
        }
    }
}
