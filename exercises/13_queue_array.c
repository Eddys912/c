/*
 ===============================================================================
 Exercise: 13_queue_fifo.c
 Description: Demonstrates queue (FIFO) implementation using linked list
 Platform: GNU/Linux (Arch/WSL) on x86_64
 ===============================================================================
 Features:
 - Implements queue with enqueue and dequeue operations
 - Interactive menu for adding, removing and displaying elements
 - Maintains front and rear pointers for efficient operations
 - Handles empty queue cases gracefully
 - Proper memory cleanup on exit
 ===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define TITLE "=== Queue Array (FIFO) ===\n\n"

#define TEXT_MENU_ENQUEUE "1. Enqueue\n"
#define TEXT_MENU_DEQUEUE "2. Dequeue\n"
#define TEXT_MENU_SHOW "3. Show\n"
#define TEXT_MENU_EXIT "4. Exit\n"
#define TEXT_ENQUEUED "  Value %d enqueued successfully\n"
#define TEXT_DEQUEUED "  Value %d dequeued successfully\n"
#define TEXT_EMPTY_QUEUE "  Queue is empty\n"
#define TEXT_EXITING "Exiting program...\n"
#define TEXT_QUEUE_PREFIX "Queue: "
#define TEXT_ARROW " -> "
#define TEXT_NULL_TERMINATOR "NULL\n"

#define INPUT_OPTION "Enter option: "
#define INPUT_VALUE "  Enter value: "

#define FORMAT_NODE "[%d]"
#define FORMAT_INTEGER "%d"

#define ERR_MSG_INVALID_OPTION "  Invalid option. Please try again.\n"
#define ERR_MSG_EMPTY_DEQUEUE "  Error: Cannot dequeue from empty queue.\n"
#define ERR_MSG_INVALID_INPUT "  Error: Invalid input.\n"
#define ERR_MSG_COULD_ALLOCATE_NODE "  Error: Could not allocate memory for new node.\n"

#define MENU_OPTION_ENQUEUE 1
#define MENU_OPTION_DEQUEUE 2
#define MENU_OPTION_SHOW 3
#define MENU_OPTION_EXIT 4

#define SCANF_SUCCESS 1
#define TRUE 1
#define FALSE 0
#define NEWLINE_CHAR '\n'
#define NEWLINE "\n"

typedef enum {
  SUCCESS = 0,
  ERROR_QUEUE_EMPTY = 1,
  ERROR_ALLOCATION_FAILED = 1,
  ERROR_INVALID_INPUT = 1
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
StatusCode read_menu_option(int *option);
StatusCode read_value(int *value);
StatusCode enqueue(Queue *queue, int value);
StatusCode dequeue(Queue *queue, int *out_value);
void print_queue(const Queue *queue);
int is_empty(const Queue *queue);
void free_queue(Queue *queue);
void display_menu(void);
void process_menu_option(Queue *queue, int option, int *continue_running);

int main(void) {
  Queue queue = {NULL, NULL};
  int option;
  int continue_running = TRUE;

  printf(TITLE);

  while (continue_running) {
    display_menu();

    if (read_menu_option(&option) != SUCCESS) {
      continue;
    }

    process_menu_option(&queue, option, &continue_running);
  }

  free_queue(&queue);

  return SUCCESS;
}

void clear_input_buffer(void) {
  int c;
  while ((c = getchar()) != NEWLINE_CHAR && c != EOF)
    ;
}

StatusCode read_menu_option(int *option) {
  printf(INPUT_OPTION);

  if (scanf(FORMAT_INTEGER, option) != SCANF_SUCCESS) {
    fprintf(stderr, ERR_MSG_INVALID_INPUT);
    clear_input_buffer();
    return ERROR_INVALID_INPUT;
  }
  clear_input_buffer();

  return SUCCESS;
}

StatusCode read_value(int *value) {
  printf(INPUT_VALUE);

  if (scanf(FORMAT_INTEGER, value) != SCANF_SUCCESS) {
    fprintf(stderr, ERR_MSG_INVALID_INPUT);
    clear_input_buffer();
    return ERROR_INVALID_INPUT;
  }
  clear_input_buffer();

  return SUCCESS;
}

StatusCode enqueue(Queue *queue, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));

  if (new_node == NULL) {
    fprintf(stderr, ERR_MSG_COULD_ALLOCATE_NODE);
    return ERROR_ALLOCATION_FAILED;
  }

  new_node->value = value;
  new_node->next = NULL;

  if (is_empty(queue)) {
    queue->front = new_node;
    queue->rear = new_node;
    return SUCCESS;
  }

  queue->rear->next = new_node;
  queue->rear = new_node;

  return SUCCESS;
}

StatusCode dequeue(Queue *queue, int *out_value) {
  Node *current = queue->front;

  if (is_empty(queue)) {
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

void print_queue(const Queue *queue) {
  const Node *current = queue->front;

  if (is_empty(queue)) {
    return;
  }

  printf(TEXT_QUEUE_PREFIX);
  while (current != NULL) {
    printf(FORMAT_NODE, current->value);
    printf(TEXT_ARROW);
    current = current->next;
  }
  printf(TEXT_NULL_TERMINATOR);
}

int is_empty(const Queue *queue) { return (queue->front == NULL) ? TRUE : FALSE; }

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

void display_menu(void) {
  printf(NEWLINE);
  printf(TEXT_MENU_ENQUEUE);
  printf(TEXT_MENU_DEQUEUE);
  printf(TEXT_MENU_SHOW);
  printf(TEXT_MENU_EXIT);
}

void process_menu_option(Queue *queue, int option, int *continue_running) {
  int value;

  switch (option) {
  case MENU_OPTION_ENQUEUE:
    if (read_value(&value) == SUCCESS) {
      if (enqueue(queue, value) == SUCCESS) {
        printf(TEXT_ENQUEUED, value);
      }
    }
    break;

  case MENU_OPTION_DEQUEUE:
    if (dequeue(queue, &value) == SUCCESS) {
      printf(TEXT_DEQUEUED, value);
    } else {
      printf(ERR_MSG_EMPTY_DEQUEUE);
    }
    break;

  case MENU_OPTION_SHOW:
    if (is_empty(queue)) {
      printf(TEXT_EMPTY_QUEUE);
    } else {
      print_queue(queue);
    }
    break;

  case MENU_OPTION_EXIT:
    printf(TEXT_EXITING);
    *continue_running = FALSE;
    break;

  default:
    printf(ERR_MSG_INVALID_OPTION);
    break;
  }
}
