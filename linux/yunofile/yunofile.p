#include <aio.h>
#include <signal.h>
#include <stdbool.h>

typedef enum yunofile_request_status {
  YUNOFILE_FREE,
  YUNOFILE_READING,
  YUNOFILE_WRITING,
  YUNOFILE_READ_COMPLETED,
  YUNOFILE_WRITE_COMPLETED
} yunofile_request_status;

typedef struct yunofile {
  int mode;
  int fd;
  bool asyncp;
  yunosize asyncseek;
  yunosize completedsize;
  yunofile_request_status requeststatus;
  yunofile_buffer buffer;
  struct aiocb cb; // like as overlapped in windows.
} yunofile;

