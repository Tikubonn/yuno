
/*
  Linux 環境での呼び出し規約は未指定になります。
*/

#ifdef __linux__
#undef __yunocall 
#define __yunocall
#endif

/*
  Windows 環境での呼出し規約は __stdcall で統一されます。
*/

#ifdef _WIN32
#undef __yunocall 
#define __yunocall __stdcall
#endif

#ifdef _WIN64
#undef __yunocall 
#define __yunocall __stdcall
#endif
