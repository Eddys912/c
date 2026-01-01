/*
===============================================================================
Exercise: 10_binary_files.c
Description: Demonstrates binary file operations with structured data
Platform: GNU/Linux (Arch/WSL) on x86_64
===============================================================================
Features:
- Reads sensor configuration from user input with validation
- Writes structured data to binary file using fwrite
- Reads structured data from binary file using fread
- Validates sensor status (Active/Inactive)
- Displays formatted sensor configuration
===============================================================================
*/

#include <stdio.h>
#include <string.h>

#define TITLE "=== Binary Files ===\n\n"
#define TITLE_SENSOR_CONFIG "\nSensor configuration:\n"

#define TEXT_WRITING_DATA "\nWriting data to binary file...\n"
#define TEXT_DATA_WRITTEN "Data written successfully.\n"
#define TEXT_READING_DATA "\nReading data from binary file...\n"
#define TEXT_ID "ID:"
#define TEXT_THRESHOLD "Threshold:"
#define TEXT_STATUS "Status:"
#define TEXT_STATUS_ACTIVE "Active"
#define TEXT_STATUS_INACTIVE "Inactive"

#define INPUT_SENSOR_ID "Enter sensor ID: "
#define INPUT_THRESHOLD "Enter threshold: "
#define INPUT_STATUS "Enter status (A/I): "

#define FORMAT_DISPLAY_ID "  %-10s %d\n"
#define FORMAT_DISPLAY_THRESHOLD "  %-10s %.2f\n"
#define FORMAT_DISPLAY_STATUS "  %-10s %c (%s)\n"
#define FORMAT_INTEGER "%d"
#define FORMAT_FLOAT "%f"
#define FORMAT_CHAR "%c"

#define ERR_MSG_INVALID_ID "Error: Invalid ID input.\n"
#define ERR_MSG_INVALID_THRESHOLD "Error: Invalid threshold input.\n"
#define ERR_MSG_INVALID_STATUS_INPUT "Error: Invalid status input.\n"
#define ERR_MSG_INVALID_STATUS "Error: Status must be 'A' (Active) or 'I' (Inactive).\n"
#define ERR_MSG_OPENING_FILE "Error opening file"
#define ERR_MSG_CLOSING_FILE "Error closing file"
#define ERR_MSG_WRITE_FAILED "Error: Failed to write sensor data to file.\n"
#define ERR_MSG_READ_FAILED "Error: Failed to read sensor data from file.\n"
#define ERR_MSG_EOF "Error: Unexpected end of file.\n"

#define FILE_PATH "files/sensor.bin"
#define WRITE_BINARY_MODE "wb"
#define READ_BINARY_MODE "rb"

#define STATUS_ACTIVE 'A'
#define STATUS_INACTIVE 'I'

#define SCANF_SUCCESS 1
#define FCLOSE_SUCCESS 0
#define FWRITE_SUCCESS 1
#define FREAD_SUCCESS 1
#define MEMSET_ZERO 0
#define NEWLINE_CHAR '\n'

typedef enum {
  SUCCESS = 0,
  ERROR_INPUT_FAILED = 1,
  ERROR_FILE_OPERATION = 1,
  ERROR_VALIDATION_FAILED = 1
} StatusCode;

typedef struct {
  int id;
  float threshold;
  char status;
} SensorConfig;

void clear_input_buffer(void);
StatusCode read_user_input(SensorConfig *sensor);
StatusCode validate_status(char status);
FILE *open_file_safe(const char *filepath, const char *mode);
StatusCode close_file_safe(FILE *file);
StatusCode write_sensor_to_file(const SensorConfig *sensor, const char *filepath);
StatusCode read_sensor_from_file(SensorConfig *sensor, const char *filepath);
void display_sensor(const SensorConfig *sensor);

int main(void) {
  SensorConfig sensor;

  printf(TITLE);

  if (read_user_input(&sensor) != SUCCESS) {
    return ERROR_INPUT_FAILED;
  }

  printf(TEXT_WRITING_DATA);
  if (write_sensor_to_file(&sensor, FILE_PATH) != SUCCESS) {
    return ERROR_FILE_OPERATION;
  }
  printf(TEXT_DATA_WRITTEN);

  printf(TEXT_READING_DATA);
  memset(&sensor, MEMSET_ZERO, sizeof(SensorConfig));
  if (read_sensor_from_file(&sensor, FILE_PATH) != SUCCESS) {
    return ERROR_FILE_OPERATION;
  }

  display_sensor(&sensor);

  return SUCCESS;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != NEWLINE_CHAR && c != EOF)
    ;
}

StatusCode validate_status(char status) {
  if (status != STATUS_ACTIVE && status != STATUS_INACTIVE) {
    fprintf(stderr, ERR_MSG_INVALID_STATUS);
    return ERROR_VALIDATION_FAILED;
  }
  return SUCCESS;
}

StatusCode read_user_input(SensorConfig *sensor) {
  int id;
  float threshold;
  char status;

  printf(INPUT_SENSOR_ID);
  if (scanf(FORMAT_INTEGER, &id) != SCANF_SUCCESS) {
    fprintf(stderr, ERR_MSG_INVALID_ID);
    clear_input_buffer();
    return ERROR_INPUT_FAILED;
  }
  clear_input_buffer();

  printf(INPUT_THRESHOLD);
  if (scanf(FORMAT_FLOAT, &threshold) != SCANF_SUCCESS) {
    fprintf(stderr, ERR_MSG_INVALID_THRESHOLD);
    clear_input_buffer();
    return ERROR_INPUT_FAILED;
  }
  clear_input_buffer();

  printf(INPUT_STATUS);
  if (scanf(FORMAT_CHAR, &status) != SCANF_SUCCESS) {
    fprintf(stderr, ERR_MSG_INVALID_STATUS_INPUT);
    clear_input_buffer();
    return ERROR_INPUT_FAILED;
  }
  clear_input_buffer();

  if (validate_status(status) != SUCCESS) {
    return ERROR_VALIDATION_FAILED;
  }

  sensor->id = id;
  sensor->threshold = threshold;
  sensor->status = status;

  return SUCCESS;
}

FILE *open_file_safe(const char *filepath, const char *mode) {
  FILE *file = fopen(filepath, mode);

  if (file == NULL) {
    perror(ERR_MSG_OPENING_FILE);
  }

  return file;
}

StatusCode close_file_safe(FILE *file) {
  if (fclose(file) != FCLOSE_SUCCESS) {
    perror(ERR_MSG_CLOSING_FILE);
    return ERROR_FILE_OPERATION;
  }
  return SUCCESS;
}

StatusCode write_sensor_to_file(const SensorConfig *sensor, const char *filepath) {
  FILE *file = open_file_safe(filepath, WRITE_BINARY_MODE);

  if (file == NULL) {
    return ERROR_FILE_OPERATION;
  }

  size_t written = fwrite(sensor, sizeof(SensorConfig), FWRITE_SUCCESS, file);
  if (written != FWRITE_SUCCESS) {
    fprintf(stderr, ERR_MSG_WRITE_FAILED);
    close_file_safe(file);
    return ERROR_FILE_OPERATION;
  }

  return close_file_safe(file);
}

StatusCode read_sensor_from_file(SensorConfig *sensor, const char *filepath) {
  FILE *file = open_file_safe(filepath, READ_BINARY_MODE);

  if (file == NULL) {
    return ERROR_FILE_OPERATION;
  }

  size_t read = fread(sensor, sizeof(SensorConfig), FREAD_SUCCESS, file);
  if (read != FREAD_SUCCESS) {
    if (feof(file)) {
      fprintf(stderr, ERR_MSG_EOF);
    } else {
      fprintf(stderr, ERR_MSG_READ_FAILED);
    }
    close_file_safe(file);
    return ERROR_FILE_OPERATION;
  }

  return close_file_safe(file);
}

void display_sensor(const SensorConfig *sensor) {
  printf(TITLE_SENSOR_CONFIG);
  printf(FORMAT_DISPLAY_ID, TEXT_ID, sensor->id);
  printf(FORMAT_DISPLAY_THRESHOLD, TEXT_THRESHOLD, sensor->threshold);
  printf(FORMAT_DISPLAY_STATUS, TEXT_STATUS, sensor->status,
         sensor->status == STATUS_ACTIVE ? TEXT_STATUS_ACTIVE : TEXT_STATUS_INACTIVE);
}
