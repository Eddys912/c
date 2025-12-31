/*
 ===============================================================================
 Exercise: 01_pointer_basics.c
 Description: Demonstrates pointer fundamentals, memory addresses and endianness
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Displays variable values, addresses and sizes
 - Explores memory byte by byte
 - Detects system endianness (little/big)
 ===============================================================================
*/

#include <stdint.h>
#include <stdio.h>

#define SAMPLE_CHAR 0x41
#define SAMPLE_INT 0x12345678
#define SAMPLE_DOUBLE 3.14159
#define ENDIAN_TEST_VALUE 0x12345678
#define LITTLE_ENDIAN_BYTE 0x78
#define HEADER_FORMAT "%-10s %-10s %-16s %s\n"
#define ROW_FORMAT "%-10s %-10s %-16p %zu\n"

void print_table_header(void);
void print_variable_row(const char *name, const char *value_str, const void *addr, size_t size);
void explore_memory_bytes(const void *addr, size_t size);
const char *detect_endianness(void);

int main(void) {
  unsigned char val_1b = SAMPLE_CHAR;
  unsigned int val_4b = SAMPLE_INT;
  double val_8b = SAMPLE_DOUBLE;
  char buf_c[20], buf_i[20], buf_d[20];

  sprintf(buf_c, "'%c' (%u)", val_1b, val_1b);
  sprintf(buf_i, "%u", val_4b);
  sprintf(buf_d, "%.5f", val_8b);

  printf("=== Pointer Basics ===\n\n");

  print_table_header();
  print_variable_row("Char", buf_c, &val_1b, sizeof(val_1b));
  print_variable_row("Int", buf_i, &val_4b, sizeof(val_4b));
  print_variable_row("Double", buf_d, &val_8b, sizeof(val_8b));

  explore_memory_bytes(&val_4b, sizeof(val_4b));

  printf("\nSystem is %s-endian\n", detect_endianness());

  return 0;
}

void print_table_header(void) {
  printf(HEADER_FORMAT, "VARIABLE", "VALUE", "ADDRESS (HEX)", "SIZE (B)");
  printf("-----------------------------------------------\n");
}

void print_variable_row(const char *name, const char *value_str, const void *addr, size_t size) {
  printf(ROW_FORMAT, name, value_str, addr, size);
}

void explore_memory_bytes(const void *addr, size_t size) {
  const unsigned char *byte_ptr = (const unsigned char *)addr;
  printf("\nBase Address: %p\n", addr);

  for (size_t i = 0; i < size; i++) {
    printf("  Byte [%zu] at %p: 0x%02x\n", i, (const void *)(byte_ptr + i), *(byte_ptr + i));
  }
}

const char *detect_endianness(void) {
  uint32_t test_value = ENDIAN_TEST_VALUE;
  const unsigned char *p = (const unsigned char *)&test_value;

  return (*p == LITTLE_ENDIAN_BYTE) ? "little" : "big";
}
