
extern yunomutex_status __stdcall make_yunomutex_manually (yunomutex*);
extern yunomutex_status __stdcall make_named_yunomutex_manually (const char*, yunomutex*);
extern yunomutex __stdcall *make_yunomutex ();
extern yunomutex __stdcall *make_named_yunomutex (const char*);
extern yunomutex_status __stdcall wait_yunomutex (yunomutex_wait_mode, yunomutex*);
extern yunomutex_status __stdcall release_yunomutex (yunomutex*);
extern yunomutex_status __stdcall close_yunomutex (yunomutex*);
extern yunomutex_status __stdcall free_yunomutex (yunomutex*);
