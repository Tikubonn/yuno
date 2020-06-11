
.PHONY: clean
clean:
	rm -f compiled/test-yunomemory.o
	rm -f compiled/test-yunomemory1.o
	rm -f compiled/test-yunomemory2.o
	rm -f yunomemory.lib

.PHONY: lib
lib:
	make yunomemory.lib 

yunomemory.lib: compiled/test-yunomemory.o compiled/test-yunomemory1.o compiled/test-yunomemory2.o
	ar r yunomemory.lib compiled/test-yunomemory.o compiled/test-yunomemory1.o compiled/test-yunomemory2.o

compiled/test-yunomemory.o: src/test-yunomemory.c 
	gcc $(CFLAGS) -c src/test-yunomemory.c -o compiled/test-yunomemory.o

compiled/test-yunomemory1.o: src/test-yunomemory1.c 
	gcc $(CFLAGS) -c src/test-yunomemory1.c -o compiled/test-yunomemory1.o

compiled/test-yunomemory2.o: src/test-yunomemory2.c 
	gcc $(CFLAGS) -c src/test-yunomemory2.c -o compiled/test-yunomemory2.o
