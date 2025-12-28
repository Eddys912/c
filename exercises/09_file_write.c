#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 256
#define TIMESTAMP_SIZE 64
#define FILE_PATH "files/logs.txt"

int read_user_input(char *buffer, size_t size);
void generate_timestamp(char *timestamp, size_t size);
int write_log_entry(const char *filepath, const char *message);
int display_log_file(const char *filepath);
FILE *open_file_safe(const char *filepath, const char *mode);
int close_file_safe(FILE *file);

int main() {
  char buffer[BUFFER_SIZE];
  char timestamp[TIMESTAMP_SIZE];

  printf("=== Writing File: %s ===\n\n", FILE_PATH);

  if (read_user_input(buffer, BUFFER_SIZE) != 0) {
    return 1;
  }

  if (write_log_entry(FILE_PATH, buffer) != 0) {
    return 1;
  }

  printf("Log saved successfully.\n");

  printf("\nLogs saved in: %s\n\n", FILE_PATH);
  if (display_log_file(FILE_PATH) != 0) {
    return 1;
  }

  return 0;
}

int read_user_input(char *buffer, size_t size) {
  printf("Write a short description: ");

  if (fgets(buffer, size, stdin) == NULL) {
    fprintf(stderr, "Error: Failed to read input.\n");
    return 1;
  }

  buffer[strcspn(buffer, "\n")] = '\0';

  if (strlen(buffer) == 0) {
    fprintf(stderr, "Error: Empty log entry not allowed.\n");
    return 1;
  }

  return 0;
}

FILE *open_file_safe(const char *filepath, const char *mode) {
  FILE *file = fopen(filepath, mode);

  if (file == NULL) {
    perror("Error opening file");
  }

  return file;
}

int close_file_safe(FILE *file) {
  if (fclose(file) != 0) {
    perror("Error closing file");
    return 1;
  }
  return 0;
}

void generate_timestamp(char *timestamp, size_t size) {
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(timestamp, size, "%Y-%m-%d %H:%M:%S", t);
}

int write_log_entry(const char *filepath, const char *message) {
  FILE *file = open_file_safe(filepath, "a");
  char timestamp[TIMESTAMP_SIZE];

  if (file == NULL) {
    return 1;
  }

  generate_timestamp(timestamp, TIMESTAMP_SIZE);

  if (fprintf(file, "[%s] [INFO] %s\n", timestamp, message) < 0) {
    fprintf(stderr, "Error: Failed to write to file.\n");
    close_file_safe(file);
    return 1;
  }

  return close_file_safe(file);
}

int display_log_file(const char *filepath) {
  FILE *file = open_file_safe(filepath, "r");
  char buffer[BUFFER_SIZE];
  unsigned int count = 0;

  if (file == NULL) {
    return 1;
  }

  while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
    printf("  %s", buffer);
    count++;
  }

  if (count == 0) {
    printf("  (File is empty)\n");
  }

  return close_file_safe(file);
}
