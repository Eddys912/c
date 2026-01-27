/*
 ===============================================================================
 Exercise: 02_unit_converter.c
 Description: Unit converter with interactive menu
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Temperature conversion (Celsius, Fahrenheit, Kelvin)
 - Length conversion (meters, kilometers, miles, feet)
 - Weight conversion (kilograms, pounds, ounces)
 - Time conversion (seconds, minutes, hours)
 - Input validation and error handling
 - Case-insensitive unit input
 ===============================================================================
*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define EXIT_OPTION 5

static const double KELVIN_OFFSET = 273.15;
static const double FAHRENHEIT_RATIO = 1.8;
static const double FAHRENHEIT_OFFSET = 32.0;

static const double METERS_PER_KM = 1000.0;
static const double METERS_PER_MILE = 1609.34;
static const double METERS_PER_FOOT = 0.3048;

static const double KG_PER_POUND = 0.453592;
static const double KG_PER_OUNCE = 0.0283495;

static const double SECONDS_PER_MINUTE = 60.0;
static const double SECONDS_PER_HOUR = 3600.0;

typedef enum { SUCCESS, ERR_INVALID_UNIT, ERR_INVALID_OPTION } Status;

void show_menu(void);
void clear_input_buffer(void);
int read_integer(int *value);
int read_double(double *value);
int read_char(char *value);
int read_conversion_input(double *value, char *from, char *to);
void show_unit_options(int option);
void handle_error(Status status);

Status convert_temperature(double value, char from, char to, double *result);
Status convert_length(double value, char from, char to, double *result);
Status convert_weight(double value, char from, char to, double *result);
Status convert_time(double value, char from, char to, double *result);

void run_temperature_conversion(void);
void run_length_conversion(void);
void run_weight_conversion(void);
void run_time_conversion(void);

int main(void) {
  int option = 0;

  while (TRUE) {
    show_menu();

    if (!read_integer(&option)) {
      printf("Error: Invalid option. Please select 1-5.\n\n");
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("\nThank you for using the converter!\n");
      break;
    }

    if (option < 1 || option > 5) {
      printf("Error: Invalid option. Please select 1-5.\n\n");
      continue;
    }

    show_unit_options(option);

    switch (option) {
    case 1:
      run_temperature_conversion();
      break;
    case 2:
      run_length_conversion();
      break;
    case 3:
      run_weight_conversion();
      break;
    case 4:
      run_time_conversion();
      break;
    }
  }

  return 0;
}

void show_menu(void) {
  printf("=== Unit Converter ===\n\n");
  printf("1. Temperature\n2. Length\n3. Weight\n4. Time\n5. Exit\n");
  printf("Select an option: ");
}

void clear_input_buffer(void) {
  while (getchar() != '\n')
    ;
}

int read_integer(int *value) {
  if (scanf("%d", value) != 1) {
    printf("Error: Invalid option. Please select 1-5.\n\n");
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

int read_double(double *value) {
  if (scanf("%lf", value) != 1) {
    printf("Error: That is not a valid number. Try again.\n\n");
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

int read_char(char *value) {
  if (scanf(" %c", value) != 1) {
    printf("Error: That is not a valid unit. Try again.\n\n");
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

int read_conversion_input(double *value, char *from, char *to) {
  printf("Enter value: ");
  if (!read_double(value))
    return FALSE;

  printf("Enter source unit: ");
  if (!read_char(from))
    return FALSE;

  printf("Enter target unit: ");
  if (!read_char(to))
    return FALSE;

  return TRUE;
}

void show_unit_options(int option) {
  switch (option) {
  case 1:
    printf("\nUnits: C (Celsius), F (Fahrenheit), K (Kelvin)\n");
    break;
  case 2:
    printf("\nUnits: M (meters), K (km), I (miles), F (feet)\n");
    break;
  case 3:
    printf("\nUnits: K (kg), P (pounds), O (ounces)\n");
    break;
  case 4:
    printf("\nUnits: S (seconds), M (minutes), H (hours)\n");
    break;
  }
}

void handle_error(Status status) {
  switch (status) {
  case ERR_INVALID_UNIT:
    printf("Error: Invalid unit selected.\n\n");
    break;
  case ERR_INVALID_OPTION:
    printf("Error: Invalid option.\n\n");
    break;
  case SUCCESS:
    break;
  }
}

void run_temperature_conversion(void) {
  double value, result;
  char from, to;

  if (!read_conversion_input(&value, &from, &to))
    return;

  Status status = convert_temperature(value, from, to, &result);
  if (status == SUCCESS) {
    printf("\n  - Result: %.2f %c\n\n", result, to);
  } else {
    handle_error(status);
  }
}

void run_length_conversion(void) {
  double value, result;
  char from, to;

  if (!read_conversion_input(&value, &from, &to))
    return;

  Status status = convert_length(value, from, to, &result);
  if (status == SUCCESS) {
    printf("\n  - Result: %.2f %c\n\n", result, to);
  } else {
    handle_error(status);
  }
}

void run_weight_conversion(void) {
  double value, result;
  char from, to;

  if (!read_conversion_input(&value, &from, &to))
    return;

  Status status = convert_weight(value, from, to, &result);
  if (status == SUCCESS) {
    printf("\n  - Result: %.2f %c\n\n", result, to);
  } else {
    handle_error(status);
  }
}

void run_time_conversion(void) {
  double value, result;
  char from, to;

  if (!read_conversion_input(&value, &from, &to))
    return;

  Status status = convert_time(value, from, to, &result);
  if (status == SUCCESS) {
    printf("\n  - Result: %.2f %c\n\n", result, to);
  } else {
    handle_error(status);
  }
}

Status convert_temperature(double value, char from, char to, double *result) {
  double celsius;

  if (from == 'C' || from == 'c')
    celsius = value;
  else if (from == 'F' || from == 'f')
    celsius = (value - FAHRENHEIT_OFFSET) / FAHRENHEIT_RATIO;
  else if (from == 'K' || from == 'k')
    celsius = value - KELVIN_OFFSET;
  else
    return ERR_INVALID_UNIT;

  if (to == 'C' || to == 'c') {
    *result = celsius;
    return SUCCESS;
  }
  if (to == 'F' || to == 'f') {
    *result = celsius * FAHRENHEIT_RATIO + FAHRENHEIT_OFFSET;
    return SUCCESS;
  }
  if (to == 'K' || to == 'k') {
    *result = celsius + KELVIN_OFFSET;
    return SUCCESS;
  }

  return ERR_INVALID_UNIT;
}

Status convert_length(double value, char from, char to, double *result) {
  double meters;

  if (from == 'M' || from == 'm')
    meters = value;
  else if (from == 'K' || from == 'k')
    meters = value * METERS_PER_KM;
  else if (from == 'I' || from == 'i')
    meters = value * METERS_PER_MILE;
  else if (from == 'F' || from == 'f')
    meters = value * METERS_PER_FOOT;
  else
    return ERR_INVALID_UNIT;

  if (to == 'M' || to == 'm') {
    *result = meters;
    return SUCCESS;
  }
  if (to == 'K' || to == 'k') {
    *result = meters / METERS_PER_KM;
    return SUCCESS;
  }
  if (to == 'I' || to == 'i') {
    *result = meters / METERS_PER_MILE;
    return SUCCESS;
  }
  if (to == 'F' || to == 'f') {
    *result = meters / METERS_PER_FOOT;
    return SUCCESS;
  }

  return ERR_INVALID_UNIT;
}

Status convert_weight(double value, char from, char to, double *result) {
  double kg;

  if (from == 'K' || from == 'k')
    kg = value;
  else if (from == 'P' || from == 'p')
    kg = value * KG_PER_POUND;
  else if (from == 'O' || from == 'o')
    kg = value * KG_PER_OUNCE;
  else
    return ERR_INVALID_UNIT;

  if (to == 'K' || to == 'k') {
    *result = kg;
    return SUCCESS;
  }
  if (to == 'P' || to == 'p') {
    *result = kg / KG_PER_POUND;
    return SUCCESS;
  }
  if (to == 'O' || to == 'o') {
    *result = kg / KG_PER_OUNCE;
    return SUCCESS;
  }

  return ERR_INVALID_UNIT;
}

Status convert_time(double value, char from, char to, double *result) {
  double seconds;

  if (from == 'S' || from == 's')
    seconds = value;
  else if (from == 'M' || from == 'm')
    seconds = value * SECONDS_PER_MINUTE;
  else if (from == 'H' || from == 'h')
    seconds = value * SECONDS_PER_HOUR;
  else
    return ERR_INVALID_UNIT;

  if (to == 'S' || to == 's') {
    *result = seconds;
    return SUCCESS;
  }
  if (to == 'M' || to == 'm') {
    *result = seconds / SECONDS_PER_MINUTE;
    return SUCCESS;
  }
  if (to == 'H' || to == 'h') {
    *result = seconds / SECONDS_PER_HOUR;
    return SUCCESS;
  }

  return ERR_INVALID_UNIT;
}
