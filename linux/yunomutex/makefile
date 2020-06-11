
.PHONY: clean
clean:
	rm -f compiled/close-yunomutex.o
	rm -f compiled/make-yunomutex.o
	rm -f compiled/release-yunomutex.o
	rm -f compiled/wait-yunomutex.o
	rm -f yunomutex.h
	rm -f yunomutex.lib

.PHONY: h
h:
	make yunomutex.h 

.PHONY: lib
lib:
	make yunomutex.lib 

yunomutex.h: yunomutex.p src/close-yunomutex.h src/make-yunomutex.h src/release-yunomutex.h src/wait-yunomutex.h
	cat yunomutex.p src/close-yunomutex.h src/make-yunomutex.h src/release-yunomutex.h src/wait-yunomutex.h > yunomutex.h

yunomutex.lib: compiled/close-yunomutex.o compiled/make-yunomutex.o compiled/release-yunomutex.o compiled/wait-yunomutex.o
	ar r yunomutex.lib compiled/close-yunomutex.o compiled/make-yunomutex.o compiled/release-yunomutex.o compiled/wait-yunomutex.o

compiled/close-yunomutex.o: src/close-yunomutex.c 
	gcc $(CFLAGS) -c src/close-yunomutex.c -o compiled/close-yunomutex.o

compiled/make-yunomutex.o: src/make-yunomutex.c 
	gcc $(CFLAGS) -c src/make-yunomutex.c -o compiled/make-yunomutex.o

compiled/release-yunomutex.o: src/release-yunomutex.c 
	gcc $(CFLAGS) -c src/release-yunomutex.c -o compiled/release-yunomutex.o

compiled/wait-yunomutex.o: src/wait-yunomutex.c 
	gcc $(CFLAGS) -c src/wait-yunomutex.c -o compiled/wait-yunomutex.o
