
.always:

clean: .always
	rm -f yunofile.a
	rm -f yunofile.private
	rm -f yunofile.public
	rm -f compiled/close-yunofile.o
	rm -f compiled/free-yunofile.o
	rm -f compiled/get-async-yunostandard-error.o
	rm -f compiled/get-async-yunostandard-error-manually.o
	rm -f compiled/get-async-yunostandard-input.o
	rm -f compiled/get-async-yunostandard-input-manually.o
	rm -f compiled/get-async-yunostandard-output.o
	rm -f compiled/get-async-yunostandard-output-manually.o
	rm -f compiled/get-yunostandard-error.o
	rm -f compiled/get-yunostandard-error-manually.o
	rm -f compiled/get-yunostandard-input.o
	rm -f compiled/get-yunostandard-input-manually.o
	rm -f compiled/get-yunostandard-output.o
	rm -f compiled/get-yunostandard-output-manually.o
	rm -f compiled/init-async-yunofile.o
	rm -f compiled/init-yunofile.o
	rm -f compiled/open-async-yunofile.o
	rm -f compiled/open-async-yunofile-manually.o
	rm -f compiled/open-yunofile.o
	rm -f compiled/open-yunofile-manually.o
	rm -f compiled/read-yunofile.o
	rm -f compiled/request-read-yunofile.o
	rm -f compiled/request-write-yunofile.o
	rm -f compiled/seek-yunofile.o
	rm -f compiled/setup-aiocb-by-yunofile.o
	rm -f compiled/tell-yunofile.o
	rm -f compiled/wait-read-yunofile.o
	rm -f compiled/wait-write-yunofile.o
	rm -f compiled/write-yunofile.o
	rm -f compiled/yunofile-readablep.o
	rm -f compiled/yunofile-writablep.o

yunofile.private: yunofile.p src/init-yunofile.h src/init-async-yunofile.h src/setup-aiocb-by-yunofile.h
	cat yunofile.p src/init-yunofile.h src/init-async-yunofile.h src/setup-aiocb-by-yunofile.h > yunofile.private

yunofile.public: yunofile.p
	cat yunofile.p > yunofile.public

yunofile.a: compiled/close-yunofile.o compiled/free-yunofile.o compiled/get-async-yunostandard-error.o compiled/get-async-yunostandard-error-manually.o compiled/get-async-yunostandard-input.o compiled/get-async-yunostandard-input-manually.o compiled/get-async-yunostandard-output.o compiled/get-async-yunostandard-output-manually.o compiled/get-yunostandard-error.o compiled/get-yunostandard-error-manually.o compiled/get-yunostandard-input.o compiled/get-yunostandard-input-manually.o compiled/get-yunostandard-output.o compiled/get-yunostandard-output-manually.o compiled/init-async-yunofile.o compiled/init-yunofile.o compiled/open-async-yunofile.o compiled/open-async-yunofile-manually.o compiled/open-yunofile.o compiled/open-yunofile-manually.o compiled/read-yunofile.o compiled/request-read-yunofile.o compiled/request-write-yunofile.o compiled/seek-yunofile.o compiled/setup-aiocb-by-yunofile.o compiled/tell-yunofile.o compiled/wait-read-yunofile.o compiled/wait-write-yunofile.o compiled/write-yunofile.o compiled/yunofile-readablep.o compiled/yunofile-writablep.o
	ar r yunofile.a compiled/close-yunofile.o compiled/free-yunofile.o compiled/get-async-yunostandard-error.o compiled/get-async-yunostandard-error-manually.o compiled/get-async-yunostandard-input.o compiled/get-async-yunostandard-input-manually.o compiled/get-async-yunostandard-output.o compiled/get-async-yunostandard-output-manually.o compiled/get-yunostandard-error.o compiled/get-yunostandard-error-manually.o compiled/get-yunostandard-input.o compiled/get-yunostandard-input-manually.o compiled/get-yunostandard-output.o compiled/get-yunostandard-output-manually.o compiled/init-async-yunofile.o compiled/init-yunofile.o compiled/open-async-yunofile.o compiled/open-async-yunofile-manually.o compiled/open-yunofile.o compiled/open-yunofile-manually.o compiled/read-yunofile.o compiled/request-read-yunofile.o compiled/request-write-yunofile.o compiled/seek-yunofile.o compiled/setup-aiocb-by-yunofile.o compiled/tell-yunofile.o compiled/wait-read-yunofile.o compiled/wait-write-yunofile.o compiled/write-yunofile.o compiled/yunofile-readablep.o compiled/yunofile-writablep.o

compiled/close-yunofile.o: src/close-yunofile.c 
	gcc $(CFLAGS) -c src/close-yunofile.c -o compiled/close-yunofile.o

compiled/free-yunofile.o: src/free-yunofile.c 
	gcc $(CFLAGS) -c src/free-yunofile.c -o compiled/free-yunofile.o

compiled/get-async-yunostandard-error.o: src/get-async-yunostandard-error.c 
	gcc $(CFLAGS) -c src/get-async-yunostandard-error.c -o compiled/get-async-yunostandard-error.o

compiled/get-async-yunostandard-error-manually.o: src/get-async-yunostandard-error-manually.c 
	gcc $(CFLAGS) -c src/get-async-yunostandard-error-manually.c -o compiled/get-async-yunostandard-error-manually.o

compiled/get-async-yunostandard-input.o: src/get-async-yunostandard-input.c 
	gcc $(CFLAGS) -c src/get-async-yunostandard-input.c -o compiled/get-async-yunostandard-input.o

compiled/get-async-yunostandard-input-manually.o: src/get-async-yunostandard-input-manually.c 
	gcc $(CFLAGS) -c src/get-async-yunostandard-input-manually.c -o compiled/get-async-yunostandard-input-manually.o

compiled/get-async-yunostandard-output.o: src/get-async-yunostandard-output.c 
	gcc $(CFLAGS) -c src/get-async-yunostandard-output.c -o compiled/get-async-yunostandard-output.o

compiled/get-async-yunostandard-output-manually.o: src/get-async-yunostandard-output-manually.c 
	gcc $(CFLAGS) -c src/get-async-yunostandard-output-manually.c -o compiled/get-async-yunostandard-output-manually.o

compiled/get-yunostandard-error.o: src/get-yunostandard-error.c 
	gcc $(CFLAGS) -c src/get-yunostandard-error.c -o compiled/get-yunostandard-error.o

compiled/get-yunostandard-error-manually.o: src/get-yunostandard-error-manually.c 
	gcc $(CFLAGS) -c src/get-yunostandard-error-manually.c -o compiled/get-yunostandard-error-manually.o

compiled/get-yunostandard-input.o: src/get-yunostandard-input.c 
	gcc $(CFLAGS) -c src/get-yunostandard-input.c -o compiled/get-yunostandard-input.o

compiled/get-yunostandard-input-manually.o: src/get-yunostandard-input-manually.c 
	gcc $(CFLAGS) -c src/get-yunostandard-input-manually.c -o compiled/get-yunostandard-input-manually.o

compiled/get-yunostandard-output.o: src/get-yunostandard-output.c 
	gcc $(CFLAGS) -c src/get-yunostandard-output.c -o compiled/get-yunostandard-output.o

compiled/get-yunostandard-output-manually.o: src/get-yunostandard-output-manually.c 
	gcc $(CFLAGS) -c src/get-yunostandard-output-manually.c -o compiled/get-yunostandard-output-manually.o

compiled/init-async-yunofile.o: src/init-async-yunofile.c 
	gcc $(CFLAGS) -c src/init-async-yunofile.c -o compiled/init-async-yunofile.o

compiled/init-yunofile.o: src/init-yunofile.c 
	gcc $(CFLAGS) -c src/init-yunofile.c -o compiled/init-yunofile.o

compiled/open-async-yunofile.o: src/open-async-yunofile.c 
	gcc $(CFLAGS) -c src/open-async-yunofile.c -o compiled/open-async-yunofile.o

compiled/open-async-yunofile-manually.o: src/open-async-yunofile-manually.c 
	gcc $(CFLAGS) -c src/open-async-yunofile-manually.c -o compiled/open-async-yunofile-manually.o

compiled/open-yunofile.o: src/open-yunofile.c 
	gcc $(CFLAGS) -c src/open-yunofile.c -o compiled/open-yunofile.o

compiled/open-yunofile-manually.o: src/open-yunofile-manually.c 
	gcc $(CFLAGS) -c src/open-yunofile-manually.c -o compiled/open-yunofile-manually.o

compiled/read-yunofile.o: src/read-yunofile.c 
	gcc $(CFLAGS) -c src/read-yunofile.c -o compiled/read-yunofile.o

compiled/request-read-yunofile.o: src/request-read-yunofile.c 
	gcc $(CFLAGS) -c src/request-read-yunofile.c -o compiled/request-read-yunofile.o

compiled/request-write-yunofile.o: src/request-write-yunofile.c 
	gcc $(CFLAGS) -c src/request-write-yunofile.c -o compiled/request-write-yunofile.o

compiled/seek-yunofile.o: src/seek-yunofile.c 
	gcc $(CFLAGS) -c src/seek-yunofile.c -o compiled/seek-yunofile.o

compiled/setup-aiocb-by-yunofile.o: src/setup-aiocb-by-yunofile.c 
	gcc $(CFLAGS) -c src/setup-aiocb-by-yunofile.c -o compiled/setup-aiocb-by-yunofile.o

compiled/tell-yunofile.o: src/tell-yunofile.c 
	gcc $(CFLAGS) -c src/tell-yunofile.c -o compiled/tell-yunofile.o

compiled/wait-read-yunofile.o: src/wait-read-yunofile.c 
	gcc $(CFLAGS) -c src/wait-read-yunofile.c -o compiled/wait-read-yunofile.o

compiled/wait-write-yunofile.o: src/wait-write-yunofile.c 
	gcc $(CFLAGS) -c src/wait-write-yunofile.c -o compiled/wait-write-yunofile.o

compiled/write-yunofile.o: src/write-yunofile.c 
	gcc $(CFLAGS) -c src/write-yunofile.c -o compiled/write-yunofile.o

compiled/yunofile-readablep.o: src/yunofile-readablep.o
	gcc $(CFLAGS) -c src/yunofile-readablep.c -o compiled/yunofile-readablep.o

compiled/yunofile-writablep.o: src/yunofile-writablep.o
	gcc $(CFLAGS) -c src/yunofile-writablep.c -o compiled/yunofile-writablep.o

