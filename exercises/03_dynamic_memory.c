#include <stdio.h>
#include <stdlib.h>

int main() {

  unsigned int total_temperatures, i;
  double average_temperature = 0;
  double *temperatures;

  printf("=== Dynamic Memory Allocation ===\n\n");
  printf("How many temperatures do you want to enter?: ");
  scanf("%u", &total_temperatures);

  temperatures = (double *)malloc(total_temperatures * sizeof(double));
  if (temperatures == NULL) {
    printf("Error: Could not allocate memory.\n");
    return 1;
  }

  for (i = 0; i < total_temperatures; i++) {
    printf("  Enter temperature %u: ", i + 1);
    scanf("%lf", (temperatures + i));
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
