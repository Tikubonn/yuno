
extern yunoprocess_status __yunocall __make_yunoprocess_manually (yunoprocess_entry_point, void*, yunoprocess*, yunoshared_memory**);

#define make_yunoprocess_manually(entrypoint, parameter, process)\
__make_yunoprocess_manually(entrypoint, parameter, process, &global_yunoshared_memory)
