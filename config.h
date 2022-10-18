#ifndef CONFIG
#define CONFIG
#pragma once

// Numbers, +*-/, Square Root(S), Backspace(C), Clear(E),Percentage(%), Memory Clear(c), Memory Add(a), Memory Subtract(s), Memory Read(r), On/Off(o), +/-(_), Decimal(.), =
// Menu(M), (), Left(<), Right(>), Ans(A)

#define NO_OF_ROWS 4
#define NO_OF_COLS 8

#define DEFAULT_PASSWORD "EEE20003"

#define MAX_EXPRESSION_LENGTH 250
#define NumberOfOperators 4
#define NumberOfFunctions 2
#define MAX_DECIMALS 4
#define FORMAT_ERROR "Syntax Error"

#define LOWER_CURSOR_LIMIT 0
#define SCREEN_LENGTH 16
#define LCD_ANODE 23
#define LCD_DATA_PINS 10, 9, 8, 7
#define LCD_RS 12
#define LCD_ENABLE 11
#define LCD_ROWS 2

#define TIMER_STATE_0_INSTRUCTIONS "1Start2Reset3Set"
#define TIMER_STATE_1_INSTRUCTIONS "1Stop"
#define TIMER_STATE_2_INSTRUCTIONS "=Save"
#define TIMER_INTERRUPT_TIME 7811

static const char OPERATORS[NumberOfOperators] = {'+', '-', '*', '/'};
static const char FUNCTIONS[NumberOfFunctions] = {'S'};
static const char PERCENTAGE = '%';
static const char MULTIPLIERS[] = {'+', '-'};

static byte rowPins[NO_OF_ROWS] = {18, 19, 2, 3};
static byte colPins[NO_OF_COLS] = {39, 41, 43, 45, 47, 49, 51, 53};
static char keys[NO_OF_ROWS * NO_OF_COLS] = {'O', '1', '2', '3', '+', 'S', '<', '>',
                                             'C', '4', '5', '6', '-', '_', '(', ')',
                                             'E', '7', '8', '9', '*', '%', 'r', 'c',
                                             'M', '.', '0', '=', '/', 'A', 'a', 's'};

static uint8_t SQUARE_ROOT[8] = {
    0b00111,
    0b00100,
    0b00100,
    0b00100,
    0b10100,
    0b01100,
    0b00100,
    0b00000,
};

#endif  // CONFIG