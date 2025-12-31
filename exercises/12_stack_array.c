#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

void clear_input_buffer();
int read_positive(const char *prompt, unsigned int *value);
int read_menu_option(char *option);
int push(Node **top, int data);
int pop(Node **top, int *out_value);
void print_stack(const Node *top);
int is_stack_empty(const Node *top);
void free_stack(Node *top);
int build_stack(Node **top, unsigned int items);
void interactive_menu(Node **top);

int main() {
  Node *top = NULL;
  unsigned int items;

  printf("=== Stack Array (LIFO) ===\n\n");

  if (read_positive("How many items do you want to add to the stack?: ", &items) != 0) {
    return 1;
  }

  if (build_stack(&top, items) != 0) {
    free_stack(top);
    return 1;
  }

  printf("\nInitial stack contents:\n");
  if (is_stack_empty(top)) {
    printf("  (Stack is empty)\n");
  } else {
    printf("  ");
    print_stack(top);
  }

  interactive_menu(&top);

  printf("\nFreeing remaining memory...\n");
  free_stack(top);
  printf("Memory freed successfully.\n");

  return 0;
}

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int read_positive(const char *prompt, unsigned int *value) {
  printf("%s", prompt);

  if (scanf("%u", value) != 1) {
    fprintf(stderr, "Error: Invalid input.\n");
    return 1;
  }
  clear_input_buffer();

  if (*value == 0) {
    fprintf(stderr, "Error: Value must be greater than zero.\n");
    return 1;
  }

  return 0;
}

int read_menu_option(char *option) {
  printf("\nDo you want to remove an item? (Y/N): ");

  if (scanf(" %c", option) != 1) {
    fprintf(stderr, "Error: Invalid input.\n");
    return 1;
  }
  clear_input_buffer();

  return 0;
}

int push(Node **top, int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));

  if (new_node == NULL) {
    fprintf(stderr, "Error: Could not allocate memory for new node.\n");
    return 1;
  }

  new_node->value = data;
  new_node->next = *top;
  *top = new_node;

  return 0;
}

int pop(Node **top, int *out_value) {
  Node *current = *top;

  if (*top == NULL) {
    fprintf(stderr, "Error: Stack is empty.\n");
    return 1;
  }

  *out_value = current->value;
  *top = current->next;
  free(current);

  return 0;
}

void print_stack(const Node *top) {
  const Node *current = top;

  if (current == NULL) {
    printf("NULL\n");
    return;
  }

  while (current != NULL) {
    printf("[%d]", current->value);
    if (current->next != NULL) {
      printf(" -> ");
    }
    current = current->next;
  }
  printf(" -> NULL\n");
}

int is_stack_empty(const Node *top) { return top == NULL; }

void free_stack(Node *top) {
  Node *current = top;
  Node *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

int build_stack(Node **top, unsigned int items) {
  unsigned int i;
  int value;

  for (i = 0; i < items; i++) {
    printf("  Enter value %u: ", i + 1);

    if (scanf("%d", &value) != 1) {
      fprintf(stderr, "Error: Invalid value input.\n");
      return 1;
    }
    clear_input_buffer();

    if (push(top, value) != 0) {
      return 1;
    }
  }

  return 0;
}

void interactive_menu(Node **top) {
  char option;
  int value;

  printf("\n=== Interactive Pop Menu ===\n");

  while (1) {
    if (read_menu_option(&option) != 0) {
      continue;
    }

    if (option == 'Y' || option == 'y') {
      if (is_stack_empty(*top)) {
        printf("  Error: Stack is already empty.\n");
        break;
      }

      if (pop(top, &value) == 0) {
        printf("  Item [%d] removed successfully.\n", value);
      }

      printf("\nStack contents:\n  ");
      print_stack(*top);

    } else if (option == 'N' || option == 'n') {
      printf("Exiting menu.\n");
      break;

    } else {
      printf("  Invalid option. Please enter Y or N.\n");
    }
  }
}
