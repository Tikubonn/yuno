#include <yuno.private>

yunothread_status __yunocall close_yunothread (yunothread *thread){
  (void*)thread; //! ignore unused warning.
  return YUNOTHREAD_SUCCESS;
}

