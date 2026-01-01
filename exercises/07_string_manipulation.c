/*
 ===============================================================================
 Exercise: 07_string_manipulation.c
 Description: Demonstrates dynamic string allocation and manipulation
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Reads string with dynamic buffer growth (starts at 10, doubles as needed)
 - Reverses string in-place using pointer arithmetic
 - Optimizes final memory allocation to exact size
 - Handles realloc failures gracefully
 ===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define TITLE "=== String Manipulation ===\n\n"

#define TEXT_ORIGINAL_STRING "Original string"
#define TEXT_REVERSED_STRING "Reversed string"
#define TEXT_STRING_OUTPUT "  %s: %s\n"

#define INPUT_STRING "Enter a string: "

#define FORMAT_STRING "%s"

#define ERR_MSG_COULD_ALLOCATE "Error: Could not allocate memory.\n"
#define ERR_MSG_COULD_REALLOCATE "Error: Could not reallocate memory.\n"

#define WARN_MSG_OPTIMIZE "Warning: Could not optimize memory allocation.\n"

#define INITIAL_BUFFER_SIZE 10
#define BUFFER_GROWTH_FACTOR 2
#define NULL_TERMINATOR '\0'
#define NEWLINE_CHAR '\n'

typedef enum { SUCCESS = 0, ERROR_ALLOCATION_FAILED = 1 } StatusCode;

char *read_dynamic_string(const char *prompt);
void print_string(const char *msg, const char *str);
void reverse_string(char *str);

int main(void) {
  char *sentence;

  printf(TITLE);

  sentence = read_dynamic_string(INPUT_STRING);
  if (sentence == NULL) {
    return ERROR_ALLOCATION_FAILED;
  }

  print_string(TEXT_ORIGINAL_STRING, sentence);
  reverse_string(sentence);
  print_string(TEXT_REVERSED_STRING, sentence);

  free(sentence);
  sentence = NULL;

  return SUCCESS;
}

char *read_dynamic_string(const char *prompt) {
  unsigned int buffer_size = INITIAL_BUFFER_SIZE;
  unsigned int length = 0;
  int c;
  char *str = (char *)malloc(buffer_size * sizeof(char));

  if (str == NULL) {
    fprintf(stderr, ERR_MSG_COULD_ALLOCATE);
    return NULL;
  }

  printf(FORMAT_STRING, prompt);

  while ((c = getchar()) != NEWLINE_CHAR && c != EOF) {
    *(str + length) = (char)c;
    length++;

    if (length >= buffer_size) {
      buffer_size *= BUFFER_GROWTH_FACTOR;
      char *temp = (char *)realloc(str, buffer_size * sizeof(char));
      if (temp == NULL) {
        fprintf(stderr, ERR_MSG_COULD_REALLOCATE);
        free(str);
        return NULL;
      }
      str = temp;
    }
  }

  *(str + length) = NULL_TERMINATOR;

  char *optimized = (char *)realloc(str, (length + 1) * sizeof(char));
  if (optimized != NULL) {
    str = optimized;
  } else {
    fprintf(stderr, WARN_MSG_OPTIMIZE);
  }

  return str;
}

void print_string(const char *msg, const char *str) { printf(TEXT_STRING_OUTPUT, msg, str); }

void reverse_string(char *str) {
  char *start = str;
  char *end = str;
  char temp;

  while (*end != NULL_TERMINATOR) {
    end++;
  }

  if (end != str) {
    end--;
  }

  while (start < end) {
    temp = *start;
    *start = *end;
    *end = temp;

    start++;
    end--;
  }
}
