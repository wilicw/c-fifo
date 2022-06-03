# c-fifo

## Example

```c
#include "fifo.h"

int main() {
  fifo_t fifo;
  fifo_init(&fifo);
  
  int a = 0;
  fifo_enqueue(&fifo, &a);
  
  int *b;
  b = fifo_dequeue(&fifo);
  
  return 0;
}
```
