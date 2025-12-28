#include <stdio.h>
#include <stdlib.h>

void clear_input_buffer();
int read_positive(const char *prompt, unsigned int *value);
double **allocate_matrix(unsigned int rows, unsigned int cols);
void free_matrix(double **matrix, unsigned int rows);
int read_matrix_data(double **matrix, unsigned int rows, unsigned int cols);
void display_matrix(double **matrix, unsigned int rows, unsigned int cols);

int main() {
  unsigned int stations, pressures;
  double **matrix_stations;

  printf("=== Array Pointers Allocation ===\n\n");

  if (read_positive("How many stations do you want to enter?: ", &stations) != 0) {
    return 1;
  }

  if (read_positive("How many pressure readings do you want to enter?: ", &pressures) != 0) {
    return 1;
  }

  matrix_stations = allocate_matrix(stations, pressures);
  if (matrix_stations == NULL) {
    return 1;
  }

  if (read_matrix_data(matrix_stations, stations, pressures) != 0) {
    free_matrix(matrix_stations, stations);
    return 1;
  }

  printf("\nPressure readings entered:\n");
  display_matrix(matrix_stations, stations, pressures);

  free_matrix(matrix_stations, stations);
  matrix_stations = NULL;
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
    fprintf(stderr, "Error: Value must be greater than zero.\n");
    return 1;
  }

  return 0;
}

double **allocate_matrix(unsigned int rows, unsigned int cols) {
  double **matrix;
  unsigned int i;

  matrix = (double **)malloc(rows * sizeof(double *));
  if (matrix == NULL) {
    fprintf(stderr, "Error: Could not allocate memory for matrix rows.\n");
    return NULL;
  }

  for (i = 0; i < rows; i++) {
    *(matrix + i) = (double *)malloc(cols * sizeof(double));
    if (*(matrix + i) == NULL) {
      fprintf(stderr, "Error: Could not allocate memory for matrix columns.\n");
      for (unsigned int k = 0; k < i; k++) {
        free(*(matrix + k));
      }
      free(matrix);
      return NULL;
    }
  }

  return matrix;
}

void free_matrix(double **matrix, unsigned int rows) {
  unsigned int i;

  for (i = 0; i < rows; i++) {
    free(*(matrix + i));
  }
  free(matrix);
}

int read_matrix_data(double **matrix, unsigned int rows, unsigned int cols) {
  unsigned int i, j;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf("  Enter pressure %u for station %u: ", j + 1, i + 1);

      if (scanf("%lf", *(matrix + i) + j) != 1) {
        fprintf(stderr, "Error: Invalid pressure input.\n");
        return 1;
      }
      clear_input_buffer();
    }
  }

  return 0;
}

void display_matrix(double **matrix, unsigned int rows, unsigned int cols) {
  unsigned int i, j;

  for (i = 0; i < rows; i++) {
    printf("  Station %u: ", i + 1);
    for (j = 0; j < cols; j++) {
      printf("%.4f ", *(*(matrix + i) + j));
    }
    printf("\n");
  }
}
