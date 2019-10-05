
.always:

clean: .always
	rm -f yunoshared-memory.private
	rm -f yunoshared-memory.public
	rm -f yunoshared-memory.a
	rm -f compiled/global-yunoshared-memory.o
	rm -f compiled/allocate-yunoshared-memory.o
	rm -f compiled/free-yunoshared-memory.o

yunoshared-memory.private: yunoshared-memory.p src/global-yunoshared-memory.h src/allocate-yunoshared-memory.h src/free-yunoshared-memory.h
	cat yunoshared-memory.p src/global-yunoshared-memory.h src/allocate-yunoshared-memory.h src/free-yunoshared-memory.h > yunoshared-memory.private

yunoshared-memory.public: yunoshared-memory.p src/global-yunoshared-memory.h src/allocate-yunoshared-memory.h src/free-yunoshared-memory.h
	cat yunoshared-memory.p src/global-yunoshared-memory.h src/allocate-yunoshared-memory.h src/free-yunoshared-memory.h > yunoshared-memory.public

yunoshared-memory.a: compiled/global-yunoshared-memory.o compiled/allocate-yunoshared-memory.o compiled/free-yunoshared-memory.o
	ar r yunoshared-memory.a compiled/global-yunoshared-memory.o compiled/allocate-yunoshared-memory.o compiled/free-yunoshared-memory.o

compiled/global-yunoshared-memory.o: src/global-yunoshared-memory.c 
	gcc $(CFLAGS) -c src/global-yunoshared-memory.c -o compiled/global-yunoshared-memory.o

compiled/allocate-yunoshared-memory.o: src/allocate-yunoshared-memory.c 
	gcc $(CFLAGS) -c src/allocate-yunoshared-memory.c -o compiled/allocate-yunoshared-memory.o

compiled/free-yunoshared-memory.o: src/free-yunoshared-memory.c 
	gcc $(CFLAGS) -c src/free-yunoshared-memory.c -o compiled/free-yunoshared-memory.o
