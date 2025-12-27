#include <stdio.h>
#include <stdlib.h>

void clear_input_buffer();
void free_matrix(double **matrix, unsigned int rows);

int main() {

  unsigned int stations, pressures, i, j;
  double **matrix_stations;

  printf("=== Array Pointers Allocation ===\n\n");

  printf("How many stations do you want to enter?: ");
  if (scanf("%u", &stations) != 1) {
    fprintf(stderr, "Error: Invalid input.\n");
    return 1;
  }
  clear_input_buffer();

  printf("How many pressure readings do you want to enter?: ");
  if (scanf("%u", &pressures) != 1) {
    fprintf(stderr, "Error: Invalid input.\n");
    return 1;
  }
  clear_input_buffer();

  if (stations == 0 || pressures == 0) {
    fprintf(stderr, "Error: Stations and pressures must be greater than zero.\n");
    return 1;
  }

  matrix_stations = (double **)malloc(stations * sizeof(double *));
  if (matrix_stations == NULL) {
    fprintf(stderr, "Error: Could not allocate memory.\n");
    return 1;
  }

  for (i = 0; i < stations; i++) {
    *(matrix_stations + i) = (double *)malloc(pressures * sizeof(double));
    if (*(matrix_stations + i) == NULL) {
      fprintf(stderr, "Error: Could not allocate memory.\n");
      for (unsigned int k = 0; k < i; k++) {
        free(*(matrix_stations + k));
      }
      free(matrix_stations);
      return 1;
    }
  }

  for (i = 0; i < stations; i++) {
    for (j = 0; j < pressures; j++) {
      printf("  Enter pressure %u for station %u: ", j + 1, i + 1);
      if (scanf("%lf", *(matrix_stations + i) + j) != 1) {
        fprintf(stderr, "Error: Invalid pressure input.\n");
        free_matrix(matrix_stations, stations);
        return 1;
      }
      clear_input_buffer();
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

  free_matrix(matrix_stations, stations);
  matrix_stations = NULL;
  printf("\nMemory freed successfully.\n");

  return 0;
}

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void free_matrix(double **matrix, unsigned int rows) {
  for (unsigned int i = 0; i < rows; i++) {
    free(*(matrix + i));
  }
  free(matrix);
}
