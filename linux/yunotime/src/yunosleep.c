#include <yuno.private>
#include <unistd.h>

yunosleep_status __yunocall yunosleep (int seconds){
  if (sleep(seconds) != 0){
    return YUNOSLEEP_ERROR;
  }
  return YUNOSLEEP_SUCCESS;
}

