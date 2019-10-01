#include <yuno.private>

yunoprocess_status __yunocall close_yunoprocess (yunoprocess *process){
  (void*)process; // ignore unused warning!
  return YUNOPROCESS_SUCCESS;
}

