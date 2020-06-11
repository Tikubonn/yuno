#include <yuno.h>
#include <windows.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define MIN(a, b) ((a)<(b)?(a):(b))

/*
	名前付きパイプを作成する際に必要になるパイプ名を作成します
*/

static void generate_pipe_path (char *bufferseq, size_t buffersize, uintmax_t count){
	size_t index = 0;
	for (; index < buffersize && index < sizeof(YUNOPIPE_PATH_PREFIX) -1; index++){
		bufferseq[index] = YUNOPIPE_PATH_PREFIX[index];
	}
	if (count == 0){
		bufferseq[index] = '0';
		index += 1;
	}
	else {
		for (uintmax_t cnt = count; index < buffersize && 0 < cnt; index++, cnt = cnt / 10){
			bufferseq[index] = '0' + cnt % 10;
		}
	}
	bufferseq[MIN(index, buffersize -1)] = '\0';
}

/*
	名前付きパイプ・ファイル・イベントを作成する際に必要になるセキュリティ記述子を作成します
*/

static void setup_secutiry_attributes (SECURITY_ATTRIBUTES *secattrs){
	secattrs->nLength = sizeof(SECURITY_ATTRIBUTES);
	secattrs->lpSecurityDescriptor = NULL;
	secattrs->bInheritHandle = TRUE;
}

/*
	非同期・同期の名前付きパイプを作成します
	この関数は文字列定数 YUNOPIPE_PATH_PREFIX に 
	globalpipecountp が参照する整数を付加した名前のパイプを作成します
	この関数はパイプを作成するたびに globalpipecountp の参照する値を加算します
*/

static HANDLE make_server_pipe (bool asyncp, char *bufferseq, size_t buffersize, uintmax_t *globalpipecountp){
	reset_yunoerror();
	HANDLE serverpipe;
	for (size_t trycount = 0; trycount < YUNOPIPE_TRY_COUNT; trycount++){
		generate_pipe_path(bufferseq, buffersize, *globalpipecountp);
		*globalpipecountp += 1;
		SECURITY_ATTRIBUTES secattrs;
		setup_secutiry_attributes(&secattrs);
		DWORD flags;
		if (asyncp == true){
			flags = PIPE_ACCESS_INBOUND | FILE_FLAG_FIRST_PIPE_INSTANCE | FILE_FLAG_OVERLAPPED;
		}
		else {
			flags = PIPE_ACCESS_INBOUND | FILE_FLAG_FIRST_PIPE_INSTANCE;
		}
		serverpipe = CreateNamedPipe(bufferseq, flags, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, YUNOPIPE_INPUT_BUFFER_SIZE, YUNOPIPE_OUTPUT_BUFFER_SIZE, NMPWAIT_USE_DEFAULT_WAIT, &secattrs);
		if (serverpipe != INVALID_HANDLE_VALUE){
			break;
		}
		else {
			DWORD lasterror = GetLastError();
			if (lasterror != ERROR_ACCESS_DENIED){
				set_yunoerror(YUNOOS_ERROR);
				return INVALID_HANDLE_VALUE;
			}
		}
	}
	if (serverpipe == INVALID_HANDLE_VALUE){
		set_yunoerror(YUNOERROR);
		return INVALID_HANDLE_VALUE;
	}
	return serverpipe;
}

/*
	作成された名前付きパイプを開きます
*/

static HANDLE make_client_pipe (bool asyncp, char *bufferseq, size_t buffersize){
	(void)buffersize; // ignore unused variable!
	reset_yunoerror();
	DWORD flags;
	if (asyncp == true){
		flags = FILE_FLAG_OVERLAPPED;
	}
	else {
		flags = FILE_ATTRIBUTE_NORMAL;
	}
	SECURITY_ATTRIBUTES secattrs;
	setup_secutiry_attributes(&secattrs);
	HANDLE clientpipe = CreateFile(bufferseq, GENERIC_WRITE, FILE_SHARE_WRITE, &secattrs, OPEN_EXISTING, flags, NULL);
	if (clientpipe == INVALID_HANDLE_VALUE){
		set_yunoerror(YUNOOS_ERROR);
		return INVALID_HANDLE_VALUE;
	}
	return clientpipe;
}

/*
	イベントを作成します
*/

static HANDLE make_event (){
	reset_yunoerror();
	SECURITY_ATTRIBUTES secattrs;
	setup_secutiry_attributes(&secattrs);
	HANDLE event = CreateEvent(&secattrs, false, false, NULL);
	if (event == INVALID_HANDLE_VALUE){
		set_yunoerror(YUNOOS_ERROR);
		return INVALID_HANDLE_VALUE;
	}
	return event;
}

static int parse_flags (int flags, bool *asyncp){
	reset_yunoerror();
	switch (flags){
		case 0:
			*asyncp = false;
			return 0;
		case YUNOFILE_SYNC:
			*asyncp = false;
			return 0;
		case YUNOFILE_ASYNC:
			*asyncp = true;
			return 0;
		default:
			set_yunoerror(YUNOARGUMENT_ERROR);
			return 1;
	}
}

int __stdcall __make_yunopipe (int flags, void *inputbufferseq, yunosize inputbuffersize, void *outputbufferseq, yunosize outputbuffersize, yunofile *inputfilep, yunofile *outputfilep, uintmax_t *globalpipecountp){
	reset_yunoerror();
	bool asyncp;
	if (parse_flags(flags, &asyncp) != 0){
		return 1;
	}
	char pipepath[MAX_PATH];
	HANDLE serverpipe = make_server_pipe(asyncp, pipepath, sizeof(pipepath), globalpipecountp);
	if (serverpipe == INVALID_HANDLE_VALUE){
		return 1;
	}
	HANDLE clientpipe = make_client_pipe(asyncp, pipepath, sizeof(pipepath));
	if (clientpipe == INVALID_HANDLE_VALUE){
		return 1;
	}
	HANDLE serverevent = make_event();
	if (serverevent == INVALID_HANDLE_VALUE){
		return 1;
	}
	HANDLE clientevent = make_event();
	if (clientevent == INVALID_HANDLE_VALUE){
		return 1;
	}
	init_yunofile(TYPE_YUNOSERVER_PIPE, YUNOFILE_READABLE, serverpipe, asyncp, serverevent, inputbufferseq, inputbuffersize, 0, inputfilep);
	init_yunofile(TYPE_YUNOCLIENT_PIPE, YUNOFILE_WRITABLE, clientpipe, asyncp, clientevent, outputbufferseq, outputbuffersize, 0, outputfilep);
	return 0;
}
