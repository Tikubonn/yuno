
extern yunothread_status __stdcall make_yunothread_manually (yunothread_entry_point, void*, yunothread*);
extern yunothread __stdcall *make_yunothread (yunothread_entry_point, void*);
extern yunothread_status __stdcall start_yunothread (yunothread*);
extern yunothread_status __stdcall wait_yunothread (yunothread_wait_mode, yunothread*);
extern yunothread_status __stdcall close_yunothread (yunothread*);
extern yunothread_status __stdcall get_yunothread_exit_code (yunothread*, int*);
extern yunothread_status __stdcall free_yunothread (yunothread*);
