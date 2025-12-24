#include <stdio.h>

int main() {

  unsigned char packet[] = {0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0xFF};
  unsigned char *ptr_packet = packet;

  printf("=== Pointer Arithmetic ===\n\n");
  printf("Analyzing packet at address: %p\n", (void *)ptr_packet);
  printf("%-18s 0x%X\n", "  Extracted header:", *(unsigned int *)ptr_packet);
  printf("%-19s %d\n", "  Sensor ID:", *(ptr_packet + 4));
  printf("%-19s %d\n", "  Value:", *(ptr_packet + 5));

  return 0;
}
