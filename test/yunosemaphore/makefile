
all: .always
	make yunosemaphore.lib

clean: .always
	rm -f yunosemaphore.lib
	rm -f compiled/test-yunosemaphore.o
	rm -f compiled/test-make-yunosemaphore.o
	rm -f compiled/test-make-named-yunosemaphore.o

yunosemaphore.lib: compiled/test-yunosemaphore.o compiled/test-make-yunosemaphore.o compiled/test-make-named-yunosemaphore.o
	ar r yunosemaphore.lib compiled/test-yunosemaphore.o compiled/test-make-yunosemaphore.o compiled/test-make-named-yunosemaphore.o

compiled/test-yunosemaphore.o: src/test-yunosemaphore.c
	gcc $(CFLAGS) -c src/test-yunosemaphore.c -o compiled/test-yunosemaphore.o

compiled/test-make-yunosemaphore.o: src/test-make-yunosemaphore.c
	gcc $(CFLAGS) -c src/test-make-yunosemaphore.c -o compiled/test-make-yunosemaphore.o

compiled/test-make-named-yunosemaphore.o: src/test-make-named-yunosemaphore.c
	gcc $(CFLAGS) -c src/test-make-named-yunosemaphore.c -o compiled/test-make-named-yunosemaphore.o

.always:
