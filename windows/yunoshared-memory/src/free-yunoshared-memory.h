
extern yunoshared_memory_status __yunocall __free_yunoshared_memory (void*, size_t, yunoshared_memory**);

#define free_yunoshared_memory(address, size)\
after_init_yunoshared_memory(\
__free_yunoshared_memory(address, size, &global_yunoshared_memory))
