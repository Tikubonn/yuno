
.PHONY: clean
clean:
	rm -f compiled/make-yunosemaphore.o
	rm -f compiled/wait-yunosemaphore.o
	rm -f compiled/release-yunosemaphore.o
	rm -f compiled/close-yunosemaphore.o
	rm -f yunosemaphore.h
	rm -f yunosemaphore.lib 

.PHONY: h
h:
	make yunosemaphore.h 

.PHONY: lib 
lib:
	make yunosemaphore.lib 

yunosemaphore.h: yunosemaphore.p src/make-yunosemaphore.h src/wait-yunosemaphore.h src/release-yunosemaphore.h src/close-yunosemaphore.h
	cat yunosemaphore.p src/make-yunosemaphore.h src/wait-yunosemaphore.h src/release-yunosemaphore.h src/close-yunosemaphore.h > yunosemaphore.h 

yunosemaphore.lib: compiled/make-yunosemaphore.o compiled/wait-yunosemaphore.o compiled/release-yunosemaphore.o compiled/close-yunosemaphore.o
	ar r yunosemaphore.lib compiled/make-yunosemaphore.o compiled/wait-yunosemaphore.o compiled/release-yunosemaphore.o compiled/close-yunosemaphore.o

compiled/make-yunosemaphore.o: src/make-yunosemaphore.c 
	gcc $(CFLAGS) -c src/make-yunosemaphore.c -o compiled/make-yunosemaphore.o

compiled/wait-yunosemaphore.o: src/wait-yunosemaphore.c 
	gcc $(CFLAGS) -c src/wait-yunosemaphore.c -o compiled/wait-yunosemaphore.o

compiled/release-yunosemaphore.o: src/release-yunosemaphore.c 
	gcc $(CFLAGS) -c src/release-yunosemaphore.c -o compiled/release-yunosemaphore.o

compiled/close-yunosemaphore.o: src/close-yunosemaphore.c 
	gcc $(CFLAGS) -c src/close-yunosemaphore.c -o compiled/close-yunosemaphore.o
