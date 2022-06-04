#include "fifo.h"

#if defined(__FIFO_LINKED__)

void fifo_init(fifo_t *fifo) {
  fifo->head = NULL;
  fifo->back = &(fifo->head);
}

#elif defined(__FIFO_MALLOC_ARR__)

void fifo_init(fifo_t* fifo, size_t element_size, size_t max_len) {
  fifo->element_size = element_size;
  fifo->storage = malloc(max_len * element_size);
  fifo->len = 0;
  fifo->front = fifo->back = &(fifo->storage);
  fifo->max_len = max_len;
}

#else

void fifo_init(fifo_t *fifo, size_t element_size, size_t max_len, void *storage) {
  fifo->element_size = element_size;
  fifo->storage = storage;
  fifo->len = 0;
  fifo->front = fifo->storage;
  fifo->back = fifo->storage;
  fifo->max_len = max_len;
}

#endif

#if defined(__FIFO_LINKED__)

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

void *fifo_peek(fifo_t* fifo) {
 if (fifo_empty(fifo))
    return NULL;
  node_t *node = fifo->head;
  void *value = node->value;
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

#else


void fifo_enqueue(fifo_t *fifo, void *value) {
  memcpy(fifo->back, value, fifo->element_size);
  fifo->back += fifo->element_size;
  fifo->len++;
}

void *fifo_dequeue(fifo_t *fifo) {
  if (fifo_empty(fifo))
    return NULL;
  void *value = fifo->front;
  fifo->front += fifo->element_size;
  fifo->len--;
  return value;
}

void *fifo_peek(fifo_t *fifo) {
  if (fifo_empty(fifo))
    return NULL;
  void *value = fifo->front;
  return value;
}

uint8_t fifo_empty(fifo_t *fifo) {
  return !fifo->len;
}

#endif

