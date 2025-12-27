#include <stdio.h>

#define MIN_PACKET_SIZE 6

int main() {

  unsigned char packet[] = {0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0xFF};
  unsigned char *ptr_packet = packet;
  size_t packet_size = sizeof(packet);

  printf("=== Pointer Arithmetic ===\n\n");

  if (packet_size < MIN_PACKET_SIZE) {
    fprintf(stderr, "Error: Packet too small (minimum %d bytes required).\n", MIN_PACKET_SIZE);
    return 1;
  }

  printf("Analyzing packet at address: %p\n", (void *)ptr_packet);
  printf("%-18s 0x%X\n", "  Extracted header:", *(unsigned int *)ptr_packet);
  printf("%-19s %d\n", "  Sensor ID:", *(ptr_packet + 4));
  printf("%-19s %d\n", "  Value:", *(ptr_packet + 5));

  return 0;
}
