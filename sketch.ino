/* Code to Test Calculator Calculate Function */

#include "Calculator.h"

Calculator calc;
String expression;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.println("Enter Expression to Solve");
}

void loop() {
    if (Serial.available() > 0) {
        expression = Serial.readString();
        Serial.println(calc.Calculate(expression));
    }
}