
#ifdef __linux__
#undef __yunocall 
#define __yunocall
#endif

#ifdef _WIN32
#undef __yunocall 
#define __yunocall __stdcall
#endif

#ifdef _WIN64
#undef __yunocall 
#define __yunocall __stdcall
#endif
