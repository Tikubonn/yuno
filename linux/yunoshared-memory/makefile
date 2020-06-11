
.PHONY: clean
clean:
	rm -f compiled/allocate-yunoshared-memory.o
	rm -f compiled/free-yunoshared-memory.o
	rm -f compiled/global-yunoshared-memory.o
	rm -f compiled/init-yunoshared-memory.o
	rm -f compiled/sync-yunoshared-memory.o
	rm -f yunoshared-memory.h
	rm -f yunoshared-memory.lib

.PHONY: h
h:
	make yunoshared-memory.h 

.PHONY: lib
lib:
	make yunoshared-memory.lib 

yunoshared-memory.h: yunoshared-memory.p src/allocate-yunoshared-memory.h src/free-yunoshared-memory.h src/global-yunoshared-memory.h src/init-yunoshared-memory.h src/sync-yunoshared-memory.h
	cat yunoshared-memory.p src/allocate-yunoshared-memory.h src/free-yunoshared-memory.h src/global-yunoshared-memory.h src/init-yunoshared-memory.h src/sync-yunoshared-memory.h > yunoshared-memory.h 

yunoshared-memory.lib: compiled/allocate-yunoshared-memory.o compiled/free-yunoshared-memory.o compiled/global-yunoshared-memory.o compiled/init-yunoshared-memory.o compiled/sync-yunoshared-memory.o
	ar r yunoshared-memory.lib compiled/allocate-yunoshared-memory.o compiled/free-yunoshared-memory.o compiled/global-yunoshared-memory.o compiled/init-yunoshared-memory.o compiled/sync-yunoshared-memory.o

compiled/allocate-yunoshared-memory.o: src/allocate-yunoshared-memory.h 
	gcc $(CFLAGS) -c src/allocate-yunoshared-memory.c -o compiled/allocate-yunoshared-memory.o

compiled/free-yunoshared-memory.o: src/free-yunoshared-memory.h 
	gcc $(CFLAGS) -c src/free-yunoshared-memory.c -o compiled/free-yunoshared-memory.o

compiled/global-yunoshared-memory.o: src/global-yunoshared-memory.h 
	gcc $(CFLAGS) -c src/global-yunoshared-memory.c -o compiled/global-yunoshared-memory.o

compiled/init-yunoshared-memory.o: src/init-yunoshared-memory.h 
	gcc $(CFLAGS) -c src/init-yunoshared-memory.c -o compiled/init-yunoshared-memory.o

compiled/sync-yunoshared-memory.o: src/sync-yunoshared-memory.h 
	gcc $(CFLAGS) -c src/sync-yunoshared-memory.c -o compiled/sync-yunoshared-memory.o
