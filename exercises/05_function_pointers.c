#include <stdio.h>

typedef double (*Operation)(double);

double square(double n);
double cubic(double n);
void process_number(double val, Operation op, const char *msg);
void clear_input_buffer();

int main() {
  double number;

  printf("=== Function Pointers ===\n\n");

  printf("Enter a number: ");
  if (scanf("%lf", &number) != 1) {
    fprintf(stderr, "Error: Invalid input.\n");
    return 1;
  }
  clear_input_buffer();

  printf("\nProcessing number %.2f:\n", number);
  process_number(number, square, "Square");
  process_number(number, cubic, "Cubic");

  return 0;
}

double square(double n) { return n * n; }
double cubic(double n) { return n * n * n; }

void process_number(double val, Operation op, const char *msg) {
  double result = op(val);
  printf("  [Callback %-7s] Input: %.2f | Result: %.2f\n", msg, val, result);
}

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}
