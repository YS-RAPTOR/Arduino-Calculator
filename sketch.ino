#include "Calculator.h"
#include "Int_Keypad.h"
#include "Menu.h"
#include "Password.h"
#include "Timer.h"
#include "config.h"

// 0 - Menu, 1 - Change Password, 2 - Timer, 3 - Calculator
byte state;
bool keyPressed = false;
char key;
bool power = false;

Menu menu(StateChange);
Password password(StateChange);
Int_Keypad Keypad(rowPins, colPins, keys, &keyPressed, &key);
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_DATA_PINS);
Calculator calculator(&keyPressed, &key, &power, StateChange, &lcd);
Timer timer(&keyPressed, &key, &power, StateChange, &lcd);

void setup() {
    // Begin Systems
    Serial.begin(9600);
    Keypad.begin();
    password.begin();
    lcd.begin(SCREEN_LENGTH, LCD_ROWS);
    calculator.begin();
    timer.begin();
    pinMode(LCD_ANODE, OUTPUT);
    StateChange(0);
}

void loop() {
    switch (state) {
        case 0:
            menu.AcceptInput();
            break;
        case 1:
            password.AcceptInput();
            break;
        case 2:
            timer.UpdateTimerString();
            timer.AcceptInput();
            break;
        case 3:
            calculator.AcceptInput();
            break;
        default:
            state = 0;
            break;
    }
    timer.Update();
}

void StateChange(byte newState) {
    switch (newState) {
        case 0:
            TurnDisplayOff();
            Keypad.Disable();
            menu.DisplayMenu();
            break;
        case 1:
            TurnDisplayOff();
            Keypad.Disable();
            password.ChangePassword();
            break;
        case 2:
            timer.EnterTimer();
            Keypad.Enable();
            break;
        case 3:
            calculator.EnterCalculator();
            Keypad.Enable();
            break;
        default:
            break;
    };

    state = newState;
}

void TurnDisplayOff() {
    // Turn display off by negating the anode
    power = false;
    lcd.clear();
    lcd.noCursor();
    digitalWrite(LCD_ANODE, LOW);
}
