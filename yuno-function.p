
//extern yunoprocess_status __yunocall make_yunoprocess_manually (yunoprocess_entry_point, void*, yunoprocess*);
//extern yunoprocess __yunocall *make_yunoprocess (yunoprocess_entry_point, void*);
extern yunoprocess_status __yunocall start_yunoprocess (yunoprocess*);
extern yunoprocess_status __yunocall wait_yunoprocess (yunoprocess_wait_mode, yunoprocess*);
extern yunoprocess_status __yunocall close_yunoprocess (yunoprocess*);
extern yunoprocess_status __yunocall get_yunoprocess_exit_code (yunoprocess*, int*);
extern yunoprocess_status __yunocall free_yunoprocess (yunoprocess*);

extern yunothread_status __yunocall make_yunothread_manually (yunothread_entry_point, void*, yunothread*);
extern yunothread __yunocall *make_yunothread (yunothread_entry_point, void*);
extern yunothread_status __yunocall start_yunothread (yunothread*);
extern yunothread_status __yunocall wait_yunothread (yunothread_wait_mode, yunothread*);
extern yunothread_status __yunocall close_yunothread (yunothread*);
extern yunothread_status __yunocall get_yunothread_exit_code (yunothread*, int*);
extern yunothread_status __yunocall free_yunothread (yunothread*);

extern yunofile_status __yunocall open_yunofile_manually (const char*, int, void*, yunosize, yunofile*);
extern yunofile_status __yunocall open_async_yunofile_manually (const char*, int, void*, yunosize, yunofile*);
extern yunofile __yunocall *open_yunofile (const char*, int, yunosize);
extern yunofile __yunocall *open_async_yunofile (const char*, int, yunosize);
extern bool __yunocall yunofile_readablep (yunofile*);
extern bool __yunocall yunofile_writablep (yunofile*);
extern yunofile_status __yunocall write_yunofile (void*, yunosize, yunofile*, yunosize*);
extern yunofile_status __yunocall request_write_yunofile (void*, yunosize, yunofile*);
extern yunofile_status __yunocall wait_write_yunofile (yunofile_wait_mode, yunofile*, yunosize*);
extern yunofile_status __yunocall read_yunofile (void*, yunosize, yunofile*, yunosize*);
extern yunofile_status __yunocall request_read_yunofile (yunosize, yunofile*);
extern yunofile_status __yunocall wait_read_yunofile (void*, yunofile_wait_mode, yunofile*, yunosize*);
extern yunofile_status __yunocall seek_yunofile (yunossize, yunofile_where, yunofile*, yunosize*);
extern yunofile_status __yunocall tell_yunofile (yunofile*, yunosize*);
extern yunofile_status __yunocall close_yunofile (yunofile*);
extern yunofile_status __yunocall free_yunofile (yunofile*);
extern yunofile_status __yunocall get_yunostandard_input_manually (void*, yunosize, yunofile*);
extern yunofile_status __yunocall get_yunostandard_output_manually (void*, yunosize, yunofile*);
extern yunofile_status __yunocall get_yunostandard_error_manually (void*, yunosize, yunofile*);
extern yunofile_status __yunocall get_async_yunostandard_input_manually (void*, yunosize, yunofile*);
extern yunofile_status __yunocall get_async_yunostandard_output_manually (void*, yunosize, yunofile*);
extern yunofile_status __yunocall get_async_yunostandard_error_manually (void*, yunosize, yunofile*);
extern yunofile __yunocall *get_yunostandard_input (yunosize);
extern yunofile __yunocall *get_yunostandard_output (yunosize);
extern yunofile __yunocall *get_yunostandard_error (yunosize);
extern yunofile __yunocall *get_async_yunostandard_input (yunosize);
extern yunofile __yunocall *get_async_yunostandard_output (yunosize);
extern yunofile __yunocall *get_async_yunostandard_error (yunosize);

extern yunomutex_status __yunocall make_yunomutex_manually (yunomutex*);
extern yunomutex __yunocall *make_yunomutex ();
extern yunomutex_status __yunocall wait_yunomutex (yunomutex_wait_mode, yunomutex*);
extern yunomutex_status __yunocall release_yunomutex (yunomutex*);
extern yunomutex_status __yunocall close_yunomutex (yunomutex*);
extern yunomutex_status __yunocall free_yunomutex (yunomutex*);

extern yunosemaphore_status __yunocall make_yunosemaphore_manually (int, yunosemaphore*);
extern yunosemaphore __yunocall *make_yunosemaphore (int);
extern yunosemaphore_status __yunocall wait_yunosemaphore (yunosemaphore_wait_mode, yunosemaphore*);
extern yunosemaphore_status __yunocall release_yunosemaphore (yunosemaphore*);
extern yunosemaphore_status __yunocall close_yunosemaphore (yunosemaphore*);
extern yunosemaphore_status __yunocall free_yunosemaphore (yunosemaphore*);

extern yunosleep_status __yunocall yunosleep (int);

extern yunopipe_status __yunocall make_yunopipe_manually (yunofile*, yunofile*);
extern yunopipe_status __yunocall make_yunopipe (yunofile**, yunofile**);

//extern void __yunocall *allocate_yunoshared_memory (size_t);
//extern yunoshared_memory_status __yunocall free_yunoshared_memory (void*, size_t);
