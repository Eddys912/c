/*
 ===============================================================================
 Exercise: 06_void_pointers.c
 Description: Demonstrates void pointers for generic type handling
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Uses void pointers to handle multiple data types generically
 - Type discrimination via character codes
 - Safe pointer validation before dereferencing
 - Demonstrates type casting from void pointer
 ===============================================================================
*/

#include <stdio.h>

#define TITLE "=== Void Pointers ===\n\n"

#define TEXT_GENERIC_PRINT "Generic Print %-10s %s\n"
#define TEXT_TYPE_INTEGER "(Integer):"
#define TEXT_TYPE_FLOAT "(Float):"
#define TEXT_TYPE_CHAR "(Char):"

#define FORMAT_INTEGER "%d"
#define FORMAT_FLOAT "%.2f"
#define FORMAT_CHAR "%c"

#define ERR_MSG_NULL_POINTER "Error: NULL pointer received.\n"
#define ERR_MSG_UNKNOWN_TYPE "Error: Unknown type '%c'\n"

#define TYPE_INT 'i'
#define TYPE_FLOAT 'f'
#define TYPE_CHAR 'c'

#define SAMPLE_INT 100
#define SAMPLE_FLOAT 3.14f
#define SAMPLE_CHAR 'Z'
#define SAMPLE_UNKNOWN_TYPE 'e'

void print_generic(const void *ptr, char type);

int main(void) {
  int i = SAMPLE_INT;
  float f = SAMPLE_FLOAT;
  char c = SAMPLE_CHAR;

  printf(TITLE);

  print_generic(&i, TYPE_INT);
  print_generic(&f, TYPE_FLOAT);
  print_generic(&c, TYPE_CHAR);
  print_generic(&c, SAMPLE_UNKNOWN_TYPE);

  return 0;
}

void print_generic(const void *ptr, char type) {
  char buf[32];

  if (ptr == NULL) {
    fprintf(stderr, ERR_MSG_NULL_POINTER);
    return;
  }

  switch (type) {
  case TYPE_INT:
    sprintf(buf, FORMAT_INTEGER, *(const int *)ptr);
    printf(TEXT_GENERIC_PRINT, TEXT_TYPE_INTEGER, buf);
    break;
  case TYPE_FLOAT:
    sprintf(buf, FORMAT_FLOAT, *(const float *)ptr);
    printf(TEXT_GENERIC_PRINT, TEXT_TYPE_FLOAT, buf);
    break;
  case TYPE_CHAR:
    sprintf(buf, FORMAT_CHAR, *(const char *)ptr);
    printf(TEXT_GENERIC_PRINT, TEXT_TYPE_CHAR, buf);
    break;
  default:
    fprintf(stderr, ERR_MSG_UNKNOWN_TYPE, type);
    break;
  }
}
