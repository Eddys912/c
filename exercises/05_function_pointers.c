#include <stdio.h>

typedef double (*Operation)(double);

double square(double n);
double cubic(double n);
void process_number(double val, Operation op, const char *msg);

int main() {
  double number;

  printf("=== Function Pointers ===\n\n");
  printf("Enter a number: ");
  if (scanf("%lf", &number) != 1)
    return 1;

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
