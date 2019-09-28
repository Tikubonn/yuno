
.always:

clean:
	rm -f yunofile.private
	rm -f yunofile.public
	rm -f yunofile.lib
	rm -f compiled/setup-yunofile-overlapped.o
	rm -f compiled/write-sync-yunofile.o
	rm -f compiled/write-yunofile.o
	rm -f compiled/request-write-yunofile.o
	rm -f compiled/wait-write-yunofile.o
	rm -f compiled/read-sync-yunofile.o
	rm -f compiled/read-yunofile.o
	rm -f compiled/request-read-yunofile.o
	rm -f compiled/wait-read-yunofile.o
	rm -f compiled/init-yunofile.o
	rm -f compiled/init-async-yunofile.o
	rm -f compiled/parse-yunofile-mode.o
	rm -f compiled/open-yunostandard-input-manually.o
	rm -f compiled/open-yunostandard-output-manually.o
	rm -f compiled/open-yunostandard-error-manually.o
	rm -f compiled/open-async-yunostandard-input-manually.o
	rm -f compiled/open-async-yunostandard-output-manually.o
	rm -f compiled/open-async-yunostandard-error-manually.o
	rm -f compiled/open-yunostandard-input.o
	rm -f compiled/open-yunostandard-output.o
	rm -f compiled/open-yunostandard-error.o
	rm -f compiled/open-async-yunostandard-input.o
	rm -f compiled/open-async-yunostandard-output.o
	rm -f compiled/open-async-yunostandard-error.o
	rm -f compiled/open-yunofile-manually.o
	rm -f compiled/open-async-yunofile-manually.o
	rm -f compiled/open-yunofile.o
	rm -f compiled/open-async-yunofile.o
	rm -f compiled/close-yunofile.o
	rm -f compiled/free-yunofile.o
	rm -f compiled/tell-yunofile.o
	rm -f compiled/seek-yunofile.o
	rm -f compiled/yunofile-readablep.o
	rm -f compiled/yunofile-writablep.o

yunofile.private: yunofile.p src/init-yunofile.h src/init-async-yunofile.h src/setup-yunofile-overlapped.h src/read-sync-yunofile.h src/write-sync-yunofile.h src/parse-yunofile-mode.h
	cat yunofile.p src/init-yunofile.h src/init-async-yunofile.h src/setup-yunofile-overlapped.h src/read-sync-yunofile.h src/write-sync-yunofile.h src/parse-yunofile-mode.h > yunofile.private

yunofile.public: yunofile.p 
	cp yunofile.p yunofile.public

yunofile.lib: compiled/setup-yunofile-overlapped.o compiled/write-sync-yunofile.o compiled/write-yunofile.o compiled/request-write-yunofile.o compiled/wait-write-yunofile.o compiled/read-sync-yunofile.o compiled/read-yunofile.o compiled/request-read-yunofile.o compiled/wait-read-yunofile.o compiled/init-yunofile.o compiled/init-async-yunofile.o compiled/parse-yunofile-mode.o compiled/open-yunostandard-input-manually.o compiled/open-yunostandard-output-manually.o compiled/open-yunostandard-error-manually.o compiled/open-async-yunostandard-input-manually.o compiled/open-async-yunostandard-output-manually.o compiled/open-async-yunostandard-error-manually.o compiled/open-yunostandard-input.o compiled/open-yunostandard-output.o compiled/open-yunostandard-error.o compiled/open-async-yunostandard-input.o compiled/open-async-yunostandard-output.o compiled/open-async-yunostandard-error.o compiled/open-yunofile-manually.o compiled/open-async-yunofile-manually.o compiled/open-yunofile.o compiled/open-async-yunofile.o compiled/close-yunofile.o compiled/free-yunofile.o compiled/tell-yunofile.o compiled/seek-yunofile.o compiled/yunofile-readablep.o compiled/yunofile-writablep.o
	ar r yunofile.lib compiled/setup-yunofile-overlapped.o compiled/write-sync-yunofile.o compiled/write-yunofile.o compiled/request-write-yunofile.o compiled/wait-write-yunofile.o compiled/read-sync-yunofile.o compiled/read-yunofile.o compiled/request-read-yunofile.o compiled/wait-read-yunofile.o compiled/init-yunofile.o compiled/init-async-yunofile.o compiled/parse-yunofile-mode.o compiled/open-yunostandard-input-manually.o compiled/open-yunostandard-output-manually.o compiled/open-yunostandard-error-manually.o compiled/open-async-yunostandard-input-manually.o compiled/open-async-yunostandard-output-manually.o compiled/open-async-yunostandard-error-manually.o compiled/open-yunostandard-input.o compiled/open-yunostandard-output.o compiled/open-yunostandard-error.o compiled/open-async-yunostandard-input.o compiled/open-async-yunostandard-output.o compiled/open-async-yunostandard-error.o compiled/open-yunofile-manually.o compiled/open-async-yunofile-manually.o compiled/open-yunofile.o compiled/open-async-yunofile.o compiled/close-yunofile.o compiled/free-yunofile.o compiled/tell-yunofile.o compiled/seek-yunofile.o compiled/yunofile-readablep.o compiled/yunofile-writablep.o

compiled/setup-yunofile-overlapped.o: src/setup-yunofile-overlapped.c 
	gcc $(CFLAGS) -c src/setup-yunofile-overlapped.c -o compiled/setup-yunofile-overlapped.o

compiled/write-sync-yunofile.o: src/write-sync-yunofile.c 
	gcc $(CFLAGS) -c src/write-sync-yunofile.c -o compiled/write-sync-yunofile.o

compiled/write-yunofile.o: src/write-yunofile.c 
	gcc $(CFLAGS) -c src/write-yunofile.c -o compiled/write-yunofile.o

compiled/request-write-yunofile.o: src/request-write-yunofile.c 
	gcc $(CFLAGS) -c src/request-write-yunofile.c -o compiled/request-write-yunofile.o

compiled/wait-write-yunofile.o: src/wait-write-yunofile.c 
	gcc $(CFLAGS) -c src/wait-write-yunofile.c -o compiled/wait-write-yunofile.o

compiled/read-sync-yunofile.o: src/read-sync-yunofile.c 
	gcc $(CFLAGS) -c src/read-sync-yunofile.c -o compiled/read-sync-yunofile.o

compiled/read-yunofile.o: src/read-yunofile.c 
	gcc $(CFLAGS) -c src/read-yunofile.c -o compiled/read-yunofile.o

compiled/request-read-yunofile.o: src/request-read-yunofile.c 
	gcc $(CFLAGS) -c src/request-read-yunofile.c -o compiled/request-read-yunofile.o

compiled/wait-read-yunofile.o: src/wait-read-yunofile.c 
	gcc $(CFLAGS) -c src/wait-read-yunofile.c -o compiled/wait-read-yunofile.o

compiled/init-yunofile.o: src/init-yunofile.c 
	gcc $(CFLAGS) -c src/init-yunofile.c -o compiled/init-yunofile.o

compiled/init-async-yunofile.o: src/init-async-yunofile.c 
	gcc $(CFLAGS) -c src/init-async-yunofile.c -o compiled/init-async-yunofile.o

compiled/parse-yunofile-mode.o: src/parse-yunofile-mode.c 
	gcc $(CFLAGS) -c src/parse-yunofile-mode.c -o compiled/parse-yunofile-mode.o

compiled/open-yunostandard-input-manually.o: src/open-yunostandard-input-manually.c 
	gcc $(CFLAGS) -c src/open-yunostandard-input-manually.c -o compiled/open-yunostandard-input-manually.o

compiled/open-yunostandard-output-manually.o: src/open-yunostandard-output-manually.c 
	gcc $(CFLAGS) -c src/open-yunostandard-output-manually.c -o compiled/open-yunostandard-output-manually.o

compiled/open-yunostandard-error-manually.o: src/open-yunostandard-error-manually.c 
	gcc $(CFLAGS) -c src/open-yunostandard-error-manually.c -o compiled/open-yunostandard-error-manually.o

compiled/open-async-yunostandard-input-manually.o: src/open-async-yunostandard-input-manually.c 
	gcc $(CFLAGS) -c src/open-async-yunostandard-input-manually.c -o compiled/open-async-yunostandard-input-manually.o

compiled/open-async-yunostandard-output-manually.o: src/open-async-yunostandard-output-manually.c 
	gcc $(CFLAGS) -c src/open-async-yunostandard-output-manually.c -o compiled/open-async-yunostandard-output-manually.o

compiled/open-async-yunostandard-error-manually.o: src/open-async-yunostandard-error-manually.c 
	gcc $(CFLAGS) -c src/open-async-yunostandard-error-manually.c -o compiled/open-async-yunostandard-error-manually.o

compiled/open-yunostandard-input.o: src/open-yunostandard-input.c 
	gcc $(CFLAGS) -c src/open-yunostandard-input.c -o compiled/open-yunostandard-input.o

compiled/open-yunostandard-output.o: src/open-yunostandard-output.c 
	gcc $(CFLAGS) -c src/open-yunostandard-output.c -o compiled/open-yunostandard-output.o

compiled/open-yunostandard-error.o: src/open-yunostandard-error.c 
	gcc $(CFLAGS) -c src/open-yunostandard-error.c -o compiled/open-yunostandard-error.o

compiled/open-async-yunostandard-input.o: src/open-async-yunostandard-input.c 
	gcc $(CFLAGS) -c src/open-async-yunostandard-input.c -o compiled/open-async-yunostandard-input.o

compiled/open-async-yunostandard-output.o: src/open-async-yunostandard-output.c 
	gcc $(CFLAGS) -c src/open-async-yunostandard-output.c -o compiled/open-async-yunostandard-output.o

compiled/open-async-yunostandard-error.o: src/open-async-yunostandard-error.c 
	gcc $(CFLAGS) -c src/open-async-yunostandard-error.c -o compiled/open-async-yunostandard-error.o

compiled/open-yunofile-manually.o: src/open-yunofile-manually.c 
	gcc $(CFLAGS) -c src/open-yunofile-manually.c -o compiled/open-yunofile-manually.o

compiled/open-async-yunofile-manually.o: src/open-async-yunofile-manually.c 
	gcc $(CFLAGS) -c src/open-async-yunofile-manually.c -o compiled/open-async-yunofile-manually.o

compiled/open-yunofile.o: src/open-yunofile.c 
	gcc $(CFLAGS) -c src/open-yunofile.c -o compiled/open-yunofile.o

compiled/open-async-yunofile.o: src/open-async-yunofile.c 
	gcc $(CFLAGS) -c src/open-async-yunofile.c -o compiled/open-async-yunofile.o

compiled/close-yunofile.o: src/close-yunofile.c 
	gcc $(CFLAGS) -c src/close-yunofile.c -o compiled/close-yunofile.o

compiled/free-yunofile.o: src/free-yunofile.c 
	gcc $(CFLAGS) -c src/free-yunofile.c -o compiled/free-yunofile.o

compiled/tell-yunofile.o: src/tell-yunofile.c 
	gcc $(CFLAGS) -c src/tell-yunofile.c -o compiled/tell-yunofile.o

compiled/seek-yunofile.o: src/seek-yunofile.c 
	gcc $(CFLAGS) -c src/seek-yunofile.c -o compiled/seek-yunofile.o

compiled/yunofile-readablep.o: src/yunofile-readablep.c 
	gcc $(CFLAGS) -c src/yunofile-readablep.c -o compiled/yunofile-readablep.o

compiled/yunofile-writablep.o: src/yunofile-writablep.c 
	gcc $(CFLAGS) -c src/yunofile-writablep.c -o compiled/yunofile-writablep.o