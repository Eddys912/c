/*
 ===============================================================================
 Exercise: 13_queue_array.c
 Description: Demonstrates queue (FIFO) implementation using linked list
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Implements queue with enqueue and dequeue operations
 - Builds initial queue from user input
 - Interactive menu for removing items one by one
 - Displays queue contents after each operation
 - Proper memory cleanup on exit
 ===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define TITLE "=== Queue Array (FIFO) ===\n\n"
#define TITLE_INITIAL_QUEUE "\nInitial queue contents:\n"
#define TITLE_INTERACTIVE_MENU "\n=== Interactive Dequeue Menu ===\n"
#define TITLE_QUEUE_CONTENTS "\nQueue contents:\n  "

#define TEXT_EMPTY_QUEUE "  (Queue is empty)\n"
#define TEXT_QUEUE_PREFIX "  "
#define TEXT_FREEING_MEMORY "\nFreeing remaining memory...\n"
#define TEXT_MEMORY_FREED "Memory freed successfully.\n"
#define TEXT_EXITING_MENU "Exiting menu.\n"
#define TEXT_ITEM_REMOVED "  Item [%d] removed successfully.\n"
#define TEXT_ARROW " -> "
#define TEXT_NULL_TERMINATOR " -> NULL\n"
#define TEXT_NULL "NULL\n"
#define TEXT_INVALID_OPTION "  Invalid option. Please enter Y or N.\n"

#define INPUT_ITEMS "How many items do you want to add to the queue?: "
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
#define ERR_MSG_QUEUE_EMPTY "Error: Queue is empty.\n"
#define ERR_MSG_QUEUE_ALREADY_EMPTY "  Error: Queue is already empty.\n"

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
  ERROR_QUEUE_EMPTY = 1
} StatusCode;

typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct {
  Node *front;
  Node *rear;
} Queue;

void clear_input_buffer(void);
StatusCode read_positive_integer(const char *prompt, unsigned int *value);
StatusCode enqueue(Queue *queue, int data);
StatusCode dequeue(Queue *queue, int *out_value);
StatusCode build_queue(Queue *queue, unsigned int items);
void free_queue(Queue *queue);
int is_queue_empty(const Queue *queue);
void print_queue(const Queue *queue);
StatusCode read_menu_option(char *option);
void interactive_menu(Queue *queue);

int main(void) {
  Queue queue = {NULL, NULL};
  unsigned int items;

  printf(TITLE);

  if (read_positive_integer(INPUT_ITEMS, &items) != SUCCESS) {
    return ERROR_INVALID_INPUT;
  }

  if (build_queue(&queue, items) != SUCCESS) {
    free_queue(&queue);
    return ERROR_INVALID_INPUT;
  }

  printf(TITLE_INITIAL_QUEUE);
  if (is_queue_empty(&queue)) {
    printf(TEXT_EMPTY_QUEUE);
  } else {
    printf(TEXT_QUEUE_PREFIX);
    print_queue(&queue);
  }

  interactive_menu(&queue);

  printf(TEXT_FREEING_MEMORY);
  free_queue(&queue);
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

StatusCode enqueue(Queue *queue, int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));

  if (new_node == NULL) {
    fprintf(stderr, ERR_MSG_COULD_ALLOCATE_NODE);
    return ERROR_ALLOCATION_FAILED;
  }

  new_node->value = data;
  new_node->next = NULL;

  if (is_queue_empty(queue)) {
    queue->front = new_node;
    queue->rear = new_node;
  } else {
    queue->rear->next = new_node;
    queue->rear = new_node;
  }

  return SUCCESS;
}

StatusCode dequeue(Queue *queue, int *out_value) {
  Node *current = queue->front;

  if (is_queue_empty(queue)) {
    fprintf(stderr, ERR_MSG_QUEUE_EMPTY);
    return ERROR_QUEUE_EMPTY;
  }

  *out_value = current->value;
  queue->front = current->next;

  if (queue->front == NULL) {
    queue->rear = NULL;
  }

  free(current);

  return SUCCESS;
}

StatusCode build_queue(Queue *queue, unsigned int items) {
  int value;

  for (unsigned int i = 0; i < items; i++) {
    printf(INPUT_VALUE, i + 1);

    if (scanf(FORMAT_INTEGER, &value) != SCANF_SUCCESS) {
      fprintf(stderr, ERR_MSG_INVALID_VALUE);
      clear_input_buffer();
      return ERROR_INVALID_INPUT;
    }
    clear_input_buffer();

    if (enqueue(queue, value) != SUCCESS) {
      return ERROR_ALLOCATION_FAILED;
    }
  }

  return SUCCESS;
}

void free_queue(Queue *queue) {
  Node *current = queue->front;
  Node *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }

  queue->front = NULL;
  queue->rear = NULL;
}

int is_queue_empty(const Queue *queue) { return queue->front == NULL; }

void print_queue(const Queue *queue) {
  const Node *current = queue->front;

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

void interactive_menu(Queue *queue) {
  char option;
  int value;

  printf(TITLE_INTERACTIVE_MENU);

  while (1) {
    if (read_menu_option(&option) != SUCCESS) {
      continue;
    }

    if (option == OPTION_YES_UPPER || option == OPTION_YES_LOWER) {
      if (is_queue_empty(queue)) {
        printf(ERR_MSG_QUEUE_ALREADY_EMPTY);
        break;
      }

      if (dequeue(queue, &value) == SUCCESS) {
        printf(TEXT_ITEM_REMOVED, value);
      }

      printf(TITLE_QUEUE_CONTENTS);
      print_queue(queue);

    } else if (option == OPTION_NO_UPPER || option == OPTION_NO_LOWER) {
      printf(TEXT_EXITING_MENU);
      break;

    } else {
      printf(TEXT_INVALID_OPTION);
    }
  }
}
