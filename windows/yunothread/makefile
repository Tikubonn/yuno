
.always:

clean: .always
	rm -f yunothread.lib
	rm -f yunothread.private
	rm -f yunothread.public
	rm -f compiled/make-yunothread-manually.o
	rm -f compiled/make-yunothread.o
	rm -f compiled/start-yunothread.o
	rm -f compiled/wait-yunothread.o
	rm -f compiled/close-yunothread.o
	rm -f compiled/get-yunothread-exit-code.o
	rm -f compiled/free-yunothread.o

yunothread.private: yunothread.p
	cat yunothread.p > yunothread.private

yunothread.public: yunothread.p
	cat yunothread.p > yunothread.public

yunothread.lib: compiled/make-yunothread-manually.o compiled/make-yunothread.o compiled/start-yunothread.o compiled/wait-yunothread.o compiled/close-yunothread.o compiled/get-yunothread-exit-code.o compiled/free-yunothread.o
	ar r yunothread.lib compiled/make-yunothread-manually.o compiled/make-yunothread.o compiled/start-yunothread.o compiled/wait-yunothread.o compiled/close-yunothread.o compiled/get-yunothread-exit-code.o compiled/free-yunothread.o

compiled/make-yunothread-manually.o: src/make-yunothread-manually.c 
	gcc $(CFLAGS) -lpsapi -c src/make-yunothread-manually.c -o compiled/make-yunothread-manually.o

compiled/make-yunothread.o: src/make-yunothread.c 
	gcc $(CFLAGS) -c src/make-yunothread.c -o compiled/make-yunothread.o

compiled/start-yunothread.o: src/start-yunothread.c 
	gcc $(CFLAGS) -c src/start-yunothread.c -o compiled/start-yunothread.o

compiled/wait-yunothread.o: src/wait-yunothread.c 
	gcc $(CFLAGS) -c src/wait-yunothread.c -o compiled/wait-yunothread.o

compiled/close-yunothread.o: src/close-yunothread.c 
	gcc $(CFLAGS) -c src/close-yunothread.c -o compiled/close-yunothread.o

compiled/get-yunothread-exit-code.o: src/get-yunothread-exit-code.c 
	gcc $(CFLAGS) -c src/get-yunothread-exit-code.c -o compiled/get-yunothread-exit-code.o

compiled/free-yunothread.o: src/free-yunothread.c 
	gcc $(CFLAGS) -c src/free-yunothread.c -o compiled/free-yunothread.o
