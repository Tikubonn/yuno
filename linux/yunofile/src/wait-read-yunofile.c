#define  _GNU_SOURCE
#include <yuno.h>
#include <poll.h>
#include <unistd.h>
//#include <stdio.h>

static int wait_read_async_file (void *sequence, yunowait_mode waitmode, yunofile *file, yunosize *readsizep){
	reset_yunoerror();
	int timeout;
	switch (waitmode){
		case YUNOFOREVER:
			timeout = -1;
			break;
		case YUNONOWAIT:
			timeout = 0;
			break;
		default:
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
	}
	struct pollfd pfd;
	pfd.fd = file->filefd;
	pfd.events = POLLIN | POLLHUP | POLLRDHUP;
	pfd.revents = 0;
	int pollresult = poll(&pfd, 1, timeout);
	if (pollresult == 1){
		/*
		printf("POLLIN=%d\n", POLLIN);
		printf("POLLPRI=%d\n", POLLPRI);
		printf("POLLOUT=%d\n", POLLOUT);
		printf("POLLRDHUP =%d\n", POLLRDHUP);
		printf("POLLERR=%d\n", POLLERR);
		printf("POLLIN=%d\n", POLLIN);
		printf("POLLHUP=%d\n", POLLHUP);
		printf("POLLNVAL=%d\n", POLLNVAL);
		printf("POLLRDNORM=%d\n", POLLRDNORM);
		printf("POLLRDBAND=%d\n", POLLRDBAND);
		printf("POLLWRNORM=%d\n", POLLWRNORM);
		printf("POLLWRBAND=%d\n", POLLWRBAND);
		printf("pfd.events=%d\n", pfd.events);
		printf("pfd.revents=%d\n", pfd.revents);
		*/
		if (pfd.revents & POLLIN){
			ssize_t readsize = read(file->filefd, sequence, file->asynccompletedsize);
			if (readsize == -1){
				set_yunoerror(YUNOOS_ERROR);
				return 1;
			}
			file->asyncstatus = YUNOFILE_FREE;
			*readsizep = readsize;
			return 0;
		}
		else 
		if (pfd.revents & POLLHUP){
			file->asyncstatus = YUNOFILE_FREE;
			*readsizep = 0;
			return 0;
		}
		else 
		if (pfd.revents & POLLRDHUP){
			file->asyncstatus = YUNOFILE_FREE;
			*readsizep = 0;
			return 0;
		}
		else {
			set_yunoerror(YUNOBUSY);
			return 1;
		}
	} 
	else 
	if (pollresult == 0){
		set_yunoerror(YUNOBUSY);
		return 1;
	}
	else {
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
}

static int wait_read_sync_file (void *sequence, yunowait_mode waitmode, yunofile *file, yunosize *readsizep){
	(void)waitmode; // ignore unused warning!
	reset_yunoerror();
	ssize_t readsize = read(file->filefd, sequence, file->asynccompletedsize);
	if (readsize == -1){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	file->asyncstatus = YUNOFILE_FREE;
	*readsizep = readsize;
	return 0;
}

int wait_read_yunofile (void *sequence, yunowait_mode waitmode, yunofile *file, yunosize *readsizep){
	reset_yunoerror();
	if (file->closedp == false){
		if (file->asyncp == true){
			if (file->asyncstatus == YUNOFILE_READING){
				return wait_read_async_file(sequence, waitmode, file, readsizep);
			}
			else 
			if (file->asyncstatus == YUNOFILE_FREE){
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
			}
			else {
				set_yunoerror(YUNOBUSY);
				return 1;
			}
		}
		else {
			if (file->asyncstatus == YUNOFILE_READING){
				return wait_read_sync_file(sequence, waitmode, file, readsizep);
			}
			else 
			if (file->asyncstatus == YUNOFILE_FREE){
				set_yunoerror(YUNOARGUMENT_ERROR);
				return 1;
			}
			else {
				set_yunoerror(YUNOBUSY);
				return 1;
			}
		}
	}
	else {
		set_yunoerror(YUNOALREADY_CLOSED);
		return 1;
	}
}
