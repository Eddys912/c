#include <stdio.h>

void print_generic(void *ptr, char type);

int main() {
  int i = 100;
  float f = 3.14;
  char c = 'Z';

  printf("=== Void Pointers ===\n\n");

  print_generic(&i, 'i');
  print_generic(&f, 'f');
  print_generic(&c, 'c');
  print_generic(&c, 'e');
  return 0;
}

void print_generic(void *ptr, char type) {
  if (ptr == NULL) {
    fprintf(stderr, "Error: NULL pointer received.\n");
    return;
  }

  switch (type) {
  case 'i':
    printf("Generic Print %-10s %d\n", "(Integer):", *(int *)ptr);
    break;
  case 'f':
    printf("Generic Print %-10s %.2f\n", "(Float):", *(float *)ptr);
    break;
  case 'c':
    printf("Generic Print %-10s %c\n", "(Char):", *(char *)ptr);
    break;
  default:
    fprintf(stderr, "Error: Unknown type '%c'\n", type);
    break;
  }
}
