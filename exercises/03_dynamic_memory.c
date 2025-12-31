/*
 ===============================================================================
 Exercise: 03_dynamic_memory.c
 Description: Demonstrates dynamic memory allocation for temperature averaging
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Reads N temperatures from user input with validation
 - Allocates memory dynamically for temperature array
 - Calculates average using pointer arithmetic
 - Proper memory deallocation and cleanup
 ===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define MIN_TEMPERATURES 1
#define SCANF_SUCCESS 1
#define INPUT_PROMPT_FORMAT "%s"
#define TEMP_PROMPT_FORMAT "  Enter temperature %u: "
#define MEMORY_INFO_FORMAT "\nMemory allocated at: %p\n"
#define AVERAGE_FORMAT "  Average temperature: %.2f\n"

typedef enum {
  SUCCESS = 0,
  ERROR_INVALID_INPUT = 1,
  ERROR_ALLOCATION_FAILED = 1,
  ERROR_ZERO_TEMPERATURES = 1
} StatusCode;

void clear_input_buffer(void);
StatusCode read_positive_integer(const char *prompt, unsigned int *value);
double *allocate_temperature_array(unsigned int size);
StatusCode read_temperatures(double *temperatures, unsigned int count);
double calculate_average(const double *temperatures, unsigned int count);
void print_results(const double *temperatures, double average);

int main(void) {
  unsigned int total_temperatures;
  double *temperatures;
  double average_temperature;

  printf("=== Dynamic Memory Allocation ===\n\n");

  if (read_positive_integer("How many temperatures do you want to enter?: ", &total_temperatures) !=
      SUCCESS) {
    return ERROR_INVALID_INPUT;
  }

  temperatures = allocate_temperature_array(total_temperatures);
  if (temperatures == NULL) {
    return ERROR_ALLOCATION_FAILED;
  }

  if (read_temperatures(temperatures, total_temperatures) != SUCCESS) {
    free(temperatures);
    return ERROR_INVALID_INPUT;
  }

  average_temperature = calculate_average(temperatures, total_temperatures);
  print_results(temperatures, average_temperature);

  free(temperatures);
  temperatures = NULL;
  printf("\nMemory freed successfully.\n");

  return SUCCESS;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

StatusCode read_positive_integer(const char *prompt, unsigned int *value) {
  printf(INPUT_PROMPT_FORMAT, prompt);

  if (scanf("%u", value) != SCANF_SUCCESS) {
    fprintf(stderr, "Error: Invalid input.\n");
    clear_input_buffer();
    return ERROR_INVALID_INPUT;
  }
  clear_input_buffer();

  if (*value < MIN_TEMPERATURES) {
    fprintf(stderr, "Error: Must enter at least %d temperature.\n", MIN_TEMPERATURES);
    return ERROR_ZERO_TEMPERATURES;
  }

  return SUCCESS;
}

double *allocate_temperature_array(unsigned int size) {
  double *array = (double *)malloc(size * sizeof(double));

  if (array == NULL) {
    fprintf(stderr, "Error: Could not allocate memory.\n");
  }

  return array;
}

StatusCode read_temperatures(double *temperatures, unsigned int count) {
  for (unsigned int i = 0; i < count; i++) {
    printf(TEMP_PROMPT_FORMAT, i + 1);
    if (scanf("%lf", (temperatures + i)) != SCANF_SUCCESS) {
      fprintf(stderr, "Error: Invalid temperature input.\n");
      clear_input_buffer();
      return ERROR_INVALID_INPUT;
    }
    clear_input_buffer();
  }

  return SUCCESS;
}

double calculate_average(const double *temperatures, unsigned int count) {
  double sum = 0.0;

  for (unsigned int i = 0; i < count; i++) {
    sum += *(temperatures + i);
  }

  return sum / count;
}

void print_results(const double *temperatures, double average) {
  printf(MEMORY_INFO_FORMAT, (const void *)temperatures);
  printf(AVERAGE_FORMAT, average);
}
