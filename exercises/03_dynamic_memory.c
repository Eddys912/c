#include <stdio.h>
#include <stdlib.h>

void clear_input_buffer();

int main() {

  unsigned int total_temperatures, i;
  double average_temperature = 0;
  double *temperatures;

  printf("=== Dynamic Memory Allocation ===\n\n");

  printf("How many temperatures do you want to enter?: ");
  if (scanf("%u", &total_temperatures) != 1) {
    fprintf(stderr, "Error: Invalid input.\n");
    return 1;
  }
  clear_input_buffer();

  if (total_temperatures == 0) {
    fprintf(stderr, "Error: Cannot calculate average of zero temperatures.\n");
    return 1;
  }

  temperatures = (double *)malloc(total_temperatures * sizeof(double));
  if (temperatures == NULL) {
    fprintf(stderr, "Error: Could not allocate memory.\n");
    return 1;
  }

  for (i = 0; i < total_temperatures; i++) {
    printf("  Enter temperature %u: ", i + 1);
    if (scanf("%lf", (temperatures + i)) != 1) {
      fprintf(stderr, "Error: Invalid temperature input.\n");
      free(temperatures);
      return 1;
    }
    clear_input_buffer();
  }

  for (i = 0; i < total_temperatures; i++) {
    average_temperature += *(temperatures + i);
  }
  average_temperature /= total_temperatures;

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
