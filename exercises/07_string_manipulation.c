#include <stdio.h>
#include <stdlib.h>

void print_string(char *str);
void reverse_string(char *str);

int main() {

  int initial_length = 10;
  unsigned int n = 0;
  int c;

  printf("=== String Manipulation ===\n\n");

  char *sentence = (char *)malloc(initial_length * sizeof(char));
  if (sentence == NULL) {
    fprintf(stderr, "Error: Could not allocate memory.\n");
    return 1;
  }

  printf("Enter a string: ");
  while ((c = getchar()) != '\n' && c != EOF) {
    *(sentence + n) = (char)c;
    n++;

    if (n >= initial_length) {
      initial_length *= 2;
      char *temp = realloc(sentence, initial_length * sizeof(char));
      if (temp == NULL) {
        fprintf(stderr, "Error: Could not reallocate memory.\n");
        free(sentence);
        return 1;
      }
      sentence = temp;
    }
  }

  *(sentence + n) = '\0';

  char *clean = realloc(sentence, (n + 1) * sizeof(char));
  if (clean != NULL) {
    sentence = clean;
  } else {
    fprintf(stderr, "Warning: Could not optimize memory allocation.\n");
  }

  print_string(sentence);
  reverse_string(sentence);

  free(sentence);

  return 0;
}

void print_string(char *str) { printf("  Original string: %s\n", str); }

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

  printf("  Reversed string: %s\n", str);
}
