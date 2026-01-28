/*
 ===============================================================================
 Exercise: 04_recursive_iterative_operations.c
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
#define EXIT_OPTION 5
#define MIN_SPEED_DIFF 1.5

typedef enum { SUCCESS, ERR_INVALID_INPUT, ERR_NEGATIVE_VAL, ERR_INVALID_OPTION } Status;

typedef struct {
  Status status;
  double value;
  long count;
} Result;

long g_call_count = 0;

void run_comparison(int option);

void show_menu(void);
void clear_input_buffer(void);
Status read_integer(int *value);
Status read_double(double *value);
void handle_error(Status status);

double factorial_rec_logic(int n);
double fibonacci_rec_logic(int n);
double sum_natural_rec_logic(int n);
double power_rec_logic(double base, int exp);

Result factorial_rec(int n);
Result factorial_ite(int n);
Result fibonacci_rec(int n);
Result fibonacci_ite(int n);
Result sum_natural_rec(int n);
Result sum_natural_ite(int n);
Result power_rec(double base, int exp);
Result power_ite(double base, int exp);

int main(void) {
  int option = 0;

  while (TRUE) {
    show_menu();

    if (read_integer(&option) != SUCCESS) {
      printf("Error: Invalid option. Please select 1-5.\n\n");
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("\nThank you for using the comparison tool!\n");
      break;
    }

    if (option < 1 || option > 5) {
      printf("Error: Invalid input.\n\n");
      continue;
    }

    run_comparison(option);
  }

  return 0;
}

void run_comparison(int option) {
  int n = 0, exp = 0;
  double base = 0;
  Result res_rec, res_ite;
  clock_t start, end;
  double time_rec, time_ite;

  if (option == 4) {
    printf("Enter base: ");
    if (read_double(&base) != SUCCESS) {
      handle_error(ERR_INVALID_INPUT);
      return;
    }
    printf("Enter exponent: ");
    if (read_integer(&exp) != SUCCESS) {
      handle_error(ERR_INVALID_INPUT);
      return;
    }
    n = exp;
  } else {
    printf("Enter term (n): ");
    if (read_integer(&n) != SUCCESS) {
      handle_error(ERR_INVALID_INPUT);
      return;
    }
  }

  start = clock();
  switch (option) {
  case 1:
    res_rec = factorial_rec(n);
    break;
  case 2:
    res_rec = fibonacci_rec(n);
    break;
  case 3:
    res_rec = sum_natural_rec(n);
    break;
  case 4:
    res_rec = power_rec(base, exp);
    break;
  default:
    return;
  }
  end = clock();
  time_rec = (double)(end - start) / CLOCKS_PER_SEC;

  if (res_rec.status != SUCCESS) {
    handle_error(res_rec.status);
    return;
  }

  start = clock();
  switch (option) {
  case 1:
    res_ite = factorial_ite(n);
    break;
  case 2:
    res_ite = fibonacci_ite(n);
    break;
  case 3:
    res_ite = sum_natural_ite(n);
    break;
  case 4:
    res_ite = power_ite(base, exp);
    break;
  default:
    return;
  }
  end = clock();
  time_ite = (double)(end - start) / CLOCKS_PER_SEC;

  printf("\nRecursive method:\n");
  printf("  - Result = %.0f\n  - Time: %.8f seconds\n  - Recursive calls: %ld\n", res_rec.value,
         time_rec, res_rec.count);

  printf("\nIterative method:\n");
  printf("  - Result = %.0f\n  - Time: %.8f seconds\n  - Iterations: %ld\n", res_ite.value,
         time_ite, res_ite.count);

  printf("\nComparison:\n");
  double speed_factor = 0.0;
  if (time_rec > time_ite && time_ite > 0)
    speed_factor = time_rec / time_ite;
  else if (time_ite > time_rec && time_rec > 0)
    speed_factor = time_ite / time_rec;

  if (speed_factor >= MIN_SPEED_DIFF)
    printf("  - %s method was %.2fx faster\n", (time_ite < time_rec) ? "Iterative" : "Recursive",
           speed_factor);
  else
    printf("  - Negligible speed difference\n");

  printf("  - Recommendation: %s\n\n", (time_ite < time_rec)
                                           ? "Use iterative method for efficiency"
                                           : "Either method yields similar performance");
}

void show_menu(void) {
  printf("=== Recursive vs Iterative Operations ===\n");
  printf("1. Factorial\n2. Fibonacci\n3. Sum of naturals\n4. Power\n5. Exit\n");
  printf("Select operation: ");
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

Status read_integer(int *value) {
  if (scanf("%d", value) != 1) {
    clear_input_buffer();
    return ERR_INVALID_INPUT;
  }
  clear_input_buffer();
  return SUCCESS;
}

Status read_double(double *value) {
  if (scanf("%lf", value) != 1) {
    clear_input_buffer();
    return ERR_INVALID_INPUT;
  }
  clear_input_buffer();
  return SUCCESS;
}

void handle_error(Status status) {
  switch (status) {
  case ERR_INVALID_INPUT:
    printf("Error: Invalid input. Please enter valid numbers.\n\n");
    break;
  case ERR_NEGATIVE_VAL:
    printf("Error: Operation not defined for negative values.\n\n");
    break;
  case ERR_INVALID_OPTION:
    printf("Error: Invalid option. Please select 1-5.\n\n");
    break;
  case SUCCESS:
    break;
  }
}

double factorial_rec_logic(int n) {
  g_call_count++;
  if (n <= 1)
    return 1.0;
  return (double)n * factorial_rec_logic(n - 1);
}

double fibonacci_rec_logic(int n) {
  g_call_count++;
  if (n <= 1)
    return (double)n;
  return fibonacci_rec_logic(n - 1) + fibonacci_rec_logic(n - 2);
}

double sum_natural_rec_logic(int n) {
  g_call_count++;
  if (n <= 0)
    return 0.0;
  return (double)n + sum_natural_rec_logic(n - 1);
}

double power_rec_logic(double base, int exp) {
  g_call_count++;
  if (exp == 0)
    return 1.0;
  return base * power_rec_logic(base, exp - 1);
}

Result factorial_rec(int n) {
  Result res = {SUCCESS, 0.0, 0};

  if (n < 0) {
    res.status = ERR_NEGATIVE_VAL;
    return res;
  }

  g_call_count = 0;
  res.value = factorial_rec_logic(n);
  res.count = g_call_count;

  return res;
}

Result factorial_ite(int n) {
  Result res = {SUCCESS, 1.0, 0};

  if (n < 0) {
    res.status = ERR_NEGATIVE_VAL;
    return res;
  }

  for (int i = 2; i <= n; i++) {
    res.value *= i;
    res.count++;
  }

  return res;
}

Result fibonacci_rec(int n) {
  Result res = {SUCCESS, 0.0, 0};

  if (n < 1) {
    res.value = 0;
    return res;
  }

  g_call_count = 0;
  res.value = fibonacci_rec_logic(n - 1);
  res.count = g_call_count;

  return res;
}

Result fibonacci_ite(int n) {
  Result res = {SUCCESS, 0.0, 0};

  if (n < 1)
    return res;

  if (n == 1) {
    res.value = 0;
    return res;
  }

  double a = 0, b = 1;
  res.value = 1;

  for (int i = 2; i < n; i++) {
    res.value = a + b;
    a = b;
    b = res.value;
    res.count++;
  }

  res.value = b;

  return res;
}

Result sum_natural_rec(int n) {
  Result res = {SUCCESS, 0.0, 0};

  if (n < 0) {
    res.status = ERR_NEGATIVE_VAL;
    return res;
  }

  g_call_count = 0;
  res.value = sum_natural_rec_logic(n);
  res.count = g_call_count;

  return res;
}

Result sum_natural_ite(int n) {
  Result res = {SUCCESS, 0.0, 0};

  if (n < 0) {
    res.status = ERR_NEGATIVE_VAL;
    return res;
  }

  for (int i = 1; i <= n; i++) {
    res.value += (double)i;
    res.count++;
  }

  return res;
}

Result power_rec(double base, int exp) {
  Result res = {SUCCESS, 0.0, 0};

  if (exp < 0) {
    res.status = ERR_NEGATIVE_VAL;
    return res;
  }

  g_call_count = 0;
  res.value = power_rec_logic(base, exp);
  res.count = g_call_count;

  return res;
}

Result power_ite(double base, int exp) {
  Result res = {SUCCESS, 1.0, 0};

  if (exp < 0) {
    res.status = ERR_NEGATIVE_VAL;
    return res;
  }

  for (int i = 0; i < exp; i++) {
    res.value *= base;
    res.count++;
  }

  return res;
}
