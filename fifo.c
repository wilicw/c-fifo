#include "fifo.h"

#if defined(__FIFO_LINKED__)

error_t fifo_init(fifo_t *fifo) {
  fifo->head = NULL;
  fifo->back = &(fifo->head);
  return FIFO_SUCCESS;
}

#elif defined(__FIFO_MALLOC_ARR__)

//error_t fifo_init(fifo_t* fifo, size_t element_size, size_t max_len) {
  fifo->element_size = element_size;
  fifo->storage = malloc(max_len * element_size);
  fifo->len = 0;
  fifo->front = fifo->back = &(fifo->storage);
  fifo->max_len = max_len;
  return fifo->storage == NULL ? FIFO_FAILED : FIFO_SUCCESS;
}

#else

error_t fifo_init(fifo_t *fifo, size_t element_size, size_t max_len, void *storage) {
  fifo->element_size = element_size;
  fifo->storage = storage;
  fifo->len = 0;
  fifo->front = fifo->storage;
  fifo->back = fifo->storage;
  fifo->max_len = max_len;
  return FIFO_SUCCESS;
}

#endif

#if defined(__FIFO_LINKED__)

error_t fifo_enqueue(fifo_t *fifo, void *value) {
  node_t *node = malloc(sizeof(node_t));
  if (node == NULL) return FIFO_FAILED;
  node->next = NULL;
  node->value = value;
  *(fifo->back) = node;
  fifo->back = &(node->next);
  return FIFO_SUCCESS;
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

error_t fifo_enqueue(fifo_t *fifo, void *value) {
  if (fifo->len == fifo->max_len) return FIFO_FULL;
  memcpy(fifo->back, value, fifo->element_size);
  fifo->back += fifo->element_size;
  fifo->back = CICULAR(fifo->back, fifo->storage, fifo->max_len * fifo->element_size);
  fifo->len++;
  return FIFO_SUCCESS;
}

void *fifo_dequeue(fifo_t *fifo) {
  if (fifo_empty(fifo))
    return NULL;
  void *value = fifo->front;
  fifo->front += fifo->element_size;
  fifo->front = CICULAR(fifo->front, fifo->storage, fifo->max_len * fifo->element_size);
  fifo->len--;
  return value;
}

void *fifo_peek(fifo_t *fifo) {
  if (fifo_empty(fifo))
    return NULL;
  return fifo->front;
}

error_t fifo_empty(fifo_t *fifo) {
  return !fifo->len ? FIFO_EMPTY : FIFO_NONEMPTY;
}

#endif

