#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_RANGE 10000
#define EXIT_OPTION 5

static const char *MSG_MENU_TITLE = "=== Prime Number Analyzer ===\n";
static const char *MSG_MENU_OPTIONS = "1. List primes in range\n2. Check primality\n"
                                      "3. Prime factorization\n4. Twin primes\n5. Exit\n";
static const char *MSG_GOODBYE = "Thank you for using the analyzer!\n";
static const char *MSG_IS_PRIME = "Is prime\n\n";
static const char *MSG_NOT_PRIME = "Not prime\n\n";

static const char *INPUT_OPTION = "Option: ";
static const char *INPUT_START = "Start range: ";
static const char *INPUT_END = "End range: ";
static const char *INPUT_NUMBER = "Enter number: ";

static const char *FMT_PRIMES_FOUND = "Primes found: %d\n";
static const char *FMT_FACTOR_START = "Prime factorization of %d:\n%d = ";
static const char *FMT_TWINS_TITLE = "Twin primes found:\n";

static const char *FMT_LIST_START = "[";
static const char *FMT_LIST_SEPARATOR = ", ";
static const char *FMT_LIST_END = "]\n\n";

static const char *FMT_FACTOR_SEPARATOR = " x ";
static const char *FMT_FACTOR_POWER = "%d^%d";
static const char *FMT_FACTOR_END = "\n\n";

static const char *FMT_TWIN_PAIR = "(%d, %d)";
static const char *FMT_TWIN_SEPARATOR = ", ";
static const char *FMT_TWIN_END = "\n\n";

static const char *ERR_MSG_INVALID = "Error: Invalid input or out of range (max 10000).\n";

void clear_input_buffer(void);
int read_integer(int *value);
void sieve_of_eratosthenes(int is_prime[], int n);
void list_primes(int start, int end);
void check_primality(int num);
void prime_factorization(int num);
void find_twin_primes(int start, int end);

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

    int start, end, num;

    switch (option) {
    case 1:
      printf("%s", INPUT_START);
      if (!read_integer(&start))
        break;
      printf("%s", INPUT_END);
      if (!read_integer(&end))
        break;
      if (start < 0 || end > MAX_RANGE || start > end) {
        printf("%s", ERR_MSG_INVALID);
        break;
      }
      list_primes(start, end);
      break;

    case 2:
      printf("%s", INPUT_NUMBER);
      if (!read_integer(&num))
        break;
      check_primality(num);
      break;

    case 3:
      printf("%s", INPUT_NUMBER);
      if (!read_integer(&num))
        break;
      if (num < 2) {
        printf("%s", ERR_MSG_INVALID);
        break;
      }
      prime_factorization(num);
      break;

    case 4:
      printf("%s", INPUT_START);
      if (!read_integer(&start))
        break;
      printf("%s", INPUT_END);
      if (!read_integer(&end))
        break;
      if (start < 0 || end > MAX_RANGE || start > end) {
        printf("%s", ERR_MSG_INVALID);
        break;
      }
      find_twin_primes(start, end);
      break;
    }
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

void sieve_of_eratosthenes(int is_prime[], int n) {
  for (int i = 0; i <= n; i++)
    is_prime[i] = TRUE;
  is_prime[0] = is_prime[1] = FALSE;

  for (int p = 2; p * p <= n; p++) {
    if (is_prime[p] == TRUE) {
      for (int i = p * p; i <= n; i += p)
        is_prime[i] = FALSE;
    }
  }
}

void list_primes(int start, int end) {
  if (end > MAX_RANGE)
    end = MAX_RANGE;

  int *is_prime = malloc((end + 1) * sizeof(int));
  sieve_of_eratosthenes(is_prime, end);

  int count = 0;
  for (int i = start; i <= end; i++) {
    if (is_prime[i])
      count++;
  }

  printf(FMT_PRIMES_FOUND, count);
  printf("%s", FMT_LIST_START);
  int first = TRUE;
  for (int i = start; i <= end; i++) {
    if (is_prime[i]) {
      if (!first)
        printf("%s", FMT_LIST_SEPARATOR);
      printf("%d", i);
      first = FALSE;
    }
  }
  printf("%s", FMT_LIST_END);
  free(is_prime);
}

void check_primality(int num) {
  if (num < 2) {
    printf("%s", MSG_NOT_PRIME);
    return;
  }

  int is_p = TRUE;
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0) {
      is_p = FALSE;
      break;
    }
  }

  printf("%s", is_p ? MSG_IS_PRIME : MSG_NOT_PRIME);
}

void prime_factorization(int num) {
  if (num < 2)
    return;

  printf(FMT_FACTOR_START, num, num);

  int temp = num;
  int first = TRUE;
  for (int i = 2; i * i <= temp; i++) {
    int count = 0;
    while (temp % i == 0) {
      count++;
      temp /= i;
    }
    if (count > 0) {
      if (!first)
        printf("%s", FMT_FACTOR_SEPARATOR);
      printf(FMT_FACTOR_POWER, i, count);
      first = FALSE;
    }
  }
  if (temp > 1) {
    if (!first)
      printf("%s", FMT_FACTOR_SEPARATOR);
    printf(FMT_FACTOR_POWER, temp, 1);
  }
  printf("%s", FMT_FACTOR_END);
}

void find_twin_primes(int start, int end) {
  if (end > MAX_RANGE)
    end = MAX_RANGE;

  int *is_prime = malloc((end + 1) * sizeof(int));
  sieve_of_eratosthenes(is_prime, end);

  printf("%s", FMT_TWINS_TITLE);
  int first = TRUE;
  for (int i = start; i <= end - 2; i++) {
    if (is_prime[i] && is_prime[i + 2]) {
      if (!first)
        printf("%s", FMT_TWIN_SEPARATOR);
      printf(FMT_TWIN_PAIR, i, i + 2);
      first = FALSE;
    }
  }
  printf("%s", FMT_TWIN_END);
  free(is_prime);
}
