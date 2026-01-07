#include <stdio.h>

static const char *MSG_MENU_TITLE = "=== Unit Converter ===\n\n";
static const char *MSG_MENU_OPTIONS = "1. Temperature (Celsius, Fahrenheit, Kelvin)\n"
                                      "2. Length (meters, km, miles, feet)\n"
                                      "3. Weight (kg, pounds, ounces)\n"
                                      "4. Time (seconds, minutes, hours)\n"
                                      "5. Exit\n";
static const char *MSG_MENU_TEMPERATURE = "TEMPERATURE";
static const char *MSG_MENU_LENGTH = "LENGTH";
static const char *MSG_MENU_WEIGHT = "WEIGHT";
static const char *MSG_MENU_TIME = "TIME";
static const char *MSG_GOODBYE = "Thank you for using the converter!\n";

static const char *INPUT_OPTION = "\nSelect an option: ";
static const char *INPUT_VALUE = "Enter value: ";
static const char *INPUT_SOURCE_UNIT_TEMPERATURE = "Source unit (C/F/K): ";
static const char *INPUT_TARGET_UNIT_TEMPERATURE = "Target unit (C/F/K): ";
static const char *INPUT_SOURCE_UNIT_LENGTH = "Source unit (M/K/I/F): ";
static const char *INPUT_TARGET_UNIT_LENGTH = "Target unit (M/K/I/F): ";
static const char *INPUT_SOURCE_UNIT_WEIGHT = "Source unit (K/P/O): ";
static const char *INPUT_TARGET_UNIT_WEIGHT = "Target unit (K/P/O): ";
static const char *INPUT_SOURCE_UNIT_TIME = "Source unit (S/M/H): ";
static const char *INPUT_TARGET_UNIT_TIME = "Target unit (S/M/H): ";

static const char *FMT_OPERATION_HEADER = "\n  === %s === \n\n";
static const char *FMT_RESULT_FLOAT = "\n  - Result: %.6f\n\n";

static const char *ERR_MSG_INVALID_OPTION = "Invalid option. Please try again.\n\n";
static const char *ERR_MSG_INPUT_INVALID = "Error: Invalid input. Please enter a valid number.\n\n";

#define EXIT_OPTION 5
#define FALSE 0
#define TRUE 1

typedef enum { OP_TEMPERATURE = 1, OP_LENGTH, OP_WEIGHT, OP_TIME, OP_EXIT } MenuOption;

typedef enum { STATUS_SUCCESS = 0, STATUS_ERROR_INVALID_OPTION } OperationStatus;

typedef struct {
  double value;
  OperationStatus status;
} OperationResult;

void clear_input_buffer(void);
int read_char(char *value);
int read_double(double *value);
OperationResult convert_temperature(double value, char from_unit, char to_unit);
OperationResult convert_length(double value, char from_unit, char to_unit);
OperationResult convert_weight(double value, char from_unit, char to_unit);
OperationResult convert_time(double value, char from_unit, char to_unit);
void display_menu(void);
void display_operation_header(const char *operation_name);
void display_result(OperationResult result);
void display_error(OperationStatus status);
void handle_temperature(void);
void handle_length(void);
void handle_weight(void);
void handle_time(void);
void run_interactive_menu(void);

int main(void) {
  run_interactive_menu();
  return 0;
}

void clear_input_buffer(void) {
  while (getchar() != '\n')
    ;
}

int read_char(char *value) {
  if (scanf(" %c", value) != 1) {
    printf("%s", ERR_MSG_INPUT_INVALID);
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

int read_double(double *value) {
  if (scanf("%lf", value) != 1) {
    printf("%s", ERR_MSG_INPUT_INVALID);
    clear_input_buffer();
    return FALSE;
  }
  return TRUE;
}

OperationResult convert_temperature(double value, char from_unit, char to_unit) {
  double celsius;

  if (from_unit != 'C' && from_unit != 'F' && from_unit != 'K') {
    return (OperationResult){0, STATUS_ERROR_INVALID_OPTION};
  }

  if (to_unit != 'C' && to_unit != 'F' && to_unit != 'K') {
    return (OperationResult){0, STATUS_ERROR_INVALID_OPTION};
  }

  if (from_unit == 'C') {
    celsius = value;
  } else if (from_unit == 'F') {
    celsius = (value - 32) * 5 / 9;
  } else {
    celsius = value - 273.15;
  }

  if (to_unit == 'C') {
    return (OperationResult){celsius, STATUS_SUCCESS};
  } else if (to_unit == 'F') {
    return (OperationResult){celsius * 9 / 5 + 32, STATUS_SUCCESS};
  } else {
    return (OperationResult){celsius + 273.15, STATUS_SUCCESS};
  }
}

OperationResult convert_length(double value, char from_unit, char to_unit) {
  double feet;

  if (from_unit != 'M' && from_unit != 'K' && from_unit != 'I' && from_unit != 'F') {
    return (OperationResult){0, STATUS_ERROR_INVALID_OPTION};
  }

  if (to_unit != 'M' && to_unit != 'K' && to_unit != 'I' && to_unit != 'F') {
    return (OperationResult){0, STATUS_ERROR_INVALID_OPTION};
  }

  if (from_unit == 'F') {
    feet = value;
  } else if (from_unit == 'M') {
    feet = value * 3.28084;
  } else if (from_unit == 'K') {
    feet = value * 3280.84;
  } else {
    feet = value * 5280;
  }

  if (to_unit == 'F') {
    return (OperationResult){feet, STATUS_SUCCESS};
  } else if (to_unit == 'M') {
    return (OperationResult){feet / 3.28084, STATUS_SUCCESS};
  } else if (to_unit == 'K') {
    return (OperationResult){feet / 3280.84, STATUS_SUCCESS};
  } else {
    return (OperationResult){feet / 5280, STATUS_SUCCESS};
  }
}

OperationResult convert_weight(double value, char from_unit, char to_unit) {
  double pounds;

  if (from_unit != 'K' && from_unit != 'P' && from_unit != 'O') {
    return (OperationResult){0, STATUS_ERROR_INVALID_OPTION};
  }

  if (to_unit != 'K' && to_unit != 'P' && to_unit != 'O') {
    return (OperationResult){0, STATUS_ERROR_INVALID_OPTION};
  }

  if (from_unit == 'P') {
    pounds = value;
  } else if (from_unit == 'K') {
    pounds = value * 2.20462;
  } else {
    pounds = value / 16;
  }

  if (to_unit == 'P') {
    return (OperationResult){pounds, STATUS_SUCCESS};
  } else if (to_unit == 'K') {
    return (OperationResult){pounds / 2.20462, STATUS_SUCCESS};
  } else {
    return (OperationResult){pounds * 16, STATUS_SUCCESS};
  }
}

OperationResult convert_time(double value, char from_unit, char to_unit) {
  double seconds;

  if (from_unit != 'S' && from_unit != 'M' && from_unit != 'H') {
    return (OperationResult){0, STATUS_ERROR_INVALID_OPTION};
  }

  if (to_unit != 'S' && to_unit != 'M' && to_unit != 'H') {
    return (OperationResult){0, STATUS_ERROR_INVALID_OPTION};
  }

  if (from_unit == 'S') {
    seconds = value;
  } else if (from_unit == 'M') {
    seconds = value * 60;
  } else {
    seconds = value * 3600;
  }

  if (to_unit == 'S') {
    return (OperationResult){seconds, STATUS_SUCCESS};
  } else if (to_unit == 'M') {
    return (OperationResult){seconds / 60, STATUS_SUCCESS};
  } else {
    return (OperationResult){seconds / 3600, STATUS_SUCCESS};
  }
}

void display_menu(void) {
  printf("%s", MSG_MENU_TITLE);
  printf("%s", MSG_MENU_OPTIONS);
}

void display_operation_header(const char *operation_name) {
  printf(FMT_OPERATION_HEADER, operation_name);
}

void display_result(OperationResult result) {
  if (result.status == STATUS_SUCCESS) {
    printf(FMT_RESULT_FLOAT, result.value);
  }
}

void display_error(OperationStatus status) {
  if (status == STATUS_ERROR_INVALID_OPTION)
    printf("%s", ERR_MSG_INVALID_OPTION);
}

void handle_temperature(void) {
  double value;
  char from_unit, to_unit;

  display_operation_header(MSG_MENU_TEMPERATURE);
  printf("%s", INPUT_VALUE);
  if (!read_double(&value))
    return;

  printf("%s", INPUT_SOURCE_UNIT_TEMPERATURE);
  if (!read_char(&from_unit))
    return;

  printf("%s", INPUT_TARGET_UNIT_TEMPERATURE);
  if (!read_char(&to_unit))
    return;

  OperationResult result = convert_temperature(value, from_unit, to_unit);

  if (result.status != STATUS_SUCCESS) {
    display_error(result.status);
  } else {
    display_result(result);
  }
}

void handle_length(void) {
  double value;
  char from_unit, to_unit;

  display_operation_header(MSG_MENU_LENGTH);
  printf("%s", INPUT_VALUE);
  if (!read_double(&value))
    return;

  printf("%s", INPUT_SOURCE_UNIT_LENGTH);
  if (!read_char(&from_unit))
    return;

  printf("%s", INPUT_TARGET_UNIT_LENGTH);
  if (!read_char(&to_unit))
    return;

  OperationResult result = convert_length(value, from_unit, to_unit);

  if (result.status != STATUS_SUCCESS) {
    display_error(result.status);
  } else {
    display_result(result);
  }
}

void handle_weight(void) {
  double value;
  char from_unit, to_unit;

  display_operation_header(MSG_MENU_WEIGHT);
  printf("%s", INPUT_VALUE);
  if (!read_double(&value))
    return;

  printf("%s", INPUT_SOURCE_UNIT_WEIGHT);
  if (!read_char(&from_unit))
    return;

  printf("%s", INPUT_TARGET_UNIT_WEIGHT);
  if (!read_char(&to_unit))
    return;

  OperationResult result = convert_weight(value, from_unit, to_unit);

  if (result.status != STATUS_SUCCESS) {
    display_error(result.status);
  } else {
    display_result(result);
  }
}

void handle_time(void) {
  double value;
  char from_unit, to_unit;

  display_operation_header(MSG_MENU_TIME);
  printf("%s", INPUT_VALUE);
  if (!read_double(&value))
    return;

  printf("%s", INPUT_SOURCE_UNIT_TIME);
  if (!read_char(&from_unit))
    return;

  printf("%s", INPUT_TARGET_UNIT_TIME);
  if (!read_char(&to_unit))
    return;

  OperationResult result = convert_time(value, from_unit, to_unit);

  if (result.status != STATUS_SUCCESS) {
    display_error(result.status);
  } else {
    display_result(result);
  }
}

void run_interactive_menu(void) {
  unsigned int option;

  while (TRUE) {
    display_menu();
    printf("%s", INPUT_OPTION);

    if (scanf("%u", &option) != 1) {
      printf("%s", ERR_MSG_INVALID_OPTION);
      clear_input_buffer();
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("%s", MSG_GOODBYE);
      break;
    }

    switch (option) {
    case OP_TEMPERATURE:
      handle_temperature();
      break;
    case OP_LENGTH:
      handle_length();
      break;
    case OP_WEIGHT:
      handle_weight();
      break;
    case OP_TIME:
      handle_time();
      break;
    default:
      printf("%s", ERR_MSG_INVALID_OPTION);
      break;
    }
  }
}
