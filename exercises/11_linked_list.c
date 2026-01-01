/*
 ===============================================================================
 Exercise: 11_linked_list.c
 Description: Demonstrates singly linked list implementation for task management
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Creates singly linked list with dynamic allocation
 - Adds nodes at the head of the list
 - Traverses and displays list contents
 - Proper memory deallocation of all nodes
 - Handles empty list cases gracefully
 ===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define TITLE "=== Linked List ===\n\n"
#define TITLE_LIST_CONTENTS "\nList contents:\n"

#define TEXT_EMPTY_LIST "  (List is empty)\n"
#define TEXT_FREEING_MEMORY "\nFreeing memory...\n"
#define TEXT_MEMORY_FREED "Memory freed successfully.\n"
#define TEXT_LIST_PREFIX "  "
#define TEXT_ARROW " -> "
#define TEXT_NULL_TERMINATOR " -> NULL\n"

#define INPUT_ITEMS "How many items do you want to add to the list?: "
#define INPUT_TASK_ID "  Enter task ID %u: "

#define FORMAT_STRING "%s"
#define FORMAT_NODE "[%d]"
#define FORMAT_UNSIGNED "%u"
#define FORMAT_INTEGER "%d"

#define ERR_MSG_INVALID_INPUT "Error: Invalid input.\n"
#define ERR_MSG_INVALID_TASK_ID "Error: Invalid task ID input.\n"
#define ERR_MSG_GREATER_THAN_ZERO "Error: Value must be greater than zero.\n"
#define ERR_MSG_COULD_ALLOCATE_NODE "Error: Could not allocate memory for new node.\n"

#define MIN_VALUE 1
#define SCANF_SUCCESS 1
#define NEWLINE_CHAR '\n'

typedef enum {
  SUCCESS = 0,
  ERROR_INVALID_INPUT = 1,
  ERROR_ALLOCATION_FAILED = 1,
  ERROR_ZERO_VALUE = 1
} StatusCode;

typedef struct Node {
  int task_id;
  struct Node *next;
} Node;

void clear_input_buffer(void);
StatusCode read_positive_integer(const char *prompt, unsigned int *value);
StatusCode add_node(Node **head, int id);
void print_list(const Node *head);
void free_list(Node *head);
int is_list_empty(const Node *head);

int main(void) {
  Node *head = NULL;
  unsigned int items;
  int task_id;

  printf(TITLE);

  if (read_positive_integer(INPUT_ITEMS, &items) != SUCCESS) {
    return ERROR_INVALID_INPUT;
  }

  for (unsigned int i = 0; i < items; i++) {
    printf(INPUT_TASK_ID, i + 1);

    if (scanf(FORMAT_INTEGER, &task_id) != SCANF_SUCCESS) {
      fprintf(stderr, ERR_MSG_INVALID_TASK_ID);
      clear_input_buffer();
      free_list(head);
      return ERROR_INVALID_INPUT;
    }
    clear_input_buffer();

    if (add_node(&head, task_id) != SUCCESS) {
      free_list(head);
      return ERROR_ALLOCATION_FAILED;
    }
  }

  printf(TITLE_LIST_CONTENTS);
  if (is_list_empty(head)) {
    printf(TEXT_EMPTY_LIST);
  } else {
    printf(TEXT_LIST_PREFIX);
    print_list(head);
  }

  printf(TEXT_FREEING_MEMORY);
  free_list(head);
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

StatusCode add_node(Node **head, int id) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    fprintf(stderr, ERR_MSG_COULD_ALLOCATE_NODE);
    return ERROR_ALLOCATION_FAILED;
  }

  new_node->task_id = id;
  new_node->next = *head;
  *head = new_node;

  return SUCCESS;
}

void print_list(const Node *head) {
  const Node *current = head;

  while (current != NULL) {
    printf(FORMAT_NODE, current->task_id);
    if (current->next != NULL) {
      printf(TEXT_ARROW);
    }
    current = current->next;
  }
  printf(TEXT_NULL_TERMINATOR);
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
