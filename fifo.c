#include "fifo.h"

void fifo_init(fifo_t *fifo) {
  fifo->head = NULL;
  fifo->back = &(fifo->head);
}

void fifo_enqueue(fifo_t *fifo, void *value) {
  node_t *node = malloc(sizeof(node_t));
  node->next = NULL;
  node->value = value;
  *(fifo->back) = node;
  fifo->back = &(node->next);
}

void *fifo_dequeue(fifo_t *fifo) {
  if (fifo_empty(fifo)) 
    return NULL;
  node_t *node = fifo->head;
  void *value = node->value;
  fifo->head = node->next;
  free(node);
  return value;
}

uint8_t fifo_empty(fifo_t *fifo) {
  if (fifo->head == NULL) {
    fifo_init(fifo);
    return 1;
  } else {
    return 0;
  }
}

