#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define EXIT_OPTION 6
#define MIN_HEIGHT 1
#define MAX_HEIGHT 50

static const char *MSG_MENU_TITLE = "=== Pattern Generator ===\n";
static const char *MSG_MENU_OPTIONS = "1. Pyramid\n2. Diamond\n3. Inverted Triangle\n"
                                      "4. Staircase\n5. Sine Wave\n6. Exit\n";
static const char *MSG_GOODBYE = "Thank you for using the generator!\n";

static const char *INPUT_OPTION = "Select pattern: ";
static const char *INPUT_HEIGHT = "Height: ";
static const char *INPUT_CHAR = "Character: ";

static const char *LABEL_AREA = "\nApproximate area: %d characters\n";
static const char *LABEL_SYMMETRY = "Symmetry lines: %s\n\n";

static const char *SYMMETRY_VERTICAL = "Vertical";
static const char *SYMMETRY_VERTICAL_HORIZONTAL = "Vertical, Horizontal";
static const char *SYMMETRY_NONE = "None";
static const char *SYMMETRY_PERIODIC = "Periodic";

static const char *ERR_MSG_INVALID = "Error: Invalid input. Please try again.\n";

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
    printf("%s", MSG_MENU_TITLE);
    printf("%s", MSG_MENU_OPTIONS);
    printf("%s", INPUT_OPTION);

    if (!read_integer(&option)) {
      printf("%s", ERR_MSG_INVALID);
      continue;
    }

    if (option == EXIT_OPTION) {
      printf("%s", MSG_GOODBYE);
      break;
    }

    if (option < 1 || option > 6) {
      printf("%s", ERR_MSG_INVALID);
      continue;
    }

    int height;
    char character;

    printf("%s", INPUT_HEIGHT);
    if (!read_integer(&height) || height < MIN_HEIGHT || height > MAX_HEIGHT) {
      printf("%s", ERR_MSG_INVALID);
      continue;
    }

    printf("%s", INPUT_CHAR);
    if (!read_char(&character))
      continue;

    printf("\n");
    switch (option) {
    case 1:
      draw_pyramid(height, character);
      printf(LABEL_AREA, height * height);
      printf(LABEL_SYMMETRY, SYMMETRY_VERTICAL);
      break;

    case 2:
      draw_diamond(height, character);
      printf(LABEL_AREA, (int)(height * height * 0.5));
      printf(LABEL_SYMMETRY, SYMMETRY_VERTICAL_HORIZONTAL);
      break;

    case 3:
      draw_inverted_triangle(height, character);
      printf(LABEL_AREA, (int)(height * height * 0.5));
      printf(LABEL_SYMMETRY, SYMMETRY_VERTICAL);
      break;

    case 4:
      draw_staircase(height, character);
      printf(LABEL_AREA, (height * (height + 1)) / 2);
      printf(LABEL_SYMMETRY, SYMMETRY_NONE);
      break;

    case 5:
      draw_sine_wave(height, character);
      printf(LABEL_AREA, height * 10);
      printf(LABEL_SYMMETRY, SYMMETRY_PERIODIC);
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
