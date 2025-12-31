#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR 1
#define TRUE 1
#define FALSE 0

typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct {
  Node *front;
  Node *rear;
} Queue;

void enqueue(Queue *q, int value);
int dequeue(Queue *q, int *out_value);
void print_queue(const Queue *q);
int is_empty(const Queue *queue);

int main() {
  Queue queue = {NULL, NULL};
  int extraido, option = 0;

  printf("=== Queue Array ===\n\n");

  while (option != 4) {
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. Show\n");
    printf("4. Exit\n");
    printf("Enter option: ");
    scanf("%d", &option);

    switch (option) {
    case 1:
      printf("Enter value: ");
      scanf("%d", &extraido);
      enqueue(&queue, extraido);
      printf("  Valor %d en cola\n", extraido);
      break;
    case 2:
      dequeue(&queue, &extraido);
      printf("  Valor %d fuera de la cola\n", extraido);
      break;
    case 3:
      if (!is_empty(&queue)) {
        print_queue(&queue);
        break;
      }
      printf("La cola esta vacia\n");
      break;
    default:
      printf("Exit\n");
      break;
    }
  }

  // print_queue(&queue);
  // while (!is_empty(&queue)) {
  //   dequeue(&queue, &extraido);
  //
  // }
  // printf("La cola esta vacia\n");

  return 0;
}

void enqueue(Queue *queue, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->value = value;
  new_node->next = NULL;

  if (is_empty(queue)) {
    queue->front = new_node;
    queue->rear = new_node;
    return;
  }

  queue->rear->next = new_node;
  queue->rear = new_node;
}

int dequeue(Queue *queue, int *out_value) {
  Node *current = queue->front;

  if (is_empty(queue)) {
    return 1;
  }

  *out_value = current->value;
  queue->front = current->next;
  if (queue->front == NULL) {
    queue->rear = NULL;
  }
  free(current);

  return 0;
}

void print_queue(const Queue *queue) {
  const Node *current = queue->front;

  if (is_empty(queue)) {
    return;
  }

  printf("Raw: ");
  while (current != NULL) {
    printf("[%d] -> ", current->value);
    current = current->next;
  }
  printf("NULL\n");
}

int is_empty(const Queue *queue) { return (queue->front == NULL) ? TRUE : FALSE; }
