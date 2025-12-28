#include <stdio.h>
#include <stdlib.h>

void clear_input_buffer();
int read_positive(const char *prompt, unsigned int *value);
double *allocate_temperature_array(unsigned int size);
int read_temperatures(double *temperatures, unsigned int count);
double calculate_average(const double *temperatures, unsigned int count);

int main() {
  unsigned int total_temperatures;
  double *temperatures;
  double average_temperature;

  printf("=== Dynamic Memory Allocation ===\n\n");

  if (read_positive("How many temperatures do you want to enter?: ", &total_temperatures) != 0) {
    return 1;
  }

  temperatures = allocate_temperature_array(total_temperatures);
  if (temperatures == NULL) {
    return 1;
  }

  if (read_temperatures(temperatures, total_temperatures) != 0) {
    free(temperatures);
    return 1;
  }

  average_temperature = calculate_average(temperatures, total_temperatures);

  printf("\nMemory allocated at: %p\n", (void *)temperatures);
  printf("  Average temperature: %.2f\n", average_temperature);

  free(temperatures);
  temperatures = NULL;
  printf("\nMemory freed successfully.\n");

  return 0;
}

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

int read_positive(const char *prompt, unsigned int *value) {
  printf("%s", prompt);

  if (scanf("%u", value) != 1) {
    fprintf(stderr, "Error: Invalid input.\n");
    return 1;
  }
  clear_input_buffer();

  if (*value == 0) {
    fprintf(stderr, "Error: Cannot calculate average of zero temperatures.\n");
    return 1;
  }

  return 0;
}

double *allocate_temperature_array(unsigned int size) {
  double *array = (double *)malloc(size * sizeof(double));

  if (array == NULL) {
    fprintf(stderr, "Error: Could not allocate memory.\n");
  }

  return array;
}

int read_temperatures(double *temperatures, unsigned int count) {
  unsigned int i;

  for (i = 0; i < count; i++) {
    printf("  Enter temperature %u: ", i + 1);
    if (scanf("%lf", (temperatures + i)) != 1) {
      fprintf(stderr, "Error: Invalid temperature input.\n");
      return 1;
    }
    clear_input_buffer();
  }

  return 0;
}

double calculate_average(const double *temperatures, unsigned int count) {
  double sum = 0;
  unsigned int i;

  for (i = 0; i < count; i++) {
    sum += *(temperatures + i);
  }

  return sum / count;
}
