#include <semaphore.h>
#include <stdbool.h>

typedef struct yunosemaphore {
	sem_t *semaphorep;
	bool closedp;
} yunosemaphore;
