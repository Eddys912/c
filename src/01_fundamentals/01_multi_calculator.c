#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define EXIT_OPTION 8
#define SQRT_ITERATIONS 20
#define MAX_FACTORIAL 170

static const char *MSG_MENU_TITLE = "=== Scientific Calculator ===\n\n";
static const char *MSG_MENU_OPTIONS = "1. Addition\n2. Subtract\n3. Multiply\n4. Divide\n5. Power\n"
                                      "6. Square Root\n7. Factorial\n8. Exit\n";
static const char *MSG_GOODBYE = "\nThank you for using the calculator!\n";

static const char *INPUT_OPTION = "Select an option: ";
static const char *INPUT_FIRST_NUMBER = "\nEnter first number: ";
static const char *INPUT_SECOND_NUMBER = "Enter second number: ";
static const char *INPUT_NUMBER = "\nEnter number: ";
static const char *INPUT_BASE = "\nEnter base: ";
static const char *INPUT_EXPONENT = "Enter exponent (integer): ";

static const char *FMT_RESULT_FLOAT = "\n  - Result: %.2f\n\n";
static const char *FMT_RESULT_PRECISION = "\n  - Result: %.4f\n\n";
static const char *FMT_RESULT_INT = "\n  - Result: %.0f\n\n";

static const char *ERR_MSG_INVALID_NUMBER = "Error: That is not a valid number. Try again.\n\n";
static const char *ERR_MSG_DIV_ZERO = "Error: Cannot divide by zero.\n\n";
static const char *ERR_MSG_NEGATIVE = "Error: Negative numbers not allowed for this operation.\n\n";
static const char *ERR_MSG_INVALID_OPTION = "Error: Invalid option. Please select 1-8.\n\n";
static const char *ERR_MSG_FACTORIAL_LIMIT = "Error: Number too large for factorial (max 170).\n\n";

void clear_input_buffer(void);
int read_double(double *value);
int read_integer(int *value);
int read_two_numbers(double *num1, double *num2);
double perform_basic_operation(int option, double num1, double num2);
double power(double base, int exponent);
double sqroot(double num);
double factorial(int num);

int main(void) {
  int option = 0;

  while (TRUE) {
    printf("%s", MSG_MENU_TITLE);
    printf("%s", MSG_MENU_OPTIONS);
    printf("%s", INPUT_OPTION);

    if (!read_integer(&option)) {
      printf("%s", ERR_MSG_INVALID_OPTION);
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("%s", MSG_GOODBYE);
      break;
    }

    if (option < 1 || option > 8) {
      printf("%s", ERR_MSG_INVALID_OPTION);
      continue;
    }

    double num1, num2;

    switch (option) {
    case 1:
    case 2:
    case 3:
      if (!read_two_numbers(&num1, &num2))
        break;
      printf(FMT_RESULT_FLOAT, perform_basic_operation(option, num1, num2));
      break;
    case 4:
      if (!read_two_numbers(&num1, &num2))
        break;
      if (num2 != 0.0)
        printf(FMT_RESULT_FLOAT, num1 / num2);
      else
        printf("%s", ERR_MSG_DIV_ZERO);
      break;
    case 5:
      printf("%s", INPUT_BASE);
      if (!read_double(&num1))
        break;
      printf("%s", INPUT_EXPONENT);
      int exponent;
      if (!read_integer(&exponent))
        break;
      printf(FMT_RESULT_FLOAT, power(num1, exponent));
      break;
    case 6:
      printf("%s", INPUT_NUMBER);
      if (!read_double(&num1))
        break;
      if (num1 >= 0.0)
        printf(FMT_RESULT_PRECISION, sqroot(num1));
      else
        printf("%s", ERR_MSG_NEGATIVE);
      break;
    case 7:
      printf("%s", INPUT_NUMBER);
      if (!read_double(&num1))
        break;
      if (num1 < 0.0) {
        printf("%s", ERR_MSG_NEGATIVE);
      } else if (num1 > MAX_FACTORIAL) {
        printf("%s", ERR_MSG_FACTORIAL_LIMIT);
      } else {
        printf(FMT_RESULT_INT, factorial((int)num1));
      }
      break;
    }
  }

  return 0;
}

void clear_input_buffer(void) {
  while (getchar() != '\n')
    ;
}

int read_double(double *value) {
  if (scanf("%lf", value) != 1) {
    printf("%s", ERR_MSG_INVALID_NUMBER);
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

int read_integer(int *value) {
  if (scanf("%d", value) != 1) {
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

int read_two_numbers(double *num1, double *num2) {
  printf("%s", INPUT_FIRST_NUMBER);
  if (!read_double(num1))
    return FALSE;
  printf("%s", INPUT_SECOND_NUMBER);
  if (!read_double(num2))
    return FALSE;
  return TRUE;
}

double perform_basic_operation(int option, double num1, double num2) {
  if (option == 1)
    return num1 + num2;
  else if (option == 2)
    return num1 - num2;
  else
    return num1 * num2;
}

double power(double base, int exponent) {
  double result = 1.0;
  int positive_exp = (exponent < 0) ? -exponent : exponent;

  for (int i = 0; i < positive_exp; i++) {
    result *= base;
  }

  return (exponent < 0) ? 1.0 / result : result;
}

double sqroot(double num) {
  if (num == 0.0)
    return 0.0;

  double result = num;
  for (int i = 0; i < SQRT_ITERATIONS; i++) {
    result = 0.5 * (result + num / result);
  }

  return result;
}

double factorial(int num) {
  double result = 1.0;
  for (int i = 2; i <= num; i++) {
    result *= i;
  }
  return result;
}
