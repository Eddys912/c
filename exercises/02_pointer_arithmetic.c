/*
 ===============================================================================
 Exercise: 02_pointer_arithmetic.c
 Description: Demonstrates pointer arithmetic for packet parsing
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Validates minimum packet size
 - Extracts header, sensor ID and value using pointer arithmetic
 - Safe byte-by-byte header reconstruction (avoids alignment issues)
 ===============================================================================
*/

#include <stdint.h>
#include <stdio.h>

#define MIN_PACKET_SIZE 6
#define HEADER_SIZE 4
#define OFFSET_SENSOR_ID 4
#define OFFSET_VALUE 5
#define FIELD_FORMAT "  %-16s %s\n"

typedef struct {
  const unsigned char *data;
  size_t size;
} Packet;

int validate_packet_size(size_t size);
uint32_t extract_header(const unsigned char *ptr);
unsigned char extract_sensor_id(const unsigned char *ptr);
unsigned char extract_value(const unsigned char *ptr);
void print_packet_info(const Packet *packet);

int main() {

  unsigned char packet_data[] = {0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0xFF};
  Packet packet = {packet_data, sizeof(packet_data)};

  printf("=== Pointer Arithmetic ===\n\n");

  if (validate_packet_size(packet.size) != 0) {
    return 1;
  }

  print_packet_info(&packet);

  return 0;
}

int validate_packet_size(size_t size) {
  if (size < MIN_PACKET_SIZE) {
    fprintf(stderr, "Error: Packet too small (minimum %d bytes required).\n", MIN_PACKET_SIZE);
    return 1;
  }
  return 0;
}

uint32_t extract_header(const unsigned char *ptr) {
  uint32_t header = 0;

  for (size_t i = 0; i < HEADER_SIZE; i++) {
    header |= (uint32_t)(*(ptr + i)) << (i * 8);
  }

  return header;
}

unsigned char extract_sensor_id(const unsigned char *ptr) { return *(ptr + OFFSET_SENSOR_ID); }

unsigned char extract_value(const unsigned char *ptr) { return *(ptr + OFFSET_VALUE); }

void print_packet_info(const Packet *packet) {
  char buf_addr[32], buf_header[32], buf_sensor[32], buf_value[32];

  sprintf(buf_addr, "%p", (const void *)packet->data);
  sprintf(buf_header, "0x%08X", extract_header(packet->data));
  sprintf(buf_sensor, "%u", extract_sensor_id(packet->data));
  sprintf(buf_value, "%u", extract_value(packet->data));

  printf("Analyzing packet at address: %s\n", buf_addr);
  printf(FIELD_FORMAT, "Extracted header:", buf_header);
  printf(FIELD_FORMAT, "Sensor ID:", buf_sensor);
  printf(FIELD_FORMAT, "Value:", buf_value);
}
