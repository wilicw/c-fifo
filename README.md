# c-fifo

## Example

```c
#define __FIFO_MALLOC_ARR__
#include "fifo.h"

static uint8_t storage[10000];

int main() {
  // test

  fifo_t fifo;

#if defined(__FIFO_LINKED__)
  fifo_init(&fifo);
#elif defined(__FIFO_MALLOC_ARR__)
  fifo_init(&fifo, sizeof(int), 10000);
#else
  fifo_init(&fifo, sizeof(int), 10000, &storage);
#endif
  
  int a = 0;
  fifo_enqueue(&fifo, &a);
  
  int *b;
  b = fifo_dequeue(&fifo);
  
  return 0;
}
```
