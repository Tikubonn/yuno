
.always:

clean: .always
	rm -f yunosemaphore.lib
	rm -f yunosemaphore.private
	rm -f yunosemaphore.public
	rm -f compiled/make-yunosemaphore-manually.o
	rm -f compiled/make-named-yunosemaphore-manually.o
	rm -f compiled/make-yunosemaphore.o
	rm -f compiled/make-named-yunosemaphore.o
	rm -f compiled/wait-yunosemaphore.o
	rm -f compiled/release-yunosemaphore.o
	rm -f compiled/close-yunosemaphore.o
	rm -f compiled/free-yunosemaphore.o

yunosemaphore.private: yunosemaphore.p
	cp yunosemaphore.p yunosemaphore.private

yunosemaphore.public: yunosemaphore.p
	cp yunosemaphore.p yunosemaphore.public

yunosemaphore.lib: compiled/make-yunosemaphore-manually.o compiled/make-named-yunosemaphore-manually.o compiled/make-yunosemaphore.o compiled/make-named-yunosemaphore.o compiled/wait-yunosemaphore.o compiled/release-yunosemaphore.o compiled/close-yunosemaphore.o compiled/free-yunosemaphore.o
	ar r yunosemaphore.lib compiled/make-yunosemaphore-manually.o compiled/make-named-yunosemaphore-manually.o compiled/make-yunosemaphore.o compiled/make-named-yunosemaphore.o compiled/wait-yunosemaphore.o compiled/release-yunosemaphore.o compiled/close-yunosemaphore.o compiled/free-yunosemaphore.o

compiled/make-yunosemaphore-manually.o: src/make-yunosemaphore-manually.c 
	gcc $(CFLAGS) -c src/make-yunosemaphore-manually.c -o compiled/make-yunosemaphore-manually.o
	
compiled/make-named-yunosemaphore-manually.o: src/make-named-yunosemaphore-manually.c 
	gcc $(CFLAGS) -c src/make-named-yunosemaphore-manually.c -o compiled/make-named-yunosemaphore-manually.o
	
compiled/make-yunosemaphore.o: src/make-yunosemaphore.c
	gcc $(CFLAGS) -c src/make-yunosemaphore.c -o compiled/make-yunosemaphore.o
	
compiled/make-named-yunosemaphore.o: src/make-named-yunosemaphore.c
	gcc $(CFLAGS) -c src/make-named-yunosemaphore.c -o compiled/make-named-yunosemaphore.o
	
compiled/wait-yunosemaphore.o: src/wait-yunosemaphore.c 
	gcc $(CFLAGS) -c src/wait-yunosemaphore.c -o compiled/wait-yunosemaphore.o
	
compiled/release-yunosemaphore.o: src/release-yunosemaphore.c
	gcc $(CFLAGS) -c src/release-yunosemaphore.c -o compiled/release-yunosemaphore.o
	
compiled/close-yunosemaphore.o: src/close-yunosemaphore.c
	gcc $(CFLAGS) -c src/close-yunosemaphore.c -o compiled/close-yunosemaphore.o
	
compiled/free-yunosemaphore.o: src/free-yunosemaphore.c 
	gcc $(CFLAGS) -c src/free-yunosemaphore.c -o compiled/free-yunosemaphore.o
