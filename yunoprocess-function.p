
extern yunoprocess_status __stdcall make_yunoprocess_manually (yunoprocess_entry_point, void*, yunoprocess*);
extern yunoprocess __stdcall *make_yunoprocess (yunoprocess_entry_point, void*);
extern yunoprocess_status __stdcall start_yunoprocess (yunoprocess*);
extern yunoprocess_status __stdcall wait_yunoprocess (yunoprocess_wait_mode, yunoprocess*);
extern yunoprocess_status __stdcall close_yunoprocess (yunoprocess*);
extern yunoprocess_status __stdcall get_yunoprocess_exit_code (yunoprocess*, int*);
extern yunoprocess_status __stdcall free_yunoprocess (yunoprocess*);
