
.PHONY: clean
clean:
	rm -f compiled/init-yunofile.o
	rm -f compiled/open-yunofile.o
	rm -f compiled/open-yunostandard-error.o
	rm -f compiled/open-yunostandard-input.o
	rm -f compiled/open-yunostandard-output.o
	rm -f compiled/close-yunofile.o
	rm -f compiled/setup-yunofile-overlapped.o
	rm -f compiled/seek-yunofile.o
	rm -f compiled/tell-yunofile.o
	rm -f compiled/request-read-yunofile.o
	rm -f compiled/request-write-yunofile.o
	rm -f compiled/wait-read-yunofile.o
	rm -f compiled/wait-write-yunofile.o
	rm -f compiled/read-yunofile.o
	rm -f compiled/write-yunofile.o
	rm -f compiled/yunofile-readablep.o
	rm -f compiled/yunofile-writablep.o
	rm -f compiled/yunofile-closedp.o
	rm -f compiled/yunofile-buffer-array.o
	rm -f compiled/yunofile-buffer-size.o
	rm -f compiled/yunofile-syncp.o
	rm -f compiled/yunofile-asyncp.o
	rm -f yunofile.h
	rm -f yunofile.lib

.PHONY: h
h: 
	make yunofile.h 

.PHONY: lib
lib: 
	make yunofile.lib 

yunofile.h: yunofile.p src/init-yunofile.h src/open-yunofile.h src/open-yunostandard-error.h src/open-yunostandard-input.h src/open-yunostandard-output.h src/close-yunofile.h src/setup-yunofile-overlapped.h src/seek-yunofile.h src/tell-yunofile.h src/request-read-yunofile.h src/request-write-yunofile.h src/wait-read-yunofile.h src/wait-write-yunofile.h src/read-yunofile.h src/write-yunofile.h src/yunofile-readablep.h src/yunofile-writablep.h src/yunofile-closedp.h src/yunofile-buffer-array.h src/yunofile-buffer-size.h src/yunofile-syncp.h src/yunofile-asyncp.h 
	cat yunofile.p src/init-yunofile.h src/open-yunofile.h src/open-yunostandard-error.h src/open-yunostandard-input.h src/open-yunostandard-output.h src/close-yunofile.h src/setup-yunofile-overlapped.h src/seek-yunofile.h src/tell-yunofile.h src/request-read-yunofile.h src/request-write-yunofile.h src/wait-read-yunofile.h src/wait-write-yunofile.h src/read-yunofile.h src/write-yunofile.h src/yunofile-readablep.h src/yunofile-writablep.h src/yunofile-closedp.h src/yunofile-buffer-array.h src/yunofile-buffer-size.h src/yunofile-syncp.h src/yunofile-asyncp.h > yunofile.h

yunofile.lib: compiled/init-yunofile.o compiled/open-yunofile.o compiled/open-yunostandard-error.o compiled/open-yunostandard-input.o compiled/open-yunostandard-output.o compiled/close-yunofile.o compiled/setup-yunofile-overlapped.o compiled/seek-yunofile.o compiled/tell-yunofile.o compiled/request-read-yunofile.o compiled/request-write-yunofile.o compiled/wait-read-yunofile.o compiled/wait-write-yunofile.o compiled/read-yunofile.o compiled/write-yunofile.o compiled/yunofile-readablep.o compiled/yunofile-writablep.o compiled/yunofile-closedp.o compiled/yunofile-buffer-array.o compiled/yunofile-buffer-size.o compiled/yunofile-syncp.o compiled/yunofile-asyncp.o
	ar r yunofile.lib compiled/init-yunofile.o compiled/open-yunofile.o compiled/open-yunostandard-error.o compiled/open-yunostandard-input.o compiled/open-yunostandard-output.o compiled/close-yunofile.o compiled/setup-yunofile-overlapped.o compiled/seek-yunofile.o compiled/tell-yunofile.o compiled/request-read-yunofile.o compiled/request-write-yunofile.o compiled/wait-read-yunofile.o compiled/wait-write-yunofile.o compiled/read-yunofile.o compiled/write-yunofile.o compiled/yunofile-readablep.o compiled/yunofile-writablep.o compiled/yunofile-closedp.o compiled/yunofile-buffer-array.o compiled/yunofile-buffer-size.o compiled/yunofile-syncp.o compiled/yunofile-asyncp.o

compiled/init-yunofile.o: src/init-yunofile.c 
	$(CC) $(CFLAGS) -c src/init-yunofile.c -o compiled/init-yunofile.o

compiled/open-yunofile.o: src/open-yunofile.c 
	$(CC) $(CFLAGS) -c src/open-yunofile.c -o compiled/open-yunofile.o

compiled/open-yunostandard-error.o: src/open-yunostandard-error.c 
	$(CC) $(CFLAGS) -c src/open-yunostandard-error.c -o compiled/open-yunostandard-error.o

compiled/open-yunostandard-input.o: src/open-yunostandard-input.c 
	$(CC) $(CFLAGS) -c src/open-yunostandard-input.c -o compiled/open-yunostandard-input.o

compiled/open-yunostandard-output.o: src/open-yunostandard-output.c 
	$(CC) $(CFLAGS) -c src/open-yunostandard-output.c -o compiled/open-yunostandard-output.o

compiled/close-yunofile.o: src/close-yunofile.c 
	$(CC) $(CFLAGS) -c src/close-yunofile.c -o compiled/close-yunofile.o

compiled/setup-yunofile-overlapped.o: src/setup-yunofile-overlapped.c 
	$(CC) $(CFLAGS) -c src/setup-yunofile-overlapped.c -o compiled/setup-yunofile-overlapped.o

compiled/seek-yunofile.o: src/seek-yunofile.c 
	$(CC) $(CFLAGS) -c src/seek-yunofile.c -o compiled/seek-yunofile.o

compiled/tell-yunofile.o: src/tell-yunofile.c 
	$(CC) $(CFLAGS) -c src/tell-yunofile.c -o compiled/tell-yunofile.o

compiled/request-read-yunofile.o: src/request-read-yunofile.c 
	$(CC) $(CFLAGS) -c src/request-read-yunofile.c -o compiled/request-read-yunofile.o

compiled/request-write-yunofile.o: src/request-write-yunofile.c 
	$(CC) $(CFLAGS) -c src/request-write-yunofile.c -o compiled/request-write-yunofile.o

compiled/wait-read-yunofile.o: src/wait-read-yunofile.c 
	$(CC) $(CFLAGS) -c src/wait-read-yunofile.c -o compiled/wait-read-yunofile.o

compiled/wait-write-yunofile.o: src/wait-write-yunofile.c 
	$(CC) $(CFLAGS) -c src/wait-write-yunofile.c -o compiled/wait-write-yunofile.o

compiled/read-yunofile.o: src/read-yunofile.c 
	$(CC) $(CFLAGS) -c src/read-yunofile.c -o compiled/read-yunofile.o

compiled/write-yunofile.o: src/write-yunofile.c 
	$(CC) $(CFLAGS) -c src/write-yunofile.c -o compiled/write-yunofile.o

compiled/yunofile-readablep.o: src/yunofile-readablep.c 
	$(CC) $(CFLAGS) -c src/yunofile-readablep.c -o compiled/yunofile-readablep.o

compiled/yunofile-writablep.o: src/yunofile-writablep.c 
	$(CC) $(CFLAGS) -c src/yunofile-writablep.c -o compiled/yunofile-writablep.o

compiled/yunofile-closedp.o: src/yunofile-closedp.c 
	$(CC) $(CFLAGS) -c src/yunofile-closedp.c -o compiled/yunofile-closedp.o

compiled/yunofile-buffer-array.o: src/yunofile-buffer-array.c 
	$(CC) $(CFLAGS) -c src/yunofile-buffer-array.c -o compiled/yunofile-buffer-array.o

compiled/yunofile-buffer-size.o: src/yunofile-buffer-size.c 
	$(CC) $(CFLAGS) -c src/yunofile-buffer-size.c -o compiled/yunofile-buffer-size.o

compiled/yunofile-syncp.o: src/yunofile-syncp.c 
	$(CC) $(CFLAGS) -c src/yunofile-syncp.c -o compiled/yunofile-syncp.o

compiled/yunofile-asyncp.o: src/yunofile-asyncp.c 
	$(CC) $(CFLAGS) -c src/yunofile-asyncp.c -o compiled/yunofile-asyncp.o
