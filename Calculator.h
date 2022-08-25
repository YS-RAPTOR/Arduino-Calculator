#pragma once

#include <Arduino.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

#define MAX_EXPRESSION_LENGTH 256
#define NumberOfOperators 4
#define FORMAT_ERROR "Syntax Error"
static const char OPERATORS[NumberOfOperators] = {'+', '-', '*', '/'};
static const char MULTIPLIERS[] = {'+', '-'};
inline bool IsOperator(char c);
inline bool IsMultiplier(char c);
inline byte Precedence(char op);

struct Calculator {
        // Stacks for Calculate Function
        char operatorStack[MAX_EXPRESSION_LENGTH / 2];
        double digitStack[MAX_EXPRESSION_LENGTH / 2];
        byte operatorStackTop = 0;
        byte digitStackTop = 0;

        // Stacks Functions
        void PushOperator(char op);
        void PushDigit(double digit);
        void PushDigit(String& digit);
        void PopOperator();
        void PopDigit();
        char PeekOperator();
        double PeekDigit();
        void Clear();

        // Devices
        LiquidCrystal* lcd;
        Keypad* keypad;
        bool power;

        // Memory
        char key;
        String currentToken = "";
        char prevToken;
        byte currentTokenIndex = 0;
        String expression = "";

        // Input Functions
        void PollInput();
        void ProcessInput();
        bool HandleRepetition();

        // Output Functions
        void DisplayExpression();
        void DisplayAnswer(String answer);
        void ToggleDisplay();

        // Constructors/Initializers
        Calculator();
        void begin(LiquidCrystal* lcd, Keypad* keypad);
        void Reset();

        // Calculate Functions
        double ApplyOperation(double num1, double num2, char op);
        String Calculate();
};
