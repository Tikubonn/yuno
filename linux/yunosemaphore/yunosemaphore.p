#include <semaphore.h>

typedef struct yunosemaphore {
	sem_t *semaphorep;
} yunosemaphore;
