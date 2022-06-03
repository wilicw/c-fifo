#ifndef __FIFO__
#define __FIFO__

#include <stdint.h>
#include <stdlib.h>

typedef struct node node_t;

struct node {
  node_t *next;
  void *value;
};

typedef struct {
  node_t *head;
  node_t **back;
} fifo_t;

void fifo_init(fifo_t *);
void fifo_enqueue(fifo_t *, void *);
void *fifo_dequeue(fifo_t *);
uint8_t fifo_empty(fifo_t *);

#endif
