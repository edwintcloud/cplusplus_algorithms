#include <cstdio>
#include "buffer.h"

int main() {

    Circular_Buffer<uint32_t> cb(10);

    printf("\n === CircularBuffer Test ===\n");
	printf("Size: %zu\n", cb.size());

	uint32_t x = 1;
	printf("Enqueue 1, val: %d\n", x);
	cb.enqueue(x);
    printf("Size: %zu\n", cb.size());
    x = 2;
	printf("Enqueue 1, val: %d\n", x);
	cb.enqueue(x);
    printf("Size: %zu\n", cb.size());
	printf("Enqueue 1, val: %d\n", x);
	cb.enqueue(x);
    printf("Size: %zu\n", cb.size());
    x = cb.dequeue();
	printf("Dequeue: %d\n", x);
    printf("Size: %zu\n", cb.size());
    x = cb.dequeue();
	printf("Dequeue: %d\n", x);
    printf("Size: %zu\n", cb.size());
    x = cb.dequeue();
	printf("Dequeue: %d\n", x);
    printf("Size: %zu\n", cb.size());
    x = cb.dequeue();
	printf("Dequeue: %d\n", x);
    printf("Size: %zu\n", cb.size());
	printf("Empty: %d\n", cb.is_empty());

 }