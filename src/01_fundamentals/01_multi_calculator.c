/*
 ===============================================================================
 Exercise: 01_multi_calculator.c
 Description: Scientific calculator with interactive menu
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Basic arithmetic operations (add, subtract, multiply, divide)
 - Advanced operations (power, square root, factorial)
 - Input validation and error handling
 - Division by zero detection
 - Negative number validation for sqrt and factorial
 - Factorial limit checking (max 170)
 - Uses Newton-Raphson method for square root approximation
 ===============================================================================
*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define EXIT_OPTION 8
#define SQRT_ITERATIONS 20
#define MAX_FACTORIAL 170

typedef enum {
  SUCCESS,
  ERR_DIV_ZERO,
  ERR_NEGATIVE_SQRT,
  ERR_NEGATIVE_FACTORIAL,
  ERR_FACTORIAL_LIMIT,
  ERR_INVALID_OPTION
} Status;

void clear_input_buffer(void);
int read_integer(int *value);
int read_double(double *value);
int read_two_numbers(double *num1, double *num2);
void handle_error(Status status);
Status basic_operation(int option, double num1, double num2, double *result);
Status power(double base, int exponent, double *result);
Status sqroot(double num, double *result);
Status factorial(int num, double *result);

int main(void) {
  int option = 0;

  while (TRUE) {
    printf("=== Scientific Calculator ===\n\n");
    printf("1. Addition\n2. Subtract\n3. Multiply\n4. Divide\n"
           "5. Power\n6. Square Root\n7. Factorial\n8. Exit\n");
    printf("Select an option: ");

    if (!read_integer(&option)) {
      printf("Error: Invalid option. Please select 1-8.\n\n");
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("\nThank you for using the calculator!\n");
      break;
    }

    if (option < 1 || option > 8) {
      printf("Error: Invalid option. Please select 1-8.\n\n");
      continue;
    }

    double num1, num2, result;
    Status status;

    switch (option) {
    case 1:
    case 2:
    case 3:
    case 4:
      if (!read_two_numbers(&num1, &num2)) {
        printf("Error: Invalid input. Please enter valid numbers.\n\n");
        break;
      }
      status = basic_operation(option, num1, num2, &result);
      if (status == SUCCESS) {
        printf("\n  - Result: %.2f\n\n", result);
      } else {
        handle_error(status);
      }
      break;
    case 5:
      printf("\nEnter base: ");
      if (!read_double(&num1)){
        printf("Error: Invalid input. Please enter valid numbers.\n\n");
        break;
      }
      printf("Enter exponent (integer): ");
      int exponent;
      if (!read_integer(&exponent)){
        printf("Error: Invalid input. Please enter valid numbers.\n\n");
        break;
      }
      status = power(num1, exponent, &result);
      if (status == SUCCESS) {
        printf("\n  - Result: %.2f\n\n", result);
      } else {
        handle_error(status);
      }
      break;
    case 6:
      printf("\nEnter number: ");
      if (!read_double(&num1)){
        printf("Error: Invalid input. Please enter valid numbers.\n\n");
        break;
      }
      status = sqroot(num1, &result);
      if (status == SUCCESS) {
        printf("\n  - Result: %.4f\n\n", result);
      } else {
        handle_error(status);
      }
      break;
    case 7:
      printf("\nEnter number: ");
      if (!read_double(&num1)){
        printf("Error: Invalid input. Please enter valid numbers.\n\n");
        break;
      }
      status = factorial((int)num1, &result);
      if (status == SUCCESS) {
        printf("\n  - Result: %.0f\n\n", result);
      } else {
        handle_error(status);
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

int read_integer(int *value) {
  if (scanf("%d", value) != 1) {
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}
int read_double(double *value) {
  if (scanf("%lf", value) != 1) {
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

int read_two_numbers(double *num1, double *num2) {
  printf("\nEnter first number: ");
  if (!read_double(num1))
    return FALSE;
  printf("Enter second number: ");
  if (!read_double(num2))
    return FALSE;
  return TRUE;
}

void handle_error(Status status) {
  switch (status) {
  case ERR_DIV_ZERO:
    printf("Error: Cannot divide by zero.\n\n");
    break;
  case ERR_NEGATIVE_SQRT:
    printf("Error: Negative numbers not allowed for this operation.\n\n");
    break;
  case ERR_NEGATIVE_FACTORIAL:
    printf("Error: Negative numbers not allowed for this operation.\n\n");
    break;
  case ERR_FACTORIAL_LIMIT:
    printf("Error: Number too large for factorial (max 170).\n\n");
    break;
  case ERR_INVALID_OPTION:
    printf("Error: Invalid operation.\n\n");
    break;
  case SUCCESS:
    break;
  }
}

Status basic_operation(int option, double num1, double num2, double *result) {
  if (option == 1) {
    *result = num1 + num2;
    return SUCCESS;
  } else if (option == 2) {
    *result = num1 - num2;
    return SUCCESS;
  } else if (option == 3) {
    *result = num1 * num2;
    return SUCCESS;
  } else if (option == 4) {
    if (num2 == 0.0)
      return ERR_DIV_ZERO;
    *result = num1 / num2;
    return SUCCESS;
  }
  return ERR_INVALID_OPTION;
}

Status power(double base, int exponent, double *result) {
  double res = 1.0;
  int positive_exp = (exponent < 0) ? -exponent : exponent;

  for (int i = 0; i < positive_exp; i++) {
    res *= base;
  }

  *result = (exponent < 0) ? 1.0 / res : res;
  return SUCCESS;
}

Status sqroot(double num, double *result) {
  if (num < 0.0)
    return ERR_NEGATIVE_SQRT;
  if (num == 0.0) {
    *result = 0.0;
    return SUCCESS;
  }

  double res = num;
  for (int i = 0; i < SQRT_ITERATIONS; i++) {
    res = 0.5 * (res + num / res);
  }

  *result = res;
  return SUCCESS;
}

Status factorial(int num, double *result) {
  if (num < 0)
    return ERR_NEGATIVE_FACTORIAL;
  if (num > MAX_FACTORIAL)
    return ERR_FACTORIAL_LIMIT;

  double res = 1.0;
  for (int i = 2; i <= num; i++) {
    res *= i;
  }
  *result = res;
  return SUCCESS;
}
