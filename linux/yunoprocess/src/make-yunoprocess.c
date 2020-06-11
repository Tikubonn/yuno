#include <yuno.h>
#include <unistd.h>
#include <stdbool.h>

int make_yunoprocess (yunoentrypoint entrypoint, void *parameter, yunoprocess *process){
	reset_yunoerror();
	process->entrypoint = entrypoint;
	process->parameter = parameter;
	process->exitedp = false;
	process->exitcode = -1;
	process->closedp = false;
	int processid = fork();
	if (processid == -1){
		set_yunoerror(YUNOOS_ERROR);
		return 1;
	}
	else
	if (processid == 0){
		reset_yunoerror();
		int exitcode = entrypoint(parameter);
		_exit(exitcode);
		return 0;
	}
	else {
		process->processid = processid;
		return 0;
	}
}
