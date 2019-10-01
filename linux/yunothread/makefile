
.always:

clean: .always
	rm -f compiled/make-yunothread-manually.o
	rm -f compiled/make-yunothread.o
	rm -f compiled/start-yunothread.o
	rm -f compiled/wait-yunothread.o
	rm -f compiled/close-yunothread.o
	rm -f compiled/free-yunothread.o
	rm -f compiled/get-yunothread-exit-code.o

yunothread.private: yunothread.p
	cp yunothread.p yunothread.private

yunothread.public: yunothread.p
	cp yunothread.p yunothread.public

yunothread.a: compiled/make-yunothread-manually.o compiled/make-yunothread.o compiled/start-yunothread.o compiled/wait-yunothread.o compiled/close-yunothread.o compiled/free-yunothread.o compiled/get-yunothread-exit-code.o
	ar r yunothread.a compiled/make-yunothread-manually.o compiled/make-yunothread.o compiled/start-yunothread.o compiled/wait-yunothread.o compiled/close-yunothread.o compiled/free-yunothread.o compiled/get-yunothread-exit-code.o

compiled/make-yunothread-manually.o: src/make-yunothread-manually.c
	gcc $(CFLAGS) -c src/make-yunothread-manually.c -o compiled/make-yunothread-manually.o

compiled/make-yunothread.o: src/make-yunothread.c
	gcc $(CFLAGS) -c src/make-yunothread.c -o compiled/make-yunothread.o

compiled/start-yunothread.o: src/start-yunothread.c
	gcc $(CFLAGS) -c src/start-yunothread.c -o compiled/start-yunothread.o

compiled/wait-yunothread.o: src/wait-yunothread.c
	gcc $(CFLAGS) -c src/wait-yunothread.c -o compiled/wait-yunothread.o

compiled/close-yunothread.o: src/close-yunothread.c
	gcc $(CFLAGS) -c src/close-yunothread.c -o compiled/close-yunothread.o

compiled/free-yunothread.o: src/free-yunothread.c
	gcc $(CFLAGS) -c src/free-yunothread.c -o compiled/free-yunothread.o

compiled/get-yunothread-exit-code.o: src/get-yunothread-exit-code.c
	gcc $(CFLAGS) -c src/get-yunothread-exit-code.c -o compiled/get-yunothread-exit-code.o

