
.always:

clean: .always
	rm -f yunomutex.lib
	rm -f yunomutex.private
	rm -f yunomutex.public
	rm -f compiled/close-yunomutex.o
	rm -f compiled/free-yunomutex.o
	rm -f compiled/make-yunomutex-manually.o
	rm -f compiled/make-yunomutex.o
	rm -f compiled/release-yunomutex.o
	rm -f compiled/wait-yunomutex.o

yunomutex.private: yunomutex.p
	cat yunomutex.p > yunomutex.private

yunomutex.public: yunomutex.p
	cat yunomutex.p > yunomutex.public

yunomutex.a: compiled/close-yunomutex.o compiled/free-yunomutex.o compiled/make-yunomutex-manually.o compiled/make-yunomutex.o compiled/release-yunomutex.o compiled/wait-yunomutex.o
	ar r yunomutex.a compiled/close-yunomutex.o compiled/free-yunomutex.o compiled/make-yunomutex-manually.o compiled/make-yunomutex.o compiled/release-yunomutex.o compiled/wait-yunomutex.o

compiled/close-yunomutex.o: src/close-yunomutex.c 
	gcc $(CFLAGS) -c src/close-yunomutex.c -o compiled/close-yunomutex.o

compiled/free-yunomutex.o: src/free-yunomutex.c 
	gcc $(CFLAGS) -c src/free-yunomutex.c -o compiled/free-yunomutex.o

compiled/make-yunomutex-manually.o: src/make-yunomutex-manually.c 
	gcc $(CFLAGS) -c src/make-yunomutex-manually.c -o compiled/make-yunomutex-manually.o

compiled/make-yunomutex.o: src/make-yunomutex.c 
	gcc $(CFLAGS) -c src/make-yunomutex.c -o compiled/make-yunomutex.o

compiled/release-yunomutex.o: src/release-yunomutex.c 
	gcc $(CFLAGS) -c src/release-yunomutex.c -o compiled/release-yunomutex.o

compiled/wait-yunomutex.o: src/wait-yunomutex.c 
	gcc $(CFLAGS) -c src/wait-yunomutex.c -o compiled/wait-yunomutex.o
