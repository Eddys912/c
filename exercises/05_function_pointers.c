/*
 ===============================================================================
 Exercise: 05_function_pointers.c
 Description: Demonstrates function pointers as callbacks for operations
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Defines function pointer type for mathematical operations
 - Implements square and cubic operations
 - Applies operations via callback mechanism
 - Processes single input with multiple operations
 ===============================================================================
*/

#include <stdio.h>

#define TITLE "=== Function Pointers ===\n\n"
#define TITLE_PROCESSING_NUMBER "\nProcessing number %.2f:\n"

#define TEXT_RESULT_FORMAT "  [Callback %-7s] Input: %.2f | Result: %.2f\n"

#define CALL_FUNCTION_SQUARE "Square"
#define CALL_FUNCTION_CUBIC "Cubic"

#define INPUT_NUMBER "Enter a number: "

#define ERR_MSG_INVALID_INPUT "Error: Invalid input.\n"

#define SCANF_SUCCESS 1

typedef enum { SUCCESS = 0, ERROR_INVALID_INPUT = 1 } StatusCode;

typedef double (*Operation)(double);

void clear_input_buffer(void);
StatusCode read_number(const char *prompt, double *value);
double square(double n);
double cubic(double n);
void process_number(double val, Operation op, const char *label);

int main(void) {
  double number;

  printf(TITLE);

  if (read_number(INPUT_NUMBER, &number) != SUCCESS) {
    return ERROR_INVALID_INPUT;
  }

  printf(TITLE_PROCESSING_NUMBER, number);
  process_number(number, square, CALL_FUNCTION_SQUARE);
  process_number(number, cubic, CALL_FUNCTION_CUBIC);

  return SUCCESS;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

StatusCode read_number(const char *prompt, double *value) {
  printf("%s", prompt);

  if (scanf("%lf", value) != SCANF_SUCCESS) {
    fprintf(stderr, ERR_MSG_INVALID_INPUT);
    clear_input_buffer();
    return ERROR_INVALID_INPUT;
  }
  clear_input_buffer();

  return SUCCESS;
}

double square(double n) { return n * n; }

double cubic(double n) { return n * n * n; }

void process_number(double val, Operation op, const char *label) {
  double result = op(val);
  printf(TEXT_RESULT_FORMAT, label, val, result);
}
