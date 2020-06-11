
typedef struct yunoshared_memory {
	void *bitarrayseq;
	yunosize bitarraysize;
	void *allocatorseq;
	yunosize allocatorsize;
	yunoallocator allocator;
	struct yunoshared_memory *next;
} yunoshared_memory;
