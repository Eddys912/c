/*
 ===============================================================================
 File: 02_unit_converter.c
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

void clear_input_buffer(void);
int read_double(double *value);
int read_integer(int *value);
int read_char(char *value);
void show_unit_options(int option);
double convert_temperature(double value, char from, char to, int *error);
double convert_length(double value, char from, char to, int *error);
double convert_weight(double value, char from, char to, int *error);
double convert_time(double value, char from, char to, int *error);

int main(void) {
  int option = 0;

  while (TRUE) {
    printf("=== Unit Converter ===\n\n");
    printf("1. Temperature\n2. Length\n3. Weight\n4. Time\n5. Exit\n");
    printf("Select an option: ");

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

    printf("Enter value: ");
    double value;
    if (!read_double(&value))
      continue;

    printf("Enter source unit: ");
    char from;
    if (!read_char(&from))
      continue;

    printf("Enter target unit: ");
    char to;
    if (!read_char(&to))
      continue;

    int error = FALSE;
    double result = 0.0;

    switch (option) {
    case 1:
      result = convert_temperature(value, from, to, &error);
      break;
    case 2:
      result = convert_length(value, from, to, &error);
      break;
    case 3:
      result = convert_weight(value, from, to, &error);
      break;
    case 4:
      result = convert_time(value, from, to, &error);
      break;
    }

    if (!error) {
      printf("\n  - Result: %.2f %c\n\n", result, to);
    } else {
      printf("Error: Invalid unit selected.\n\n");
    }
  }

  return 0;
}

void clear_input_buffer(void) {
  while (getchar() != '\n')
    ;
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

int read_integer(int *value) {
  if (scanf("%d", value) != 1) {
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

int read_char(char *value) {
  if (scanf(" %c", value) != 1) {
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
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

double convert_temperature(double value, char from, char to, int *error) {
  double celsius;

  if (from == 'C' || from == 'c')
    celsius = value;
  else if (from == 'F' || from == 'f')
    celsius = (value - FAHRENHEIT_OFFSET) / FAHRENHEIT_RATIO;
  else if (from == 'K' || from == 'k')
    celsius = value - KELVIN_OFFSET;
  else {
    *error = TRUE;
    return 0.0;
  }

  if (to == 'C' || to == 'c')
    return celsius;
  if (to == 'F' || to == 'f')
    return celsius * FAHRENHEIT_RATIO + FAHRENHEIT_OFFSET;
  if (to == 'K' || to == 'k')
    return celsius + KELVIN_OFFSET;

  *error = TRUE;
  return 0.0;
}

double convert_length(double value, char from, char to, int *error) {
  double meters;

  if (from == 'M' || from == 'm')
    meters = value;
  else if (from == 'K' || from == 'k')
    meters = value * METERS_PER_KM;
  else if (from == 'I' || from == 'i')
    meters = value * METERS_PER_MILE;
  else if (from == 'F' || from == 'f')
    meters = value * METERS_PER_FOOT;
  else {
    *error = TRUE;
    return 0.0;
  }

  if (to == 'M' || to == 'm')
    return meters;
  if (to == 'K' || to == 'k')
    return meters / METERS_PER_KM;
  if (to == 'I' || to == 'i')
    return meters / METERS_PER_MILE;
  if (to == 'F' || to == 'f')
    return meters / METERS_PER_FOOT;

  *error = TRUE;
  return 0.0;
}

double convert_weight(double value, char from, char to, int *error) {
  double kg;

  if (from == 'K' || from == 'k')
    kg = value;
  else if (from == 'P' || from == 'p')
    kg = value * KG_PER_POUND;
  else if (from == 'O' || from == 'o')
    kg = value * KG_PER_OUNCE;
  else {
    *error = TRUE;
    return 0.0;
  }

  if (to == 'K' || to == 'k')
    return kg;
  if (to == 'P' || to == 'p')
    return kg / KG_PER_POUND;
  if (to == 'O' || to == 'o')
    return kg / KG_PER_OUNCE;

  *error = TRUE;
  return 0.0;
}

double convert_time(double value, char from, char to, int *error) {
  double seconds;

  if (from == 'S' || from == 's')
    seconds = value;
  else if (from == 'M' || from == 'm')
    seconds = value * SECONDS_PER_MINUTE;
  else if (from == 'H' || from == 'h')
    seconds = value * SECONDS_PER_HOUR;
  else {
    *error = TRUE;
    return 0.0;
  }

  if (to == 'S' || to == 's')
    return seconds;
  if (to == 'M' || to == 'm')
    return seconds / SECONDS_PER_MINUTE;
  if (to == 'H' || to == 'h')
    return seconds / SECONDS_PER_HOUR;

  *error = TRUE;
  return 0.0;
}
