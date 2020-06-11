
.PHONY: clean
clean:
	rm -f compiled/new-yunofile.o
	rm -f compiled/new-yunomutex.o
	rm -f compiled/new-yunopipe.o
	rm -f compiled/new-yunoprocess.o
	rm -f compiled/new-yunosemaphore.o
	rm -f compiled/new-yunothread.o
	rm -f compiled/free-yunofile.o
	rm -f compiled/free-yunomutex.o
	rm -f compiled/free-yunoprocess.o
	rm -f compiled/free-yunosemaphore.o
	rm -f compiled/free-yunothread.o
	rm -f compiled/new-yunostandard-input.o
	rm -f compiled/new-yunostandard-output.o
	rm -f compiled/new-yunostandard-error.o
	rm -f utility.h
	rm -f utility.lib

.PHONY: h
h:
	make utility.h 

.PHONY: lib
lib:
	make utility.lib 

utility.h: src/new-yunofile.h src/new-yunomutex.h src/new-yunopipe.h src/new-yunoprocess.h src/new-yunosemaphore.h src/new-yunothread.h src/free-yunofile.h src/free-yunomutex.h src/free-yunoprocess.h src/free-yunosemaphore.h src/free-yunothread.h src/new-yunostandard-input.h src/new-yunostandard-output.h src/new-yunostandard-error.h
	cat src/new-yunofile.h src/new-yunomutex.h src/new-yunopipe.h src/new-yunoprocess.h src/new-yunosemaphore.h src/new-yunothread.h src/free-yunofile.h src/free-yunomutex.h src/free-yunoprocess.h src/free-yunosemaphore.h src/free-yunothread.h src/new-yunostandard-input.h src/new-yunostandard-output.h src/new-yunostandard-error.h > utility.h 

utility.lib: compiled/new-yunofile.o compiled/new-yunomutex.o compiled/new-yunopipe.o compiled/new-yunoprocess.o compiled/new-yunosemaphore.o compiled/new-yunothread.o compiled/free-yunofile.o compiled/free-yunomutex.o compiled/free-yunoprocess.o compiled/free-yunosemaphore.o compiled/free-yunothread.o compiled/new-yunostandard-input.o compiled/new-yunostandard-output.o compiled/new-yunostandard-error.o   
	ar r utility.lib compiled/new-yunofile.o compiled/new-yunomutex.o compiled/new-yunopipe.o compiled/new-yunoprocess.o compiled/new-yunosemaphore.o compiled/new-yunothread.o compiled/free-yunofile.o compiled/free-yunomutex.o compiled/free-yunoprocess.o compiled/free-yunosemaphore.o compiled/free-yunothread.o compiled/new-yunostandard-input.o compiled/new-yunostandard-output.o compiled/new-yunostandard-error.o   

compiled/new-yunofile.o: src/new-yunofile.c 
	gcc $(CFLAGS) -c src/new-yunofile.c -o compiled/new-yunofile.o

compiled/new-yunomutex.o: src/new-yunomutex.c 
	gcc $(CFLAGS) -c src/new-yunomutex.c -o compiled/new-yunomutex.o

compiled/new-yunopipe.o: src/new-yunopipe.c 
	gcc $(CFLAGS) -c src/new-yunopipe.c -o compiled/new-yunopipe.o

compiled/new-yunoprocess.o: src/new-yunoprocess.c 
	gcc $(CFLAGS) -c src/new-yunoprocess.c -o compiled/new-yunoprocess.o

compiled/new-yunosemaphore.o: src/new-yunosemaphore.c 
	gcc $(CFLAGS) -c src/new-yunosemaphore.c -o compiled/new-yunosemaphore.o

compiled/new-yunothread.o: src/new-yunothread.c 
	gcc $(CFLAGS) -c src/new-yunothread.c -o compiled/new-yunothread.o

compiled/free-yunofile.o: src/free-yunofile.c 
	gcc $(CFLAGS) -c src/free-yunofile.c -o compiled/free-yunofile.o

compiled/free-yunomutex.o: src/free-yunomutex.c 
	gcc $(CFLAGS) -c src/free-yunomutex.c -o compiled/free-yunomutex.o

compiled/free-yunoprocess.o: src/free-yunoprocess.c 
	gcc $(CFLAGS) -c src/free-yunoprocess.c -o compiled/free-yunoprocess.o

compiled/free-yunosemaphore.o: src/free-yunosemaphore.c 
	gcc $(CFLAGS) -c src/free-yunosemaphore.c -o compiled/free-yunosemaphore.o

compiled/free-yunothread.o: src/free-yunothread.c 
	gcc $(CFLAGS) -c src/free-yunothread.c -o compiled/free-yunothread.o

compiled/new-yunostandard-input.o: src/new-yunostandard-input.c 
	gcc $(CFLAGS) -c src/new-yunostandard-input.c -o compiled/new-yunostandard-input.o

compiled/new-yunostandard-output.o: src/new-yunostandard-output.c 
	gcc $(CFLAGS) -c src/new-yunostandard-output.c -o compiled/new-yunostandard-output.o

compiled/new-yunostandard-error.o: src/new-yunostandard-error.c 
	gcc $(CFLAGS) -c src/new-yunostandard-error.c -o compiled/new-yunostandard-error.o
