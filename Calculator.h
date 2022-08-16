#pragma once

#include <Arduino.h>

#define MAX_EXPRESSION_LENGTH 256
#define NumberOfOperators 4
#define FORMAT_ERROR "Error: Expression is not formatted correctly"
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

        // Constructors/Initializers
        Calculator();

        // Calculate Functions
        double ApplyOperation(double num1, double num2, char op);
        String Calculate(String expression);
};
