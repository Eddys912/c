/*
 ===============================================================================
 Exercise: 09_file_writing.c
 Description: Demonstrates file writing with timestamped log entries
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Reads user input and validates non-empty entries
 - Generates ISO 8601 timestamps for log entries
 - Appends formatted log entries to file
 - Displays complete log file contents
 - Safe file operations with error handling
 ===============================================================================
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#define TITLE "=== Writing File: %s ===\n\n"
#define TITLE_LOGS_SAVED "\nLogs saved in: %s\n"

#define TEXT_LOG_SAVED "Log saved successfully.\n"
#define TEXT_EMPTY_FILE "  (File is empty)\n"

#define INPUT_DESCRIPTION "Write a short description: "

#define FORMAT_STRING "  %s"
#define FORMAT_LOG_ENTRY "[%s] [INFO] %s\n"
#define FORMAT_TIMESTAMP "%Y-%m-%d %H:%M:%S"

#define ERR_MSG_READ_INPUT "Error: Failed to read input.\n"
#define ERR_MSG_EMPTY_LOG "Error: Empty log entry not allowed.\n"
#define ERR_MSG_OPENING_FILE "Error opening file"
#define ERR_MSG_CLOSING_FILE "Error closing file"
#define ERR_MSG_WRITE_FILE "Error: Failed to write to file.\n"

#define FILE_PATH "files/logs.txt"
#define APPEND_MODE "a"
#define READING_MODE "r"

#define BUFFER_SIZE 256
#define TIMESTAMP_SIZE 64
#define INITIAL_LOG_COUNT 0
#define EMPTY_STRING_LENGTH 0
#define FCLOSE_SUCCESS 0
#define FPRINTF_ERROR -1
#define NULL_TERMINATOR '\0'
#define NEWLINE "\n"

typedef enum {
  SUCCESS = 0,
  ERROR_INPUT_FAILED = 1,
  ERROR_FILE_OPERATION = 1,
  ERROR_EMPTY_LOG = 1
} StatusCode;

StatusCode read_user_input(char *buffer, size_t size);
FILE *open_file_safe(const char *filepath, const char *mode);
StatusCode close_file_safe(FILE *file);
void generate_timestamp(char *timestamp, size_t size);
StatusCode write_log_entry(const char *filepath, const char *message);
StatusCode display_log_file(const char *filepath);

int main(void) {
  char buffer[BUFFER_SIZE];

  printf(TITLE, FILE_PATH);

  if (read_user_input(buffer, BUFFER_SIZE) != SUCCESS) {
    return ERROR_INPUT_FAILED;
  }

  if (write_log_entry(FILE_PATH, buffer) != SUCCESS) {
    return ERROR_FILE_OPERATION;
  }

  printf(TEXT_LOG_SAVED);

  printf(TITLE_LOGS_SAVED, FILE_PATH);
  if (display_log_file(FILE_PATH) != SUCCESS) {
    return ERROR_FILE_OPERATION;
  }

  return SUCCESS;
}

StatusCode read_user_input(char *buffer, size_t size) {
  printf(INPUT_DESCRIPTION);

  if (fgets(buffer, size, stdin) == NULL) {
    fprintf(stderr, ERR_MSG_READ_INPUT);
    return ERROR_INPUT_FAILED;
  }

  *(buffer + strcspn(buffer, NEWLINE)) = NULL_TERMINATOR;

  if (strlen(buffer) == EMPTY_STRING_LENGTH) {
    fprintf(stderr, ERR_MSG_EMPTY_LOG);
    return ERROR_EMPTY_LOG;
  }

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

void generate_timestamp(char *timestamp, size_t size) {
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(timestamp, size, FORMAT_TIMESTAMP, t);
}

StatusCode write_log_entry(const char *filepath, const char *message) {
  FILE *file = open_file_safe(filepath, APPEND_MODE);
  char timestamp[TIMESTAMP_SIZE];

  if (file == NULL) {
    return ERROR_FILE_OPERATION;
  }

  generate_timestamp(timestamp, TIMESTAMP_SIZE);

  if (fprintf(file, FORMAT_LOG_ENTRY, timestamp, message) < FPRINTF_ERROR) {
    fprintf(stderr, ERR_MSG_WRITE_FILE);
    close_file_safe(file);
    return ERROR_FILE_OPERATION;
  }

  return close_file_safe(file);
}

StatusCode display_log_file(const char *filepath) {
  FILE *file = open_file_safe(filepath, READING_MODE);
  char buffer[BUFFER_SIZE];
  unsigned int log_count = INITIAL_LOG_COUNT;

  if (file == NULL) {
    return ERROR_FILE_OPERATION;
  }

  while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
    printf(FORMAT_STRING, buffer);
    log_count++;
  }

  if (log_count == INITIAL_LOG_COUNT) {
    printf(TEXT_EMPTY_FILE);
  }

  return close_file_safe(file);
}
