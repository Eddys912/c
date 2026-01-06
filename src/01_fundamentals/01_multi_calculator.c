#include <stdio.h>

static const char *MSG_MENU_TITLE = "=== Scientific Calculator ===\n\n";
static const char *MSG_MENU_OPTIONS = "1. Addition\n"
                                      "2. Subtraction\n"
                                      "3. Multiplication\n"
                                      "4. Division\n"
                                      "5. Power\n"
                                      "6. Square Root\n"
                                      "7. Factorial\n"
                                      "8. Exit\n";
static const char *MSG_MENU_ADDITION = "ADDITION";
static const char *MSG_MENU_SUBTRACTION = "SUBTRACTION";
static const char *MSG_MENU_MULTIPLICATION = "MULTIPLICATION";
static const char *MSG_MENU_DIVISION = "DIVISION";
static const char *MSG_MENU_POWER = "POWER";
static const char *MSG_MENU_SQRT = "SQUARE ROOT";
static const char *MSG_MENU_FACTORIAL = "FACTORIAL";
static const char *MSG_GOODBYE = "Thank you for using the calculator!\n";

static const char *INPUT_OPTION = "\nSelect an option: ";
static const char *INPUT_FIRST_NUMBER = "Enter the first number: ";
static const char *INPUT_SECOND_NUMBER = "Enter the second number: ";
static const char *INPUT_NUMBER = "Enter the number: ";
static const char *INPUT_BASE = "Enter the base: ";
static const char *INPUT_EXPONENT = "Enter the exponent (integer): ";

static const char *FMT_OPERATION_HEADER = "\n  === %s === \n\n";
static const char *FMT_RESULT_FLOAT = "\n  - Result: %.6f\n\n";
static const char *FMT_RESULT_INT = "\n  - Result: %.0f\n\n";

static const char *ERR_MSG_INVALID_OPTION = "Invalid option. Please try again.\n\n";
static const char *ERR_MSG_DIV_ZERO = "Error: Cannot divide by zero.\n\n";
static const char *ERR_MSG_SQRT_NEGATIVE =
    "Error: Cannot calculate square root of negative number.\n\n";
static const char *ERR_MSG_FACT_NEGATIVE =
    "Error: Factorial only defined for non-negative integers.\n\n";
static const char *ERR_MSG_FACT_NON_INTEGER = "Error: Factorial only calculated for integers.\n\n";
static const char *ERR_MSG_INPUT_INVALID = "Error: Invalid input. Please enter a valid number.\n\n";

#define SQRT_ITERATIONS 20
#define EXIT_OPTION 8
#define FALSE 0
#define TRUE 1

typedef enum {
  OP_ADDITION = 1,
  OP_SUBTRACTION,
  OP_MULTIPLICATION,
  OP_DIVISION,
  OP_POWER,
  OP_SQUARE_ROOT,
  OP_FACTORIAL,
  OP_EXIT
} MenuOption;

typedef enum {
  STATUS_SUCCESS = 0,
  STATUS_ERROR_DIV_ZERO,
  STATUS_ERROR_SQRT_NEGATIVE,
  STATUS_ERROR_FACT_NEGATIVE,
  STATUS_ERROR_FACT_NON_INTEGER
} OperationStatus;

typedef struct {
  double value;
  OperationStatus status;
} OperationResult;

void clear_input_buffer(void);
int is_integer(double num);
int read_double(double *value);
int read_integer(int *value);
OperationResult add(double a, double b);
OperationResult subtract(double a, double b);
OperationResult multiply(double a, double b);
OperationResult divide(double a, double b);
OperationResult power(double base, int exponent);
OperationResult sqroot(double num);
OperationResult factorial(double num);
void display_menu(void);
void display_operation_header(const char *operation_name);
void display_result(OperationResult result, int as_integer);
void display_error(OperationStatus status);
void handle_addition(void);
void handle_subtraction(void);
void handle_multiplication(void);
void handle_division(void);
void handle_power(void);
void handle_square_root(void);
void handle_factorial(void);
void run_interactive_menu(void);

int main(void) {
  run_interactive_menu();
  return 0;
}

void clear_input_buffer(void) {
  while (getchar() != '\n')
    ;
}

int is_integer(double num) { return num == (int)num; }

int read_double(double *value) {
  if (scanf("%lf", value) != 1) {
    printf("%s", ERR_MSG_INPUT_INVALID);
    clear_input_buffer();
    return FALSE;
  }
  return TRUE;
}

int read_integer(int *value) {
  if (scanf("%d", value) != 1) {
    printf("%s", ERR_MSG_INPUT_INVALID);
    clear_input_buffer();
    return FALSE;
  }
  return TRUE;
}

OperationResult add(double a, double b) { return (OperationResult){a + b, STATUS_SUCCESS}; }

OperationResult subtract(double a, double b) { return (OperationResult){a - b, STATUS_SUCCESS}; }

OperationResult multiply(double a, double b) { return (OperationResult){a * b, STATUS_SUCCESS}; }

OperationResult divide(double a, double b) {
  if (b == 0.0)
    return (OperationResult){0.0, STATUS_ERROR_DIV_ZERO};
  return (OperationResult){a / b, STATUS_SUCCESS};
}

OperationResult power(double base, int exponent) {
  OperationResult result = {1.0, STATUS_SUCCESS};

  if (exponent < 0) {
    base = 1.0 / base;
    exponent = -exponent;
  }

  while (exponent--) {
    result.value *= base;
  }

  return result;
}

OperationResult sqroot(double num) {
  if (num < 0.0)
    return (OperationResult){0.0, STATUS_ERROR_SQRT_NEGATIVE};

  if (num == 0.0)
    return (OperationResult){0.0, STATUS_SUCCESS};

  double res = num;
  for (int i = 0; i < SQRT_ITERATIONS; i++) {
    res = 0.5 * (res + num / res);
  }

  return (OperationResult){res, STATUS_SUCCESS};
}

OperationResult factorial(double num) {
  if (num < 0.0)
    return (OperationResult){0.0, STATUS_ERROR_FACT_NEGATIVE};

  if (!is_integer(num))
    return (OperationResult){0.0, STATUS_ERROR_FACT_NON_INTEGER};

  int n = (int)num;
  double res = 1.0;

  for (int i = 2; i <= n; i++) {
    res *= i;
  }

  return (OperationResult){res, STATUS_SUCCESS};
}

void display_menu(void) {
  printf("%s", MSG_MENU_TITLE);
  printf("%s", MSG_MENU_OPTIONS);
}

void display_operation_header(const char *operation_name) {
  printf(FMT_OPERATION_HEADER, operation_name);
}

void display_result(OperationResult result, int as_integer) {
  if (result.status == STATUS_SUCCESS) {
    const char *format = as_integer ? FMT_RESULT_INT : FMT_RESULT_FLOAT;
    printf(format, result.value);
  }
}

void display_error(OperationStatus status) {
  switch (status) {
  case STATUS_ERROR_DIV_ZERO:
    printf("%s", ERR_MSG_DIV_ZERO);
    break;
  case STATUS_ERROR_SQRT_NEGATIVE:
    printf("%s", ERR_MSG_SQRT_NEGATIVE);
    break;
  case STATUS_ERROR_FACT_NEGATIVE:
    printf("%s", ERR_MSG_FACT_NEGATIVE);
    break;
  case STATUS_ERROR_FACT_NON_INTEGER:
    printf("%s", ERR_MSG_FACT_NON_INTEGER);
    break;
  default:
    break;
  }
}

void handle_addition(void) {
  double num1, num2;

  display_operation_header(MSG_MENU_ADDITION);
  printf("%s", INPUT_FIRST_NUMBER);
  if (!read_double(&num1))
    return;

  printf("%s", INPUT_SECOND_NUMBER);
  if (!read_double(&num2))
    return;

  OperationResult result = add(num1, num2);
  display_result(result, FALSE);
}

void handle_subtraction(void) {
  double num1, num2;

  display_operation_header(MSG_MENU_SUBTRACTION);
  printf("%s", INPUT_FIRST_NUMBER);
  if (!read_double(&num1))
    return;

  printf("%s", INPUT_SECOND_NUMBER);
  if (!read_double(&num2))
    return;

  OperationResult result = subtract(num1, num2);
  display_result(result, FALSE);
}

void handle_multiplication(void) {
  double num1, num2;

  display_operation_header(MSG_MENU_MULTIPLICATION);
  printf("%s", INPUT_FIRST_NUMBER);
  if (!read_double(&num1))
    return;

  printf("%s", INPUT_SECOND_NUMBER);
  if (!read_double(&num2))
    return;

  OperationResult result = multiply(num1, num2);
  display_result(result, FALSE);
}

void handle_division(void) {
  double num1, num2;

  display_operation_header(MSG_MENU_DIVISION);
  printf("%s", INPUT_FIRST_NUMBER);
  if (!read_double(&num1))
    return;

  printf("%s", INPUT_SECOND_NUMBER);
  if (!read_double(&num2))
    return;

  OperationResult result = divide(num1, num2);

  if (result.status != STATUS_SUCCESS) {
    display_error(result.status);
  } else {
    display_result(result, FALSE);
  }
}

void handle_power(void) {
  double base;
  int exponent;

  display_operation_header(MSG_MENU_POWER);
  printf("%s", INPUT_BASE);
  if (!read_double(&base))
    return;

  printf("%s", INPUT_EXPONENT);
  if (!read_integer(&exponent))
    return;

  OperationResult result = power(base, exponent);
  display_result(result, FALSE);
}

void handle_square_root(void) {
  double num;

  display_operation_header(MSG_MENU_SQRT);
  printf("%s", INPUT_NUMBER);
  if (!read_double(&num))
    return;

  OperationResult result = sqroot(num);

  if (result.status != STATUS_SUCCESS) {
    display_error(result.status);
  } else {
    display_result(result, FALSE);
  }
}

void handle_factorial(void) {
  double num;

  display_operation_header(MSG_MENU_FACTORIAL);
  printf("%s", INPUT_NUMBER);
  if (!read_double(&num))
    return;

  OperationResult result = factorial(num);

  if (result.status != STATUS_SUCCESS) {
    display_error(result.status);
  } else {
    display_result(result, TRUE);
  }
}

void run_interactive_menu(void) {
  unsigned int option;

  while (TRUE) {
    display_menu();
    printf("%s", INPUT_OPTION);

    if (scanf("%u", &option) != 1) {
      printf("%s", ERR_MSG_INVALID_OPTION);
      clear_input_buffer();
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("%s", MSG_GOODBYE);
      break;
    }

    switch (option) {
    case OP_ADDITION:
      handle_addition();
      break;
    case OP_SUBTRACTION:
      handle_subtraction();
      break;
    case OP_MULTIPLICATION:
      handle_multiplication();
      break;
    case OP_DIVISION:
      handle_division();
      break;
    case OP_POWER:
      handle_power();
      break;
    case OP_SQUARE_ROOT:
      handle_square_root();
      break;
    case OP_FACTORIAL:
      handle_factorial();
      break;
    default:
      printf("%s", ERR_MSG_INVALID_OPTION);
      break;
    }
  }
}
