
extern yunosemaphore_status __yunocall make_yunosemaphore_manually (int, yunosemaphore*);
extern yunosemaphore_status __yunocall make_named_yunosemaphore_manually (const char*, int, yunosemaphore*);
extern yunosemaphore __yunocall *make_yunosemaphore (int);
extern yunosemaphore __yunocall *make_named_yunosemaphore (const char*, int);
extern yunosemaphore_status __yunocall wait_yunosemaphore (yunosemaphore_wait_mode, yunosemaphore*);
extern yunosemaphore_status __yunocall release_yunosemaphore (yunosemaphore*);
extern yunosemaphore_status __yunocall close_yunosemaphore (yunosemaphore*);
extern yunosemaphore_status __yunocall free_yunosemaphore (yunosemaphore*);
