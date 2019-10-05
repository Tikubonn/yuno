
.always:

clean: .always
	rm -f yunoshared-memory.private
	rm -f yunoshared-memory.public
	rm -f yunoshared-memory.lib
	rm -f compiled/allocate-yunoshared-memory.o
	rm -f compiled/free-yunoshared-memory.o
	rm -f compiled/remap-yunoshared-memory.o
	rm -f compiled/yunoshared-memory-managed-addressp.o

yunoshared-memory.private: yunoshared-memory.p src/allocate-yunoshared-memory.h src/free-yunoshared-memory.h src/remap-yunoshared-memory.h src/yunoshared-memory-managed-addressp.h
	cat yunoshared-memory.p src/allocate-yunoshared-memory.h src/free-yunoshared-memory.h src/remap-yunoshared-memory.h src/yunoshared-memory-managed-addressp.h > yunoshared-memory.private

yunoshared-memory.public: yunoshared-memory.p yunoshared-memory.public.p src/allocate-yunoshared-memory.h src/free-yunoshared-memory.h src/remap-yunoshared-memory.h src/yunoshared-memory-managed-addressp.h
	cat yunoshared-memory.p yunoshared-memory.public.p src/allocate-yunoshared-memory.h src/free-yunoshared-memory.h src/remap-yunoshared-memory.h src/yunoshared-memory-managed-addressp.h > yunoshared-memory.public

yunoshared-memory.lib: compiled/allocate-yunoshared-memory.o compiled/free-yunoshared-memory.o compiled/remap-yunoshared-memory.o compiled/yunoshared-memory-managed-addressp.o
	ar r yunoshared-memory.lib compiled/allocate-yunoshared-memory.o compiled/free-yunoshared-memory.o compiled/remap-yunoshared-memory.o compiled/yunoshared-memory-managed-addressp.o

compiled/allocate-yunoshared-memory.o: src/allocate-yunoshared-memory.c 
	gcc $(CFLAGS) -c src/allocate-yunoshared-memory.c -o compiled/allocate-yunoshared-memory.o

compiled/free-yunoshared-memory.o: src/free-yunoshared-memory.c
	gcc $(CFLAGS) -c src/free-yunoshared-memory.c -o compiled/free-yunoshared-memory.o

compiled/remap-yunoshared-memory.o: src/remap-yunoshared-memory.c
	gcc $(CFLAGS) -c src/remap-yunoshared-memory.c -o compiled/remap-yunoshared-memory.o

compiled/yunoshared-memory-managed-addressp.o: src/yunoshared-memory-managed-addressp.c 
	gcc $(CFLAGS) -c src/yunoshared-memory-managed-addressp.c -o compiled/yunoshared-memory-managed-addressp.o
