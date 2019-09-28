
extern yunosemaphore_status __stdcall make_yunosemaphore_manually (int, yunosemaphore*);
extern yunosemaphore_status __stdcall make_named_yunosemaphore_manually (const char*, int, yunosemaphore*);
extern yunosemaphore __stdcall *make_yunosemaphore (int);
extern yunosemaphore __stdcall *make_named_yunosemaphore (const char*, int);
extern yunosemaphore_status __stdcall wait_yunosemaphore (yunosemaphore_wait_mode, yunosemaphore*);
extern yunosemaphore_status __stdcall release_yunosemaphore (yunosemaphore*);
extern yunosemaphore_status __stdcall close_yunosemaphore (yunosemaphore*);
extern yunosemaphore_status __stdcall free_yunosemaphore (yunosemaphore*);
