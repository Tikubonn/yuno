
//extern yunoprocess_status __yunocall make_yunoprocess_manually (yunoprocess_entry_point, void*, yunoprocess*);
//extern yunoprocess __yunocall *make_yunoprocess (yunoprocess_entry_point, void*);
extern yunoprocess_status __yunocall start_yunoprocess (yunoprocess*);
extern yunoprocess_status __yunocall wait_yunoprocess (yunoprocess_wait_mode, yunoprocess*);
extern yunoprocess_status __yunocall close_yunoprocess (yunoprocess*);
extern yunoprocess_status __yunocall get_yunoprocess_exit_code (yunoprocess*, int*);
extern yunoprocess_status __yunocall free_yunoprocess (yunoprocess*);
