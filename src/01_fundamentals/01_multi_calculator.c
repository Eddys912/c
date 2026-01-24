/*
 ===============================================================================
 File: 01_multi_calculator.c
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

void clear_input_buffer(void);
int read_double(double *value);
int read_integer(int *value);
int read_two_numbers(double *num1, double *num2);
double basic_operation(int option, double num1, double num2);
double power(double base, int exponent);
double sqroot(double num);
double factorial(int num);

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

    double num1, num2;

    switch (option) {
    case 1:
    case 2:
    case 3:
      if (!read_two_numbers(&num1, &num2))
        break;
      printf("\n  - Result: %.2f\n\n", basic_operation(option, num1, num2));
      break;
    case 4:
      if (!read_two_numbers(&num1, &num2))
        break;
      if (num2 != 0.0)
        printf("\n  - Result: %.2f\n\n", num1 / num2);
      else
        printf("Error: Cannot divide by zero.\n\n");
      break;
    case 5:
      printf("\nEnter base: ");
      if (!read_double(&num1))
        break;
      printf("Enter exponent (integer): ");
      int exponent;
      if (!read_integer(&exponent))
        break;
      printf("\n  - Result: %.2f\n\n", power(num1, exponent));
      break;
    case 6:
      printf("\nEnter number: ");
      if (!read_double(&num1))
        break;
      if (num1 >= 0.0)
        printf("\n  - Result: %.4f\n\n", sqroot(num1));
      else
        printf("Error: Negative numbers not allowed for this operation.\n\n");
      break;
    case 7:
      printf("\nEnter number: ");
      if (!read_double(&num1))
        break;
      if (num1 < 0.0) {
        printf("Error: Negative numbers not allowed for this operation.\n\n");
      } else if (num1 > MAX_FACTORIAL) {
        printf("Error: Number too large for factorial (max 170).\n\n");
      } else {
        printf("\n  - Result: %.0f\n\n", factorial((int)num1));
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
    printf("Error: That is not a valid number. Try again.\n\n");
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
  printf("\nEnter first number: ");
  if (!read_double(num1))
    return FALSE;
  printf("Enter second number: ");
  if (!read_double(num2))
    return FALSE;
  return TRUE;
}

double basic_operation(int option, double num1, double num2) {
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
