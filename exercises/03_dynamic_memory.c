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

#define TITLE "=== Dynamic Memory Allocation ===\n\n"
#define TITLE_MEMORY_ALLOCATED "\nMemory allocated at: %p\n"

#define TEXT_AVERAGE_TEMP "  Average temperature: %.2f\n"
#define TEXT_MEMORY_FREE "\nMemory freed successfully.\n"

#define INPUT_TEMPERATURES "How many temperatures do you want to enter?: "
#define INPUT_TEMPERATURE "  Enter temperature %u: "

#define FORMAT_INPUT_PROMPT "%s"

#define ERR_MSG_INVALID_INPUT "Error: Invalid input.\n"
#define ERR_MSG_INVALID_INPUT_TEMPERATURE "Error: Invalid temperature input.\n"
#define ERR_MSG_LEAST_TEMPERATURE "Error: Must enter at least %d temperature.\n"
#define ERR_MSG_COULD_MEMORY "Error: Could not allocate memory.\n"

#define MIN_TEMPERATURES 1
#define SCANF_SUCCESS 1

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

  printf(TITLE);

  if (read_positive_integer(INPUT_TEMPERATURES, &total_temperatures) != SUCCESS) {
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
  printf(TEXT_MEMORY_FREE);

  return SUCCESS;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

StatusCode read_positive_integer(const char *prompt, unsigned int *value) {
  printf(FORMAT_INPUT_PROMPT, prompt);

  if (scanf("%u", value) != SCANF_SUCCESS) {
    fprintf(stderr, ERR_MSG_INVALID_INPUT);
    clear_input_buffer();
    return ERROR_INVALID_INPUT;
  }
  clear_input_buffer();

  if (*value < MIN_TEMPERATURES) {
    fprintf(stderr, ERR_MSG_LEAST_TEMPERATURE, MIN_TEMPERATURES);
    return ERROR_ZERO_TEMPERATURES;
  }

  return SUCCESS;
}

double *allocate_temperature_array(unsigned int size) {
  double *array = (double *)malloc(size * sizeof(double));

  if (array == NULL) {
    fprintf(stderr, ERR_MSG_COULD_MEMORY);
  }

  return array;
}

StatusCode read_temperatures(double *temperatures, unsigned int count) {
  for (unsigned int i = 0; i < count; i++) {
    printf(INPUT_TEMPERATURE, i + 1);
    if (scanf("%lf", (temperatures + i)) != SCANF_SUCCESS) {
      fprintf(stderr, ERR_MSG_INVALID_INPUT_TEMPERATURE);
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
  printf(TITLE_MEMORY_ALLOCATED, (const void *)temperatures);
  printf(TEXT_AVERAGE_TEMP, average);
}
