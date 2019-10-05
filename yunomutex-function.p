
extern yunomutex_status __yunocall make_yunomutex_manually (yunomutex*);
extern yunomutex __yunocall *make_yunomutex ();
extern yunomutex_status __yunocall wait_yunomutex (yunomutex_wait_mode, yunomutex*);
extern yunomutex_status __yunocall release_yunomutex (yunomutex*);
extern yunomutex_status __yunocall close_yunomutex (yunomutex*);
extern yunomutex_status __yunocall free_yunomutex (yunomutex*);
