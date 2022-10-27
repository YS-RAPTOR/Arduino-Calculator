#include "Calculator.h"

// Constructors/Initializers
Calculator::Calculator(bool* keyPressed, char* key, bool* power, void (*StateChange)(byte), LiquidCrystal* lcd) : keyPressed(keyPressed), key(key), power(power), StateChange(StateChange), lcd(lcd) {
    ClearStacks();
}

// Initializes the LCD and Keypad
void Calculator::begin() {
    lcd->createChar('\x03', SQUARE_ROOT);
    lcd->cursor();
}

// Run Function when changing state to calculator
void Calculator::EnterCalculator() {
    *power = 0;
    ToggleDisplay();
}

// Public Input Function. Runs in the Loop
void Calculator::AcceptInput() {
    if (*keyPressed) {
        *keyPressed = false;
        KeyCheck();
    }
}

// Helper Functions
// Defines which character is an operator
inline bool Calculator::IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Defines which character is a function
inline bool Calculator::IsFunction(char f) {
    return f == 'S';
}

// Defines which operator is a multiplier. Allows expressions like 5*-2
inline bool Calculator::IsMultiplier(char c) {
    return c == '+' || c == '-';
}

// Defines Precedence for BODMAS/PEMDAS
inline byte Calculator::Precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == 'S')
        return 3;
    return 0;
}

// Converts Double To String
String Calculator::DoubleToString(double d) {
    String str = String(d, MAX_DECIMALS);
    byte i = str.length() - 1;
    // Removes trailing zeros
    for (; i >= 0; i--) {
        if (str[i] != '0' || str[i] == '.') break;
    }
    // Makes sure the decimal is removed if it is a whole number
    str = (str[i] == '.') ? str.substring(0, i) : str.substring(0, i + 1);
    return str;
}

// Stack Functions
// Pushes value to the a given stack
void Calculator::PushOperator(char op) {
    operatorStack[operatorStackTop] = op;
    operatorStackTop++;
}

void Calculator::PushDigit(double digit) {
    digitStack[digitStackTop] = digit;
    digitStackTop++;
}

void Calculator::PushDigit(String& digit) {
    if (digit.length() > 0) {
        PushDigit(digit.toFloat());
        digit = "";
    }
}

// Pops value from the a given stack
void Calculator::PopOperator() {
    operatorStackTop--;
}

void Calculator::PopDigit() {
    digitStackTop--;
}

// Returns value from the a given stack
char Calculator::PeekOperator() {
    return operatorStack[operatorStackTop - 1];
}

double Calculator::PeekDigit() {
    return digitStack[digitStackTop - 1];
}

// Resets the stacks for future use
void Calculator::ClearStacks() {
    operatorStackTop = 0;
    digitStackTop = 0;
}

bool Calculator::Calculate() {
    ClearStacks();
    char c = ' ';
    String str = "";
    double number1 = 0.0;
    double number2 = 0.0;
    byte i = 0;
    bool decimalFlag = false;

    if (IsSyntaxError()) {
        return false;
    }

    if (IsMultiplier(expression[0])) {
        str += expression[0];
        i = 1;
    }

    for (; i < expression.length(); i++) {
        c = expression[i];

        if (isDigit(c) || c == '.') {
            // Check if Expression is Formatted Correctly. Cannot Have ) without Operator in Between. The previous character cannot also be a function or percentage
            if (i != 0 && (IsFunction(expression[i - 1]) || expression[i - 1] == PERCENTAGE || expression[i - 1] == ')')) {
                return false;
            }

            // Check For Decimal and Multiple Decimal Points
            if (decimalFlag) {
                if (c == '.') {
                    return false;
                }
            } else {
                // Add a 0 if the first character is a decimal

                if (c == '.') {
                    decimalFlag = true;
                    if (str.length() == 0) str += '0';
                }
            }

            str += c;

        } else if (c == PERCENTAGE) {
            // Check if Expression is Formatted Correctly. Only can have a digit , ) or . before percentage
            if (i != 0 && !(isDigit(expression[i - 1]) || expression[i - 1] == ')' || expression[i - 1] == '.')) {
                return false;
            }

            // Push to Digit Stack if Previous Token was a Number
            PushDigit(str);
            decimalFlag = false;

            digitStack[digitStackTop - 1] *= 0.01;
        } else if (c == '(') {
            // Check if Expression is Formatted Correctly. Cannot Have digit, % or ) without Operator in Between.
            if (i != 0 && (isDigit(expression[i - 1]) || expression[i - 1] == ')' || expression[i - 1] == PERCENTAGE)) {
                return false;
            }

            // Token Code End

            PushOperator('(');

        } else if (c == ')') {
            // Check if Expression is Formatted Correctly. Cannot Have operator, function or ( before a closing parenthesis.
            if (i != 0 && (IsOperator(expression[i - 1]) || expression[i - 1] == '(' || IsFunction(expression[i - 1]))) {
                return false;
            }

            // Push to Digit Stack if Previous Token was a Number
            PushDigit(str);
            decimalFlag = false;

            // Token Code End

            while (PeekOperator() != '(') {
                ApplyOperation(number1, number2);
            }

            PopOperator();

        } else if (IsOperator(c)) {
            // Check if Expression is Formatted Correctly. Cannot Have operator, function or ( before another operator.
            if (i != 0 && (IsOperator(expression[i - 1]) || expression[i - 1] == '(') || IsFunction(expression[i - 1])) {
                // Check if Number is Negative Number
                if (IsMultiplier(c) && str.length() == 0) {
                    str += c;
                    continue;
                } else {
                    return false;
                }
            }

            // Push to Digit Stack if Previous Token was a Number
            PushDigit(str);
            decimalFlag = false;

            // Token Code End

            while (operatorStackTop > 0 && Precedence(PeekOperator()) >= Precedence(c)) {
                ApplyOperation(number1, number2);
            }

            PushOperator(c);
        } else if (IsFunction(c)) {
            // Check if Expression is Formatted Correctly. Can only have operator or ( before a function
            if (i != 0 && !(IsOperator(expression[i - 1]) || expression[i - 1] == '(')) {
                return false;
            }

            // Check if Expression is Formatted Correctly. Can only have bracket after a function
            if (i != expression.length() - 1 && expression[i + 1] != '(') {
                return false;
            }

            // Token Code End
            PushOperator(c);
        }
    }

    // Push if Last Token is a Number
    if (str.length() > 0) {
        PushDigit(str);
    }

    // Clear Operator Stack
    while (operatorStackTop > 0) {
        ApplyOperation(number1, number2);
    }

    // Answer is the remaining digit in the digit stack
    answer = PeekDigit();
    return true;
}

void Calculator::ApplyOperation(double& num1, double& num2) {
    // Get a digit from the stack
    num2 = PeekDigit();
    PopDigit();

    // If it is a function only one digit is needed so second digit is not needed. If it is an operator then two digits are needed.
    // So second from the stack is acquired
    if (!IsFunction(PeekOperator())) {
        num1 = PeekDigit();
        PopDigit();
    }

    // Apply the operation
    switch (PeekOperator()) {
        case '+':
            PushDigit(num1 + num2);
            break;
        case '-':
            PushDigit(num1 - num2);
            break;
        case '*':
            PushDigit(num1 * num2);
            break;
        case '/':
            PushDigit(num1 / num2);
            break;
        case 'S':
            PushDigit(sqrt(num2));
            break;
        default:
            PushDigit(0.0);
            break;
    }

    // Remove operator from the operatorStack
    PopOperator();
}

void Calculator::KeyCheck() {
    // Toggle On/Off
    if (*key == 'O') ToggleDisplay();

    // If Off do Nothing
    if (!*power) return;

    switch (*key) {
        case '0' ... '9':
        case '+':
        case '-':
        case '*':
        case '/':
        case '.':
        case PERCENTAGE:
            InsertKey();
            break;
        // Open Brackets
        case '(':
            if (InsertKey())
                // Code to keep track oi the brackets in the expression are all closed
                brackets++;
            break;
        // Close Brackets
        case ')':
            if (InsertKey())
                // Code to keep track oi the brackets in the expression are all closed
                brackets--;
            break;
        // Square Root
        case 'S':
            if (InsertKey("S("))
                // Code to keep track oi the brackets in the expression are all closed
                brackets++;
            break;
        // +/-
        case '_':
            InsertKey("-");
            break;
        // Clear everything
        case 'E':
            Reset();
            break;
        // Backspace
        case 'C':
            Backspace();
            break;
        // Left
        case '<':
            MoveLeft();
            break;
        // Right
        case '>':
            MoveRight();
            break;
        // Add Answer to Expression
        case 'A':
            InsertKey(DoubleToString(answer));
            break;
        // Add Answer to Memory
        case 'a':
            // If there is an expression calculate it first
            if (expression.length() != 0) {
                // If there is an error do not add to memory and Display Error
                if (!Calculate()) {
                    DisplayError();
                    return;
                }
            }
            memory += answer;
            Reset();
            break;
        // Subtract Answer from Memory
        case 's':
            // If there is an expression calculate it first
            if (expression.length() != 0) {
                // If there is an error do not add to memory and Display Error
                if (!Calculate()) {
                    DisplayError();
                    return;
                }
            }
            memory -= answer;
            Reset();
            break;
        // Add Memory to Expression
        case 'r':
            InsertKey(DoubleToString(memory));
            break;
        // Clear Memory
        case 'c':
            memory = 0.0;
            break;
        // Calculate Answer
        case '=':
            // Calculate and if there is an error display error
            if (!Calculate()) {
                DisplayError();
                return;
            }
            // Otherwise display answer
            DisplayAnswer();
            Reset();
            return;
        // Go To Menu
        case 'M':
            Reset();
            StateChange(0);
            break;
        default:
            break;
    }
    DisplayExpression();
}

void Calculator::ToggleDisplay() {
    // Toggle Power
    *power = !*power;
    lcd->clear();
    digitalWrite(LCD_ANODE, *power);
    Reset();
    // Turn off cursor if power is off
    if (*power) {
        lcd->cursor();
    } else {
        lcd->noCursor();
    }
}

bool Calculator::InsertKey(String&& str) {
    // If there is no space do not insert.
    if (expression.length() + str.length() > MAX_EXPRESSION_LENGTH) return false;

    // Insert string to the left of the cursor
    temp = expression.substring(drawLocation + cursorPosition, expression.length());
    expression = expression.substring(0, drawLocation + cursorPosition) + str + temp;
    // Move right for every character inserted
    for (byte i = 0; i < str.length(); i++) {
        MoveRight();
    }
    return true;
}

bool Calculator::InsertKey() {
    // If there is no space do not insert.
    if (expression.length() + 1 > MAX_EXPRESSION_LENGTH) return false;

    // Insert key to the left of the cursor
    temp = expression.substring(drawLocation + cursorPosition, expression.length());
    expression = expression.substring(0, drawLocation + cursorPosition) + *key + temp;
    // Move right as the key is inserted
    MoveRight();
    return true;
}

void Calculator::Backspace() {
    // Do not backspace if cursor is at the start
    if (cursorPosition + drawLocation == 0) return;

    // Code to keep track oi the brackets in the expression are all closed
    if (expression[cursorPosition + drawLocation - 1] == '(') {
        brackets--;
    } else if (expression[cursorPosition + drawLocation - 1] == ')') {
        brackets++;
    }

    // Remove character to the left of the cursor
    temp = expression.substring(drawLocation + cursorPosition, expression.length());
    expression = expression.substring(0, drawLocation + cursorPosition - 1) + temp;

    // Move left as the character is removed
    if (!drawLocation)
        MoveLeft();
    else {
        // If the cursor location is beyond the display then move the display left
        drawLocation--;
    }
}

void Calculator::MoveLeft() {
    // Clamp upperCursorLimit to SCREEN_LENGTH
    upperCursorLimit = (expression.length() < SCREEN_LENGTH) ? expression.length() : SCREEN_LENGTH;

    // If cursor is not at the start move left
    if (cursorPosition > LOWER_CURSOR_LIMIT) {
        cursorPosition--;
    } else {
        // If cursor is at the start move the display left until at the beginning
        if (drawLocation > LOWER_CURSOR_LIMIT) {
            drawLocation--;
        }
    }
}

void Calculator::MoveRight() {
    // Clamp upperCursorLimit to SCREEN_LENGTH
    upperCursorLimit = (expression.length() < SCREEN_LENGTH) ? expression.length() : SCREEN_LENGTH;

    // If cursor is not at the end move right
    if (cursorPosition < upperCursorLimit) {
        cursorPosition++;
    } else {
        // If cursor is at the end move the display right until at the screen is filled with the last section of the expression
        if (cursorPosition == (SCREEN_LENGTH) && drawLocation < (expression.length() - (SCREEN_LENGTH))) {
            drawLocation++;
        }
    }
}

void Calculator::DisplayAnswer() {
    // Display answer
    lcd->clear();
    lcd->setCursor(0, 1);
    lcd->print(DoubleToString(answer));
}

void Calculator::DisplayError() {
    // Display error
    lcd->clear();
    lcd->setCursor(0, 1);
    lcd->print(FORMAT_ERROR);
}

void Calculator::DisplayExpression() {
    lcd->clear();
    lcd->setCursor(0, 0);
    for (byte i = drawLocation; i < drawLocation + upperCursorLimit + 1; i++) {
        // Print special character for square root
        if (IsFunction(expression[i])) {
            lcd->print('\x03');
            continue;
        }
        lcd->print(expression[i]);
    }
    lcd->setCursor(cursorPosition, 0);
}

void Calculator::Reset() {
    // Reset all variables responsible for cursor and display
    expression = "";
    cursorPosition = 0;
    brackets = 0;
    drawLocation = 0;
}

bool Calculator::IsSyntaxError() {
    // If Empty Expression Return Empty String
    if (expression.length() == 0) {
        return true;
    }

    // If there all brackets are not closed return true
    if (brackets) {
        return true;
    }

    // Cannot Start with Operator or ) or percentage
    if (IsOperator(expression[0]) || expression[0] == ')' || expression[0] == PERCENTAGE) {
        if (!IsMultiplier(expression[0])) {
            return true;
        }
    }

    // Cannot End with Operator, function or (
    if ((IsOperator(expression[expression.length() - 1]) || expression[expression.length() - 1] == '(') || IsFunction(expression[expression.length() - 1])) {
        return true;
    }

    // No Syntax Errors
    return false;
}