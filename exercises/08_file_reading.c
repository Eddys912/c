/*
 ===============================================================================
 Exercise: 08_file_reading.c
 Description: Demonstrates file reading and line-by-line processing
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Opens and reads text file line by line
 - Displays each line with line number
 - Handles empty files gracefully
 - Proper file resource management with error checking
 ===============================================================================
*/

#include <stdio.h>

#define TITLE "=== Reading File: %s ===\n\n"

#define TEXT_LINE_FORMAT "  [Line %u] %s"
#define TEXT_EMPTY_FILE "  (File is empty)\n"

#define ERR_MSG_OPENING_FILE "Error opening file"
#define ERR_MSG_CLOSING_FILE "Error closing file"

#define FILE_PATH "files/data.txt"
#define READING_MODE "r"
#define BUFFER_SIZE 100
#define INITIAL_LINE_COUNT 1
#define FCLOSE_SUCCESS 0

typedef enum { SUCCESS = 0, ERROR_FILE_OPEN = 1, ERROR_FILE_CLOSE = 1 } StatusCode;

int main(void) {
  FILE *ptr_file = fopen(FILE_PATH, READING_MODE);
  char buffer[BUFFER_SIZE];
  unsigned int line_count = INITIAL_LINE_COUNT;

  printf(TITLE, FILE_PATH);

  if (ptr_file == NULL) {
    perror(ERR_MSG_OPENING_FILE);
    return ERROR_FILE_OPEN;
  }

  while (fgets(buffer, BUFFER_SIZE, ptr_file) != NULL) {
    printf(TEXT_LINE_FORMAT, line_count, buffer);
    line_count++;
  }

  if (line_count == INITIAL_LINE_COUNT) {
    printf(TEXT_EMPTY_FILE);
  }

  if (fclose(ptr_file) != FCLOSE_SUCCESS) {
    perror(ERR_MSG_CLOSING_FILE);
    return ERROR_FILE_CLOSE;
  }

  return SUCCESS;
}
