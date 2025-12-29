#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int task_id;
  struct Node *next;
} Node;

void clear_input_buffer();
int read_positive(const char *prompt, unsigned int *value);
int add_node(Node **head, int id);
void print_list(const Node *head);
void free_list(Node *head);
int is_list_empty(const Node *head);

int main() {
  Node *head = NULL;
  unsigned int items, i;
  int task_id;

  printf("=== Linked List ===\n\n");

  if (read_positive("How many items do you want to add to the list?: ", &items) != 0) {
    return 1;
  }

  for (i = 0; i < items; i++) {
    printf("  Enter task ID %u: ", i + 1);

    if (scanf("%d", &task_id) != 1) {
      fprintf(stderr, "Error: Invalid task ID input.\n");
      free_list(head);
      return 1;
    }
    clear_input_buffer();

    if (add_node(&head, task_id) != 0) {
      free_list(head);
      return 1;
    }
  }

  printf("\nList contents:\n");
  if (is_list_empty(head)) {
    printf("  (List is empty)\n");
  } else {
    printf("  ");
    print_list(head);
  }

  printf("\nFreeing memory...\n");
  free_list(head);
  printf("Memory freed successfully.\n");

  return 0;
}

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
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

int add_node(Node **head, int id) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    fprintf(stderr, "Error: Could not allocate memory for new node.\n");
    return 1;
  }

  new_node->task_id = id;
  new_node->next = *head;
  *head = new_node;

  return 0;
}

void print_list(const Node *head) {
  const Node *current = head;

  while (current != NULL) {
    printf("[%d]", current->task_id);
    if (current->next != NULL) {
      printf(" -> ");
    }
    current = current->next;
  }
  printf(" -> NULL\n");
}

void free_list(Node *head) {
  Node *current = head;
  Node *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

int is_list_empty(const Node *head) { return head == NULL; }
