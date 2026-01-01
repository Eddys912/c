/*
 ===============================================================================
 Exercise: 04_array_pointers.c
 Description: Demonstrates 2D dynamic memory allocation for pressure readings
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Allocates 2D matrix dynamically (stations x pressure readings)
 - Reads and validates matrix data from user input
 - Displays formatted matrix output
 - Proper memory cleanup with rollback on allocation failure
 ===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define TITLE "=== Array Pointers Allocation ===\n\n"
#define TITLE_PRESSURE_READINGS "\nPressure readings entered:\n"

#define TEXT_MEMORY_FREE "\nMemory freed successfully.\n"
#define TEXT_STATION "  Station %u: "

#define INPUT_STATIONS "How many stations do you want to enter?: "
#define INPUT_PRESSURE "How many pressure readings do you want to enter?: "
#define INPUT_PRESSURE_FOR_STATION "  Enter pressure %u for station %u: "

#define FORMAT_STRING "%s"
#define FORMAT_UNSIGNED "%u"
#define FORMAT_DOUBLE "%lf"
#define FORMAT_PRESSURE "%.4f "

#define ERR_MSG_INVALID_INPUT "Error: Invalid input.\n"
#define ERR_MSG_INVALID_INPUT_PRESSURE "Error: Invalid pressure input.\n"
#define ERR_MSG_GREATER_THAN_ZERO "Error: Value must be greater than zero.\n"
#define ERR_MSG_COULD_MEMORY_FOR_ROWS "Error: Could not allocate memory for matrix rows.\n"
#define ERR_MSG_COULD_MEMORY_FOR_COLUMNS "Error: Could not allocate memory.\n"

#define MIN_VALUE 1
#define SCANF_SUCCESS 1
#define NEWLINE_CHAR '\n'
#define NEWLINE "\n"

typedef enum {
  SUCCESS = 0,
  ERROR_INVALID_INPUT = 1,
  ERROR_ALLOCATION_FAILED = 1,
  ERROR_ZERO_VALUE = 1
} StatusCode;

void clear_input_buffer(void);
StatusCode read_positive_integer(const char *prompt, unsigned int *value);
double **allocate_matrix(unsigned int rows, unsigned int cols);
void free_matrix(double **matrix, unsigned int rows);
StatusCode read_matrix_data(double **matrix, unsigned int rows, unsigned int cols);
void display_matrix(const double *const *matrix, unsigned int rows, unsigned int cols);

int main(void) {
  unsigned int stations, pressures;
  double **matrix_stations;

  printf(TITLE);

  if (read_positive_integer(INPUT_STATIONS, &stations) != SUCCESS) {
    return ERROR_INVALID_INPUT;
  }

  if (read_positive_integer(INPUT_PRESSURE, &pressures) != SUCCESS) {
    return ERROR_INVALID_INPUT;
  }

  matrix_stations = allocate_matrix(stations, pressures);
  if (matrix_stations == NULL) {
    return ERROR_ALLOCATION_FAILED;
  }

  if (read_matrix_data(matrix_stations, stations, pressures) != SUCCESS) {
    free_matrix(matrix_stations, stations);
    return ERROR_INVALID_INPUT;
  }

  printf(TITLE_PRESSURE_READINGS);
  display_matrix((const double *const *)matrix_stations, stations, pressures);

  free_matrix(matrix_stations, stations);
  matrix_stations = NULL;
  printf(TEXT_MEMORY_FREE);

  return SUCCESS;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != NEWLINE_CHAR && c != EOF)
    ;
}

StatusCode read_positive_integer(const char *prompt, unsigned int *value) {
  printf(FORMAT_STRING, prompt);

  if (scanf(FORMAT_UNSIGNED, value) != SCANF_SUCCESS) {
    fprintf(stderr, ERR_MSG_INVALID_INPUT);
    clear_input_buffer();
    return ERROR_INVALID_INPUT;
  }
  clear_input_buffer();

  if (*value < MIN_VALUE) {
    fprintf(stderr, ERR_MSG_GREATER_THAN_ZERO);
    return ERROR_ZERO_VALUE;
  }

  return SUCCESS;
}

double **allocate_matrix(unsigned int rows, unsigned int cols) {
  double **matrix = (double **)malloc(rows * sizeof(double *));

  if (matrix == NULL) {
    fprintf(stderr, ERR_MSG_COULD_MEMORY_FOR_ROWS);
    return NULL;
  }

  for (unsigned int i = 0; i < rows; i++) {
    *(matrix + i) = (double *)malloc(cols * sizeof(double));
    if (*(matrix + i) == NULL) {
      fprintf(stderr, ERR_MSG_COULD_MEMORY_FOR_COLUMNS);
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
  for (unsigned int i = 0; i < rows; i++) {
    free(*(matrix + i));
  }
  free(matrix);
}

StatusCode read_matrix_data(double **matrix, unsigned int rows, unsigned int cols) {
  for (unsigned int i = 0; i < rows; i++) {
    for (unsigned int j = 0; j < cols; j++) {
      printf(INPUT_PRESSURE_FOR_STATION, j + 1, i + 1);

      if (scanf(FORMAT_DOUBLE, *(matrix + i) + j) != SCANF_SUCCESS) {
        fprintf(stderr, ERR_MSG_INVALID_INPUT_PRESSURE);
        clear_input_buffer();
        return ERROR_INVALID_INPUT;
      }
      clear_input_buffer();
    }
  }

  return SUCCESS;
}

void display_matrix(const double *const *matrix, unsigned int rows, unsigned int cols) {
  for (unsigned int i = 0; i < rows; i++) {
    printf(TEXT_STATION, i + 1);
    for (unsigned int j = 0; j < cols; j++) {
      printf(FORMAT_PRESSURE, *(*(matrix + i) + j));
    }
    printf(NEWLINE);
  }
}
