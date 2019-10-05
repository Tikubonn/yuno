
extern yunoprocess __yunocall *__make_yunoprocess (yunoprocess_entry_point, void*, yunoshared_memory**);

#define make_yunoprocess(entrypoint, parameter)\
__make_yunoprocess(entrypoint, parameter, &global_yunoshared_memory)
