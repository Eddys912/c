#include <stdio.h>
#include <stdlib.h>

int main() {

  unsigned int stations, pressures, i, j;
  double **matrix_stations;

  printf("=== Array Memory Allocation ===\n\n");

  printf("How many stations do you want to enter?: ");
  scanf("%u", &stations);
  printf("How many pressure readings do you want to enter?: ");
  scanf("%u", &pressures);

  matrix_stations = (double **)malloc(stations * sizeof(double *));
  if (matrix_stations == NULL) {
    printf("Error: Could not allocate memory.\n");
    return 1;
  }
  for (i = 0; i < stations; i++) {
    *(matrix_stations + i) = (double *)malloc(pressures * sizeof(double));
    if (*(matrix_stations + i) == NULL) {
      printf("Error: Could not allocate memory.\n");
      return 1;
    }
  }

  for (i = 0; i < stations; i++) {
    for (j = 0; j < pressures; j++) {
      printf("  Enter pressure %u for station %u: ", j + 1, i + 1);
      scanf("%lf", *(matrix_stations + i) + j);
    }
  }

  printf("\nPressure readings entered:\n");
  for (i = 0; i < stations; i++) {
    printf("  Station %u: ", i + 1);
    for (j = 0; j < pressures; j++) {
      printf("%.4f ", *(*(matrix_stations + i) + j));
    }
    printf("\n");
  }

  for (i = 0; i < stations; i++) {
    free(*(matrix_stations + i));
  }
  free(matrix_stations);
  matrix_stations = NULL;
  printf("\nMemory freed successfully.\n");

  return 0;
}
