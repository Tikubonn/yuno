
.PHONY: clean
clean:
	rm -f compiled/allocate-yunomemory.o
	rm -f compiled/free-yunomemory.o
	rm -f yunomemory.h
	rm -f yunomemory.lib

.PHONY: h
h:
	make yunomemory.h 

.PHONY: lib
lib:
	make yunomemory.lib 

yunomemory.h: src/allocate-yunomemory.h src/free-yunomemory.h
	cat src/allocate-yunomemory.h src/free-yunomemory.h > yunomemory.h

yunomemory.lib: compiled/allocate-yunomemory.o compiled/free-yunomemory.o
	ar r yunomemory.lib compiled/allocate-yunomemory.o compiled/free-yunomemory.o

compiled/allocate-yunomemory.o: src/allocate-yunomemory.c 
	gcc $(CFLAGS) -c src/allocate-yunomemory.c -o compiled/allocate-yunomemory.o

compiled/free-yunomemory.o: src/free-yunomemory.c 
	gcc $(CFLAGS) -c src/free-yunomemory.c -o compiled/free-yunomemory.o
