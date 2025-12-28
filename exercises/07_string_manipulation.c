#include <stdio.h>
#include <stdlib.h>

#define INITIAL_BUFFER_SIZE 10

char *read_dynamic_string(const char *prompt);
void print_string(const char *str);
void reverse_string(char *str);

int main() {
  char *sentence;

  printf("=== String Manipulation ===\n\n");

  sentence = read_dynamic_string("Enter a string: ");
  if (sentence == NULL) {
    return 1;
  }

  print_string(sentence);
  reverse_string(sentence);
  print_string(sentence);

  free(sentence);

  return 0;
}

char *read_dynamic_string(const char *prompt) {
  int buffer_size = INITIAL_BUFFER_SIZE;
  unsigned int length = 0;
  int c;
  char *str = (char *)malloc(buffer_size * sizeof(char));

  if (str == NULL) {
    fprintf(stderr, "Error: Could not allocate memory.\n");
    return NULL;
  }

  printf("%s", prompt);

  while ((c = getchar()) != '\n' && c != EOF) {
    *(str + length) = (char)c;
    length++;

    if (length >= buffer_size) {
      buffer_size *= 2;
      char *temp = realloc(str, buffer_size * sizeof(char));
      if (temp == NULL) {
        fprintf(stderr, "Error: Could not reallocate memory.\n");
        free(str);
        return NULL;
      }
      str = temp;
    }
  }

  *(str + length) = '\0';

  char *optimized = realloc(str, (length + 1) * sizeof(char));
  if (optimized != NULL) {
    str = optimized;
  } else {
    fprintf(stderr, "Warning: Could not optimize memory allocation.\n");
  }

  return str;
}

void print_string(const char *str) { printf("  String: %s\n", str); }

void reverse_string(char *str) {
  char *start = str;
  char *end = str;
  char temp;

  while (*end != '\0') {
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
