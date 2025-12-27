#include <stdio.h>

#define BUFFER_SIZE 100
#define FILE_PATH "files/data.txt"

int main() {
  FILE *ptr_file = fopen(FILE_PATH, "r");
  char buffer[BUFFER_SIZE];
  unsigned int count = 1;

  printf("=== Reading File: %s ===\n\n", FILE_PATH);

  if (ptr_file == NULL) {
    perror("Error opening file");
    return 1;
  }

  while (fgets(buffer, BUFFER_SIZE, ptr_file) != NULL) {
    printf("  [Line %u]: %s", count, buffer);
    count++;
  }

  if (count == 1) {
    printf("  (File is empty)\n");
  }

  if (fclose(ptr_file) != 0) {
    perror("Error closing file");
    return 1;
  }

  return 0;
}
