/*
 ===============================================================================
 File: 04_recursive_iterative_operations.c
 Description: Performance comparison between recursive and iterative methods
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Factorial calculation (recursive vs iterative)
 - Fibonacci sequence generation (recursive vs iterative)
 - Sum of natural numbers (recursive vs iterative)
 - Power computation (recursive vs iterative)
 - Execution time measurement
 - Call/iteration counting
 - Performance recommendations based on results
 ===============================================================================
*/

#include <stdio.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define EXIT_OPTION 5
#define MIN_SPEED_DIFF 1.5

static const char *MSG_MENU_TITLE = "=== Recursive vs Iterative Operations ===\n";
static const char *MSG_MENU_OPTIONS =
    "1. Factorial\n2. Fibonacci\n3. Sum of naturals\n4. Power\n5. Exit\n";
static const char *MSG_GOODBYE = "Thank you for using the program!\n";

static const char *INPUT_OPTION = "Select operation: ";
static const char *INPUT_TERM = "Enter term (n): ";
static const char *INPUT_BASE = "Enter base: ";
static const char *INPUT_EXPONENT = "Enter exponent: ";

static const char *LABEL_RECURSIVE = "\nRecursive method:\n";
static const char *LABEL_ITERATIVE = "\nIterative method:\n";
static const char *LABEL_COMPARISON = "\nComparison:\n";

static const char *FMT_RESULT_REC =
    "  - Result(%d) = %.0f\n  - Time: %.8f seconds\n  - Recursive calls: %ld\n";
static const char *FMT_RESULT_ITE =
    "  - Result(%d) = %.0f\n  - Time: %.8f seconds\n  - Iterations: %ld\n";
static const char *FMT_COMP_SPEED_ITE = "  - Iterative method was %.2fx faster\n";
static const char *FMT_COMP_SPEED_REC = "  - Recursive method was %.2fx faster\n";
static const char *FMT_COMP_CALLS = "  - Recursive method made %ld calls\n";
static const char *FMT_RECOMMEND = "  - Recommendation: %s\n\n";

static const char *RECOMMEND_ITERATIVE = "Use iterative method for large values";
static const char *RECOMMEND_NEGLIGIBLE = "Negligible difference";

static const char *ERR_MSG_INVALID = "Error: Invalid input.\n\n";

long call_count = 0;

void clear_input_buffer(void);
int read_integer(int *value);
int read_double(double *value);
double factorial_rec(int n);
double factorial_ite(int n, long *iters);
double fibonacci_rec(int n);
double fibonacci_ite(int n, long *iters);
double sum_natural_rec(int n);
double sum_natural_ite(int n, long *iters);
double power_rec(double base, int exp);
double power_ite(double base, int exp, long *iters);
void run_comparison(int option);

int main(void) {
  int option = 0;

  while (TRUE) {
    printf("%s", MSG_MENU_TITLE);
    printf("%s", MSG_MENU_OPTIONS);
    printf("%s", INPUT_OPTION);

    if (!read_integer(&option)) {
      printf("%s", ERR_MSG_INVALID);
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("%s", MSG_GOODBYE);
      break;
    }

    if (option < 1 || option > 5) {
      printf("%s", ERR_MSG_INVALID);
      continue;
    }

    run_comparison(option);
  }

  return 0;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
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

void run_comparison(int option) {
  int n = 0, exp = 0;
  double base = 0;
  double res_rec, res_ite;
  long iters = 0;
  clock_t start, end;
  double time_rec, time_ite;

  if (option == 4) {
    printf("%s", INPUT_BASE);
    read_double(&base);
    printf("%s", INPUT_EXPONENT);
    read_integer(&exp);
    n = exp;
  } else {
    printf("%s", INPUT_TERM);
    read_integer(&n);
  }

  call_count = 0;
  start = clock();
  if (option == 1)
    res_rec = factorial_rec(n);
  else if (option == 2)
    res_rec = fibonacci_rec(n - 1);
  else if (option == 3)
    res_rec = sum_natural_rec(n);
  else
    res_rec = power_rec(base, exp);
  end = clock();
  time_rec = (double)(end - start) / CLOCKS_PER_SEC;

  iters = 0;
  start = clock();
  if (option == 1)
    res_ite = factorial_ite(n, &iters);
  else if (option == 2)
    res_ite = fibonacci_ite(n - 1, &iters);
  else if (option == 3)
    res_ite = sum_natural_ite(n, &iters);
  else
    res_ite = power_ite(base, exp, &iters);
  end = clock();
  time_ite = (double)(end - start) / CLOCKS_PER_SEC;

  printf("%s", LABEL_RECURSIVE);
  printf(FMT_RESULT_REC, n, res_rec, time_rec, call_count);

  printf("%s", LABEL_ITERATIVE);
  printf(FMT_RESULT_ITE, n, res_ite, time_ite, iters);

  printf("%s", LABEL_COMPARISON);

  double speed_factor = 0.0;
  if (time_rec > time_ite && time_ite > 0) {
    speed_factor = time_rec / time_ite;
  } else if (time_ite > time_rec && time_rec > 0) {
    speed_factor = time_ite / time_rec;
  }

  if (speed_factor >= MIN_SPEED_DIFF) {
    if (time_ite < time_rec) {
      printf(FMT_COMP_SPEED_ITE, speed_factor);
    } else {
      printf(FMT_COMP_SPEED_REC, speed_factor);
    }
  }

  printf(FMT_COMP_CALLS, call_count);
  printf(FMT_RECOMMEND, (time_ite < time_rec) ? RECOMMEND_ITERATIVE : RECOMMEND_NEGLIGIBLE);
}

double factorial_rec(int n) {
  call_count++;
  if (n <= 1)
    return 1;
  return n * factorial_rec(n - 1);
}

double factorial_ite(int n, long *iters) {
  double res = 1;
  for (int i = 2; i <= n; i++) {
    res *= i;
    (*iters)++;
  }
  return res;
}

double fibonacci_rec(int n) {
  call_count++;
  if (n <= 1)
    return n;
  return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
}

double fibonacci_ite(int n, long *iters) {
  if (n <= 1)
    return n;
  double a = 0, b = 1, res = 0;
  for (int i = 2; i <= n; i++) {
    res = a + b;
    a = b;
    b = res;
    (*iters)++;
  }
  return b;
}

double sum_natural_rec(int n) {
  call_count++;
  if (n <= 0)
    return 0;
  return n + sum_natural_rec(n - 1);
}

double sum_natural_ite(int n, long *iters) {
  double res = 0;
  for (int i = 1; i <= n; i++) {
    res += i;
    (*iters)++;
  }
  return res;
}

double power_rec(double base, int exp) {
  call_count++;
  if (exp == 0)
    return 1;
  return base * power_rec(base, exp - 1);
}

double power_ite(double base, int exp, long *iters) {
  double res = 1;
  for (int i = 0; i < exp; i++) {
    res *= base;
    (*iters)++;
  }
  return res;
}
