#include <stdio.h>

int main() {

  unsigned char val_1b = 0x41;
  unsigned int val_4b = 0x12345678;
  double val_8b = 3.14159;

  printf("=== Pointer Basics ===\n\n");

  printf("VARIABLE   VALUE      ADDRESS (HEX)    SIZE (BYTES)\n");
  printf("--------------------------------------------------\n");
  printf("%-10s %-10u %-16p %zu\n", "Char", val_1b, (void *)&val_1b, sizeof(val_1b));
  printf("%-10s %-10u %-16p %zu\n", "Int", val_4b, (void *)&val_4b, sizeof(val_4b));
  printf("%-10s %-10.5f %-16p %zu\n", "Double", val_8b, (void *)&val_8b, sizeof(val_8b));

  unsigned char *byte_explorer = (unsigned char *)&val_4b;
  printf("\nVariable Address: %p\n", (void *)&val_4b);

  for (size_t i = 0; i < sizeof(val_4b); i++) {
    printf("  Byte [%zu] at %p: 0x%02x\n", i, (void *)(byte_explorer + i), *(byte_explorer + i));
  }

  printf("\nSystem is %s-endian\n", (*(byte_explorer) == 0x78) ? "little" : "big");

  return 0;
}
