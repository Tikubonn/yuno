
.PHONY: clean
clean:
	rm -f compiled/test-yunosemaphore.o
	rm -f compiled/test-yunosemaphore1.o
	rm -f compiled/test-yunosemaphore2.o
	rm -f yunosemaphore.lib

.PHONY: lib 
lib:
	make yunosemaphore.lib 

yunosemaphore.lib: compiled/test-yunosemaphore.o compiled/test-yunosemaphore1.o compiled/test-yunosemaphore2.o
	ar r yunosemaphore.lib compiled/test-yunosemaphore.o compiled/test-yunosemaphore1.o compiled/test-yunosemaphore2.o

compiled/test-yunosemaphore.o: src/test-yunosemaphore.c 
	gcc $(CFLAGS) -c src/test-yunosemaphore.c -o compiled/test-yunosemaphore.o

compiled/test-yunosemaphore1.o: src/test-yunosemaphore1.c 
	gcc $(CFLAGS) -c src/test-yunosemaphore1.c -o compiled/test-yunosemaphore1.o

compiled/test-yunosemaphore2.o: src/test-yunosemaphore2.c 
	gcc $(CFLAGS) -c src/test-yunosemaphore2.c -o compiled/test-yunosemaphore2.o
