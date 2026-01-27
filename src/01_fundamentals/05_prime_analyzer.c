/*
 ===============================================================================
 Exercise: 05_prime_analyzer.c
 Description: Prime number analysis tool with multiple algorithms
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Sieve of Eratosthenes implementation for range analysis
 - Primality test using trial division
 - Prime factorization
 - Twin prime identification
 - Efficient memory management for dynamic arrays
 ===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_RANGE 10000
#define EXIT_OPTION 5

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
    printf("=== Prime Number Analyzer ===\n\n");
    printf("1. List primes in range\n2. Check primality\n"
           "3. Prime factorization\n4. Twin primes\n5. Exit\n");
    printf("Option: ");

    if (!read_integer(&option)) {
      printf("Error: Invalid input or out of range (max 10000).\n");
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("Thank you for using the analyzer!\n");
      break;
    }

    if (option < 1 || option > 5) {
      printf("Error: Invalid input or out of range (max 10000).\n");
      continue;
    }

    int start, end, num;

    switch (option) {
    case 1:
      printf("Start range: ");
      if (!read_integer(&start))
        break;
      printf("End range: ");
      if (!read_integer(&end))
        break;
      if (start < 0 || end > MAX_RANGE || start > end) {
        printf("Error: Invalid input or out of range (max 10000).\n");
        break;
      }
      list_primes(start, end);
      break;

    case 2:
      printf("Enter number: ");
      if (!read_integer(&num))
        break;
      check_primality(num);
      break;

    case 3:
      printf("Enter number: ");
      if (!read_integer(&num))
        break;
      if (num < 2) {
        printf("Error: Invalid input or out of range (max 10000).\n");
        break;
      }
      prime_factorization(num);
      break;

    case 4:
      printf("Start range: ");
      if (!read_integer(&start))
        break;
      printf("End range: ");
      if (!read_integer(&end))
        break;
      if (start < 0 || end > MAX_RANGE || start > end) {
        printf("Error: Invalid input or out of range (max 10000).\n");
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

  printf("  - Primes found: %d -> ", count);
  printf("[");
  int first = TRUE;
  for (int i = start; i <= end; i++) {
    if (is_prime[i]) {
      if (!first)
        printf(", ");
      printf("%d", i);
      first = FALSE;
    }
  }
  printf("]\n\n");
  free(is_prime);
}

void check_primality(int num) {
  if (num < 2) {
    printf("  - Not prime\n\n");
    return;
  }

  int is_p = TRUE;
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0) {
      is_p = FALSE;
      break;
    }
  }

  printf(is_p ? "  - Is prime\n\n" : "  - Not prime\n\n");
}

void prime_factorization(int num) {
  if (num < 2)
    return;

  printf("  - Prime factorization of %d = ", num);

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
        printf(" x ");
      printf("%d^%d", i, count);
      first = FALSE;
    }
  }
  if (temp > 1) {
    if (!first)
      printf(" x ");
    printf("%d^%d", temp, 1);
  }
  printf("\n\n");
}

void find_twin_primes(int start, int end) {
  if (end > MAX_RANGE)
    end = MAX_RANGE;

  int *is_prime = malloc((end + 1) * sizeof(int));
  sieve_of_eratosthenes(is_prime, end);

  printf("  - Twin primes found: ");
  int first = TRUE;
  for (int i = start; i <= end - 2; i++) {
    if (is_prime[i] && is_prime[i + 2]) {
      if (!first)
        printf(", ");
      printf("(%d, %d)", i, i + 2);
      first = FALSE;
    }
  }
  printf("\n\n");
  free(is_prime);
}
