/*
 ===============================================================================
 Exercise: 12_stack_array.c
 Description: Demonstrates stack (LIFO) implementation using linked list
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Implements stack with push and pop operations
 - Builds initial stack from user input
 - Interactive menu for removing items one by one
 - Displays stack contents after each operation
 - Proper memory cleanup on exit
 ===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define TITLE "=== Stack Array (LIFO) ===\n\n"
#define TITLE_INITIAL_STACK "\nInitial stack contents:\n"
#define TITLE_INTERACTIVE_MENU "\n=== Interactive Pop Menu ===\n"
#define TITLE_STACK_CONTENTS "\nStack contents:\n  "

#define TEXT_EMPTY_STACK "  (Stack is empty)\n"
#define TEXT_STACK_PREFIX "  "
#define TEXT_FREEING_MEMORY "\nFreeing remaining memory...\n"
#define TEXT_MEMORY_FREED "Memory freed successfully.\n"
#define TEXT_EXITING_MENU "Exiting menu.\n"
#define TEXT_ITEM_REMOVED "  Item [%d] removed successfully.\n"
#define TEXT_ARROW " -> "
#define TEXT_NULL_TERMINATOR " -> NULL\n"
#define TEXT_NULL "NULL\n"
#define TEXT_INVALID_OPTION "  Invalid option. Please enter Y or N.\n"

#define INPUT_ITEMS "How many items do you want to add to the stack?: "
#define INPUT_VALUE "  Enter value %u: "
#define INPUT_MENU_OPTION "\nDo you want to remove an item? (Y/N): "

#define FORMAT_NODE "[%d]"
#define FORMAT_CHAR "%c"
#define FORMAT_STRING "%s"
#define FORMAT_UNSIGNED "%u"
#define FORMAT_INTEGER "%d"

#define ERR_MSG_INVALID_INPUT "Error: Invalid input.\n"
#define ERR_MSG_INVALID_VALUE "Error: Invalid value input.\n"
#define ERR_MSG_GREATER_THAN_ZERO "Error: Value must be greater than zero.\n"
#define ERR_MSG_COULD_ALLOCATE_NODE "Error: Could not allocate memory for new node.\n"
#define ERR_MSG_STACK_EMPTY "Error: Stack is empty.\n"
#define ERR_MSG_STACK_ALREADY_EMPTY "  Error: Stack is already empty.\n"

#define MIN_VALUE 1
#define SCANF_SUCCESS 1
#define OPTION_YES_UPPER 'Y'
#define OPTION_YES_LOWER 'y'
#define OPTION_NO_UPPER 'N'
#define OPTION_NO_LOWER 'n'
#define NEWLINE_CHAR '\n'

typedef enum {
  SUCCESS = 0,
  ERROR_INVALID_INPUT = 1,
  ERROR_ALLOCATION_FAILED = 1,
  ERROR_ZERO_VALUE = 1,
  ERROR_STACK_EMPTY = 1
} StatusCode;

typedef struct Node {
  int value;
  struct Node *next;
} Node;

void clear_input_buffer(void);
StatusCode read_positive_integer(const char *prompt, unsigned int *value);
StatusCode push(Node **top, int data);
StatusCode pop(Node **top, int *out_value);
StatusCode build_stack(Node **top, unsigned int items);
void free_stack(Node *top);
int is_stack_empty(const Node *top);
void print_stack(const Node *top);
StatusCode read_menu_option(char *option);
void interactive_menu(Node **top);

int main(void) {
  Node *top = NULL;
  unsigned int items;

  printf(TITLE);

  if (read_positive_integer(INPUT_ITEMS, &items) != SUCCESS) {
    return ERROR_INVALID_INPUT;
  }

  if (build_stack(&top, items) != SUCCESS) {
    free_stack(top);
    return ERROR_INVALID_INPUT;
  }

  printf(TITLE_INITIAL_STACK);
  if (is_stack_empty(top)) {
    printf(TEXT_EMPTY_STACK);
  } else {
    printf(TEXT_STACK_PREFIX);
    print_stack(top);
  }

  interactive_menu(&top);

  printf(TEXT_FREEING_MEMORY);
  free_stack(top);
  printf(TEXT_MEMORY_FREED);

  return SUCCESS;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != NEWLINE_CHAR && c != EOF)
    ;
}

StatusCode read_positive_integer(const char *prompt, unsigned int *value) {
  printf(FORMAT_STRING, prompt);

  if (scanf(FORMAT_UNSIGNED, value) != SCANF_SUCCESS) {
    fprintf(stderr, ERR_MSG_INVALID_INPUT);
    clear_input_buffer();
    return ERROR_INVALID_INPUT;
  }
  clear_input_buffer();

  if (*value < MIN_VALUE) {
    fprintf(stderr, ERR_MSG_GREATER_THAN_ZERO);
    return ERROR_ZERO_VALUE;
  }

  return SUCCESS;
}

StatusCode push(Node **top, int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));

  if (new_node == NULL) {
    fprintf(stderr, ERR_MSG_COULD_ALLOCATE_NODE);
    return ERROR_ALLOCATION_FAILED;
  }

  new_node->value = data;
  new_node->next = *top;
  *top = new_node;

  return SUCCESS;
}

StatusCode pop(Node **top, int *out_value) {
  Node *current = *top;

  if (*top == NULL) {
    fprintf(stderr, ERR_MSG_STACK_EMPTY);
    return ERROR_STACK_EMPTY;
  }

  *out_value = current->value;
  *top = current->next;
  free(current);

  return SUCCESS;
}

StatusCode build_stack(Node **top, unsigned int items) {
  int value;

  for (unsigned int i = 0; i < items; i++) {
    printf(INPUT_VALUE, i + 1);

    if (scanf(FORMAT_INTEGER, &value) != SCANF_SUCCESS) {
      fprintf(stderr, ERR_MSG_INVALID_VALUE);
      clear_input_buffer();
      return ERROR_INVALID_INPUT;
    }
    clear_input_buffer();

    if (push(top, value) != SUCCESS) {
      return ERROR_ALLOCATION_FAILED;
    }
  }

  return SUCCESS;
}

void free_stack(Node *top) {
  Node *current = top;
  Node *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

int is_stack_empty(const Node *top) { return top == NULL; }

void print_stack(const Node *top) {
  const Node *current = top;

  if (current == NULL) {
    printf(TEXT_NULL);
    return;
  }

  while (current != NULL) {
    printf(FORMAT_NODE, current->value);
    if (current->next != NULL) {
      printf(TEXT_ARROW);
    }
    current = current->next;
  }
  printf(TEXT_NULL_TERMINATOR);
}

StatusCode read_menu_option(char *option) {
  printf(INPUT_MENU_OPTION);

  if (scanf(FORMAT_CHAR, option) != SCANF_SUCCESS) {
    fprintf(stderr, ERR_MSG_INVALID_INPUT);
    clear_input_buffer();
    return ERROR_INVALID_INPUT;
  }
  clear_input_buffer();

  return SUCCESS;
}

void interactive_menu(Node **top) {
  char option;
  int value;

  printf(TITLE_INTERACTIVE_MENU);

  while (1) {
    if (read_menu_option(&option) != SUCCESS) {
      continue;
    }

    if (option == OPTION_YES_UPPER || option == OPTION_YES_LOWER) {
      if (is_stack_empty(*top)) {
        printf(ERR_MSG_STACK_ALREADY_EMPTY);
        break;
      }

      if (pop(top, &value) == SUCCESS) {
        printf(TEXT_ITEM_REMOVED, value);
      }

      printf(TITLE_STACK_CONTENTS);
      print_stack(*top);

    } else if (option == OPTION_NO_UPPER || option == OPTION_NO_LOWER) {
      printf(TEXT_EXITING_MENU);
      break;

    } else {
      printf(TEXT_INVALID_OPTION);
    }
  }
}
