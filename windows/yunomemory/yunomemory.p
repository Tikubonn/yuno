
typedef struct yunomemory {
	void *bitarrayseq;
	yunosize bitarraysize;
	void *allocatorseq;
	yunosize allocatorsize;
	void *sequence;
	yunosize size;
	yunoallocator allocator;
	struct yunomemory *next;
} yunomemory;

yunomemory *global_yunomemory;
