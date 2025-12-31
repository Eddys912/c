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

#define TITLE "=== Pointer Arithmetic ===\n\n"
#define TITLE_ANALYZING_PACKET "Analyzing packet at address: %s\n"

#define TEXT_EXTRACTED_HEADER "Extracted header:"
#define TEXT_SENSOR_ID "Sensor ID:"
#define TEXT_VALUE "Value:"

#define FORMAT_BUF_ADDR "%p"
#define FORMAT_BUF_HEADER "0x%08X"
#define FORMAT_BUF_SENSOR "%u"
#define FORMAT_BUF_VALUE "%u"
#define FORMAT_FIELD "  %-16s %s\n"

#define ERR_MSG_PACKET_SMALL "Error: Packet too small (minimum %d bytes required).\n"

#define MIN_PACKET_SIZE 6
#define HEADER_SIZE 4
#define OFFSET_SENSOR_ID 4
#define OFFSET_VALUE 5

typedef struct {
  const unsigned char *data;
  size_t size;
} Packet;

int validate_packet_size(size_t size);
uint32_t extract_header(const unsigned char *ptr);
unsigned char extract_sensor_id(const unsigned char *ptr);
unsigned char extract_value(const unsigned char *ptr);
void print_packet_info(const Packet *packet);

int main(void) {

  unsigned char packet_data[] = {0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0xFF};
  Packet packet = {packet_data, sizeof(packet_data)};

  printf(TITLE);

  if (validate_packet_size(packet.size) != 0) {
    return 1;
  }

  print_packet_info(&packet);

  return 0;
}

int validate_packet_size(size_t size) {
  if (size < MIN_PACKET_SIZE) {
    fprintf(stderr, ERR_MSG_PACKET_SMALL, MIN_PACKET_SIZE);
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

  sprintf(buf_addr, FORMAT_BUF_ADDR, (const void *)packet->data);
  sprintf(buf_header, FORMAT_BUF_HEADER, extract_header(packet->data));
  sprintf(buf_sensor, FORMAT_BUF_SENSOR, extract_sensor_id(packet->data));
  sprintf(buf_value, FORMAT_BUF_VALUE, extract_value(packet->data));

  printf(TITLE_ANALYZING_PACKET, buf_addr);
  printf(FORMAT_FIELD, TEXT_EXTRACTED_HEADER, buf_header);
  printf(FORMAT_FIELD, TEXT_SENSOR_ID, buf_sensor);
  printf(FORMAT_FIELD, TEXT_VALUE, buf_value);
}
