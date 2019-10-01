
extern yunothread_status __yunocall make_yunothread_manually (yunothread_entry_point, void*, yunothread*);
extern yunothread __yunocall *make_yunothread (yunothread_entry_point, void*);
extern yunothread_status __yunocall start_yunothread (yunothread*);
extern yunothread_status __yunocall wait_yunothread (yunothread_wait_mode, yunothread*);
extern yunothread_status __yunocall close_yunothread (yunothread*);
extern yunothread_status __yunocall get_yunothread_exit_code (yunothread*, int*);
extern yunothread_status __yunocall free_yunothread (yunothread*);
