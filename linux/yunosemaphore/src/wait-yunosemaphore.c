#include <yuno.h>
#include <semaphore.h>
#include <errno.h>
#include <stdio.h>

int wait_yunosemaphore (yunowait_mode waitmode, yunosemaphore *semaphore){
	reset_yunoerror();
	if (semaphore->closedp == false){
		switch (waitmode){
			case YUNOFOREVER: 
				if (sem_wait(semaphore->semaphorep) != 0){
					printf("errno=%d\n", errno);
					set_yunoerror(YUNOOS_ERROR);
					return 1; 
				}
				return 0;
			case YUNONOWAIT: 
				if (sem_trywait(semaphore->semaphorep) != 0){
					switch (errno){
						case EAGAIN:
							printf("errno=EAGAIN\n");
							set_yunoerror(YUNOBUSY);
							return 1;
						default:
							printf("errno=%d\n", errno);
							set_yunoerror(YUNOOS_ERROR);
							return 1;
					}
				}
				return 0;
			default:
				printf("YUNOARGUMENT_ERROR\n");
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
		}
	}
	else {
		printf("YUNOALREADY_CLOSED\n");
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
