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

#define TITLE "=== Pointer Basics ===\n\n"
#define TITLE_SYSTEM_ENDIAN "\nSystem is %s-endian\n"
#define TITLE_TABLE_HEADER "VARIABLE", "VALUE", "ADDRESS (HEX)", "SIZE (B)"
#define TITLE_SEPARATOR "-----------------------------------------------\n"
#define TITLE_BASE_ADDRESS "\nBase Address: %p\n"

#define TEXT_TYPE_CHAR "Char"
#define TEXT_TYPE_INT "Int"
#define TEXT_TYPE_DOUBLE "Double"
#define TEXT_LITTLE_ENDIAN "little"
#define TEXT_BIG_ENDIAN "big"
#define TEXT_BYTE "  Byte [%zu] at %p: 0x%02x\n"

#define FORMAT_BUF_CHAR "'%c' (%u)"
#define FORMAT_BUF_UNSIGNED "%u"
#define FORMAT_BUF_DOUBLE "%.5f"
#define FORMAT_HEADER "%-10s %-10s %-16s %s\n"
#define FORMAT_ROW "%-10s %-10s %-16p %zu\n"

#define SAMPLE_CHAR 0x41
#define SAMPLE_INT 0x12345678
#define SAMPLE_DOUBLE 3.14159
#define ENDIAN_TEST_VALUE 0x12345678
#define LITTLE_ENDIAN_BYTE 0x78

void print_table_header(void);
void print_variable_row(const char *name, const char *value_str, const void *addr, size_t size);
void explore_memory_bytes(const void *addr, size_t size);
const char *detect_endianness(void);

int main(void) {
  unsigned char val_1b = SAMPLE_CHAR;
  unsigned int val_4b = SAMPLE_INT;
  double val_8b = SAMPLE_DOUBLE;
  char buf_c[20], buf_i[20], buf_d[20];

  sprintf(buf_c, FORMAT_BUF_CHAR, val_1b, val_1b);
  sprintf(buf_i, FORMAT_BUF_UNSIGNED, val_4b);
  sprintf(buf_d, FORMAT_BUF_DOUBLE, val_8b);

  printf(TITLE);

  print_table_header();
  print_variable_row(TEXT_TYPE_CHAR, buf_c, &val_1b, sizeof(val_1b));
  print_variable_row(TEXT_TYPE_INT, buf_i, &val_4b, sizeof(val_4b));
  print_variable_row(TEXT_TYPE_DOUBLE, buf_d, &val_8b, sizeof(val_8b));

  explore_memory_bytes(&val_4b, sizeof(val_4b));

  printf(TITLE_SYSTEM_ENDIAN, detect_endianness());

  return 0;
}

void print_table_header(void) {
  printf(FORMAT_HEADER, TITLE_TABLE_HEADER);
  printf(TITLE_SEPARATOR);
}

void print_variable_row(const char *name, const char *value_str, const void *addr, size_t size) {
  printf(FORMAT_ROW, name, value_str, addr, size);
}

void explore_memory_bytes(const void *addr, size_t size) {
  const unsigned char *byte_ptr = (const unsigned char *)addr;
  printf(TITLE_BASE_ADDRESS, addr);

  for (size_t i = 0; i < size; i++) {
    printf(TEXT_BYTE, i, (const void *)(byte_ptr + i), *(byte_ptr + i));
  }
}

const char *detect_endianness(void) {
  uint32_t test_value = ENDIAN_TEST_VALUE;
  const unsigned char *p = (const unsigned char *)&test_value;

  return (*p == LITTLE_ENDIAN_BYTE) ? TEXT_LITTLE_ENDIAN : TEXT_BIG_ENDIAN;
}
