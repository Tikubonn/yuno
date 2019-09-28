
.always:

clean: .always
	rm -f yunoprocess.lib
	rm -f yunoprocess.private
	rm -f yunoprocess.public
	rm -f compiled/make-yunoprocess-manually.o
	rm -f compiled/make-yunoprocess.o
	rm -f compiled/start-yunoprocess.o
	rm -f compiled/wait-yunoprocess.o
	rm -f compiled/close-yunoprocess.o
	rm -f compiled/get-yunoprocess-exit-code.o
	rm -f compiled/free-yunoprocess.o

yunoprocess.private: yunoprocess.p
	cat yunoprocess.p > yunoprocess.private

yunoprocess.public: yunoprocess.p
	cat yunoprocess.p > yunoprocess.public

yunoprocess.lib: compiled/make-yunoprocess-manually.o compiled/make-yunoprocess.o compiled/start-yunoprocess.o compiled/wait-yunoprocess.o compiled/close-yunoprocess.o compiled/get-yunoprocess-exit-code.o compiled/free-yunoprocess.o
	ar r yunoprocess.lib compiled/make-yunoprocess-manually.o compiled/make-yunoprocess.o compiled/start-yunoprocess.o compiled/wait-yunoprocess.o compiled/close-yunoprocess.o compiled/get-yunoprocess-exit-code.o compiled/free-yunoprocess.o

compiled/make-yunoprocess-manually.o: src/make-yunoprocess-manually.c 
	gcc $(CFLAGS) -lpsapi -c src/make-yunoprocess-manually.c -o compiled/make-yunoprocess-manually.o

compiled/make-yunoprocess.o: src/make-yunoprocess.c 
	gcc $(CFLAGS) -c src/make-yunoprocess.c -o compiled/make-yunoprocess.o

compiled/start-yunoprocess.o: src/start-yunoprocess.c 
	gcc $(CFLAGS) -c src/start-yunoprocess.c -o compiled/start-yunoprocess.o

compiled/wait-yunoprocess.o: src/wait-yunoprocess.c 
	gcc $(CFLAGS) -c src/wait-yunoprocess.c -o compiled/wait-yunoprocess.o

compiled/close-yunoprocess.o: src/close-yunoprocess.c 
	gcc $(CFLAGS) -c src/close-yunoprocess.c -o compiled/close-yunoprocess.o

compiled/get-yunoprocess-exit-code.o: src/get-yunoprocess-exit-code.c 
	gcc $(CFLAGS) -c src/get-yunoprocess-exit-code.c -o compiled/get-yunoprocess-exit-code.o

compiled/free-yunoprocess.o: src/free-yunoprocess.c 
	gcc $(CFLAGS) -c src/free-yunoprocess.c -o compiled/free-yunoprocess.o
