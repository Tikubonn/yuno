
extern void __yunocall *__allocate_yunoshared_memory (size_t, yunoshared_memory**);

#define allocate_yunoshared_memory(size)\
after_init_yunoshared_memory(\
__allocate_yunoshared_memory(size, &global_yunoshared_memory))
