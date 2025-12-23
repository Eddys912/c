#include <stdio.h>

int main() {

  unsigned char packet[] = {0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0xFF};
  unsigned char *ptr_packet = packet;

  printf("=== Pointer Arithmetic ===\n\n");
  printf("Analyzing packet at address: %p\n", (void *)ptr_packet);
  printf("  Extracted header: 0x%X\n", *(unsigned int *)ptr_packet);
  printf("  Sensor ID:        %d\n", *(ptr_packet + 4));
  printf("  Value:            %d\n", *(ptr_packet + 5));

  return 0;
}
