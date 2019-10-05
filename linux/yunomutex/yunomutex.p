#include <pthread.h>

typedef struct yunomutex {
	pthread_mutex_t *mutexp;
} yunomutex;
