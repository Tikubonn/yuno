
all:
	make yunomutex.lib

clean: 
	rm -f yunomutex.lib
	rm -f compiled/test-make-yunomutex.o
	rm -f compiled/test-make-yunomutex2.o
	rm -f compiled/test-make-named-yunomutex.o
	rm -f compiled/test-make-named-yunomutex2.o
	rm -f compiled/test-yunomutex.o

yunomutex.lib: compiled/test-make-yunomutex.o compiled/test-make-yunomutex2.o compiled/test-make-named-yunomutex.o compiled/test-make-named-yunomutex2.o compiled/test-yunomutex.o
	ar r yunomutex.lib compiled/test-make-yunomutex.o compiled/test-make-yunomutex2.o compiled/test-make-named-yunomutex.o compiled/test-make-named-yunomutex2.o compiled/test-yunomutex.o

compiled/test-make-yunomutex.o: src/test-make-yunomutex.c 
	gcc $(CFLAGS) -c src/test-make-yunomutex.c -o compiled/test-make-yunomutex.o

compiled/test-make-yunomutex2.o: src/test-make-yunomutex2.c 
	gcc $(CFLAGS) -c src/test-make-yunomutex2.c -o compiled/test-make-yunomutex2.o

compiled/test-make-named-yunomutex.o: src/test-make-named-yunomutex.c 
	gcc $(CFLAGS) -c src/test-make-named-yunomutex.c -o compiled/test-make-named-yunomutex.o

compiled/test-make-named-yunomutex2.o: src/test-make-named-yunomutex2.c 
	gcc $(CFLAGS) -c src/test-make-named-yunomutex2.c -o compiled/test-make-named-yunomutex2.o

compiled/test-yunomutex.o: src/test-yunomutex.c 
	gcc $(CFLAGS) -c src/test-yunomutex.c -o compiled/test-yunomutex.o
