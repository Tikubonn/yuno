
.PHONY: clean
clean:
	rm -f compiled/init-yunomemory.o
	rm -f compiled/allocate-yunomemory.o
	rm -f compiled/free-yunomemory.o
	rm -f compiled/remap-yunomemory.o

.PHONY: h
h:
	make yunomemory.h

.PHONY: lib
lib:
	make yunomemory.lib

yunomemory.lib: compiled/init-yunomemory.o compiled/allocate-yunomemory.o compiled/free-yunomemory.o compiled/remap-yunomemory.o
	ar r yunomemory.lib compiled/init-yunomemory.o compiled/allocate-yunomemory.o compiled/free-yunomemory.o compiled/remap-yunomemory.o

yunomemory.h: yunomemory.p src/init-yunomemory.h src/allocate-yunomemory.h src/free-yunomemory.h src/remap-yunomemory.h src/setup-yunomemory.h
	cat yunomemory.p src/init-yunomemory.h src/allocate-yunomemory.h src/free-yunomemory.h src/remap-yunomemory.h src/setup-yunomemory.h > yunomemory.h 

compiled/init-yunomemory.o: src/init-yunomemory.c 
	gcc $(CFLAGS) -c src/init-yunomemory.c -o compiled/init-yunomemory.o

compiled/allocate-yunomemory.o: src/allocate-yunomemory.c 
	gcc $(CFLAGS) -c src/allocate-yunomemory.c -o compiled/allocate-yunomemory.o

compiled/free-yunomemory.o: src/free-yunomemory.c 
	gcc $(CFLAGS) -c src/free-yunomemory.c -o compiled/free-yunomemory.o

compiled/remap-yunomemory.o: src/remap-yunomemory.c 
	gcc $(CFLAGS) -c src/remap-yunomemory.c -o compiled/remap-yunomemory.o
