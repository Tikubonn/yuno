#include <pthread.h>
#include <stdbool.h>

typedef struct yunomutex {
	pthread_mutex_t *mutexp;
	bool closedp;
} yunomutex;
