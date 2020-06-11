
.PHONY: clean
clean:
	rm -f compiled/test-yunoshared-memory.o
	rm -f compiled/test-yunoshared-memory1.o
	rm -f compiled/test-yunoshared-memory2.o
	rm -f yunoshared-memory.lib

.PHONY: lib
lib:
	make yunoshared-memory.lib 

yunoshared-memory.lib: compiled/test-yunoshared-memory.o compiled/test-yunoshared-memory1.o compiled/test-yunoshared-memory2.o
	ar r yunoshared-memory.lib compiled/test-yunoshared-memory.o compiled/test-yunoshared-memory1.o compiled/test-yunoshared-memory2.o

compiled/test-yunoshared-memory.o: src/test-yunoshared-memory.c 
	gcc $(CFLAGS) -c src/test-yunoshared-memory.c -o compiled/test-yunoshared-memory.o

compiled/test-yunoshared-memory1.o: src/test-yunoshared-memory1.c 
	gcc $(CFLAGS) -c src/test-yunoshared-memory1.c -o compiled/test-yunoshared-memory1.o

compiled/test-yunoshared-memory2.o: src/test-yunoshared-memory2.c 
	gcc $(CFLAGS) -c src/test-yunoshared-memory2.c -o compiled/test-yunoshared-memory2.o
