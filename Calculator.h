#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "config.h"

struct Calculator {
        // Constructors/Initializers
        Calculator(bool* keyPressed, char* key, bool* power, void (*StateChange)(byte), LiquidCrystal* lcd);
        void begin();

        // Run Function when changing state to calculator
        void EnterCalculator();

        // Public Input Function. Runs in the Loop
        void AcceptInput();

    private:
        // Stacks for Calculate Function
        char operatorStack[MAX_EXPRESSION_LENGTH / 2];
        double digitStack[MAX_EXPRESSION_LENGTH / 2];
        byte operatorStackTop = 0;
        byte digitStackTop = 0;
        String expression = "";

        // Check if Brackets are fully closed
        char brackets = 0;

        // Input Variables
        void (*StateChange)(byte);
        bool* keyPressed;
        char* key;

        // Output Variables
        LiquidCrystal* lcd;
        bool* power;
        byte upperCursorLimit = 0;
        byte cursorPosition = 0;
        byte drawLocation = 0;

        // Memory
        double memory = 0.0;
        double answer = 0.0;
        String temp = "";

        // Helper Functions
        static inline bool IsOperator(char c);
        static inline bool IsFunction(char f);
        static inline bool IsMultiplier(char c);
        static inline byte Precedence(char op);
        static String DoubleToString(double d);

        // Stacks Functions
        void PushOperator(char op);
        void PushDigit(double digit);
        void PushDigit(String& digit);
        void PopOperator();
        void PopDigit();
        char PeekOperator();
        double PeekDigit();
        void ClearStacks();

        // Calculate Functions
        void ApplyOperation(double& num1, double& num2);
        bool Calculate();

        // Input Functions
        void KeyCheck();

        // Output Functions
        void ToggleDisplay();
        bool InsertKey(String&& str);
        bool InsertKey();
        void Backspace();
        void MoveLeft();
        void MoveRight();
        void DisplayAnswer();
        void DisplayError();
        void DisplayExpression();
        void Reset();

        // Define Syntax Errors
        bool IsSyntaxError();
};
