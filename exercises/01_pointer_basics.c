#include <stdio.h>

int main() {

  unsigned char one_byte = 0x41;
  unsigned int four_bytes = 0x12345678;
  double eight_bytes = 3.14159;

  printf("=== Pointer Basics ===\n\n");
  printf("VARIABLE  VALUE      ADDRESS (HEX)    SIZE (BYTES)\n");
  printf("--------------------------------------------------\n");
  printf("Char      %-10u %-16p %zu\n", one_byte, (void *)&one_byte, sizeof(one_byte));
  printf("Int       %-10u %-16p %zu\n", four_bytes, (void *)&four_bytes, sizeof(four_bytes));
  printf("Double    %-10.5f %-16p %zu\n", eight_bytes, (void *)&eight_bytes, sizeof(eight_bytes));

  unsigned char *byte_explorer = (unsigned char *)&four_bytes;
  printf("\nVariable Address: %p\n", (void *)&four_bytes);
  for (size_t i = 0; i < sizeof(four_bytes); i++) {
    printf("  Byte [%d] at %p: 0x%02x\n", i, (void *)(byte_explorer + i), *(byte_explorer + i));
  }

  return 0;
}
