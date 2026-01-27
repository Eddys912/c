/*
 ===============================================================================
 Exercise: 06_pattern_generator.c
 Description: ASCII pattern generator (Pyramid, Diamond, etc.)
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Geometric pattern generation using nested loops
 - Configurable height and character
 - Symmetric pattern logic
 - Mathematical area approximation
 ===============================================================================
*/

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define EXIT_OPTION 6
#define MIN_HEIGHT 1
#define MAX_HEIGHT 50

void clear_input_buffer(void);
int read_integer(int *value);
int read_char(char *value);
void draw_pyramid(int h, char c);
void draw_diamond(int h, char c);
void draw_inverted_triangle(int h, char c);
void draw_staircase(int h, char c);
void draw_sine_wave(int h, char c);

int main(void) {
  int option = 0;

  while (TRUE) {
    printf("=== Pattern Generator ===\n");
    printf("1. Pyramid\n2. Diamond\n3. Inverted Triangle\n"
           "4. Staircase\n5. Sine Wave\n6. Exit\n");
    printf("Select pattern: ");

    if (!read_integer(&option)) {
      printf("Error: Invalid input. Please try again.\n");
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("Thank you for using the generator!\n");
      break;
    }

    if (option < 1 || option > 6) {
      printf("Error: Invalid input. Please try again.\n");
      continue;
    }

    int height;
    char character;

    printf("Height: ");
    if (!read_integer(&height) || height < MIN_HEIGHT || height > MAX_HEIGHT) {
      printf("Error: Invalid input. Please try again.\n");
      continue;
    }

    printf("Character: ");
    if (!read_char(&character))
      continue;

    printf("\n");
    switch (option) {
    case 1:
      draw_pyramid(height, character);
      printf("\nApproximate area: %d characters\n", height * height);
      printf("Symmetry lines: Vertical\n\n");
      break;

    case 2:
      draw_diamond(height, character);
      printf("\nApproximate area: %d characters\n", (int)(height * height * 0.5));
      printf("Symmetry lines: Vertical, Horizontal\n\n");
      break;

    case 3:
      draw_inverted_triangle(height, character);
      printf("\nApproximate area: %d characters\n", (int)(height * height * 0.5));
      printf("Symmetry lines: Vertical\n\n");
      break;

    case 4:
      draw_staircase(height, character);
      printf("\nApproximate area: %d characters\n", (height * (height + 1)) / 2);
      printf("Symmetry lines: None\n\n");
      break;

    case 5:
      draw_sine_wave(height, character);
      printf("\nApproximate area: %d characters\n", height * 10);
      printf("Symmetry lines: Periodic\n\n");
      break;
    }
  }

  return 0;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int read_integer(int *value) {
  if (scanf("%d", value) != 1) {
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

int read_char(char *value) {
  if (scanf(" %c", value) != 1) {
    clear_input_buffer();
    return FALSE;
  }
  clear_input_buffer();
  return TRUE;
}

void draw_pyramid(int h, char c) {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < h - i - 1; j++)
      printf(" ");
    for (int j = 0; j < (2 * i + 1); j++)
      printf("%c", c);
    printf("\n");
  }
}

void draw_diamond(int h, char c) {
  draw_pyramid(h, c);
  for (int i = h - 2; i >= 0; i--) {
    for (int j = 0; j < h - i - 1; j++)
      printf(" ");
    for (int j = 0; j < (2 * i + 1); j++)
      printf("%c", c);
    printf("\n");
  }
}

void draw_inverted_triangle(int h, char c) {
  for (int i = h; i >= 1; i--) {
    for (int j = 0; j < h - i; j++)
      printf(" ");
    for (int j = 0; j < (2 * i - 1); j++)
      printf("%c", c);
    printf("\n");
  }
}

void draw_staircase(int h, char c) {
  for (int i = 1; i <= h; i++) {
    for (int j = 0; j < i; j++)
      printf("%c", c);
    printf("\n");
  }
}

void draw_sine_wave(int h, char c) {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == i || j == (10 - i))
        printf("%c", c);
      else
        printf(" ");
    }
    printf("\n");
  }
}
