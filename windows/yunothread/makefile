
.PHONY: clean
clean:
	rm -f compiled/make-yunothread.o
	rm -f compiled/start-yunothread.o
	rm -f compiled/wait-yunothread.o
	rm -f compiled/close-yunothread.o
	rm -f compiled/get-yunothread-exit-code.o
	rm -f yunothread.h
	rm -f yunothread.lib

.PHONY: h
h:
	make yunothread.h 

.PHONY: lib
lib:
	make yunothread.lib

yunothread.h: yunothread.p src/make-yunothread.h src/start-yunothread.h src/wait-yunothread.h src/close-yunothread.h src/get-yunothread-exit-code.h  
	cat yunothread.p src/make-yunothread.h src/start-yunothread.h src/wait-yunothread.h src/close-yunothread.h src/get-yunothread-exit-code.h > yunothread.h 

yunothread.lib: compiled/make-yunothread.o compiled/start-yunothread.o compiled/wait-yunothread.o compiled/close-yunothread.o compiled/get-yunothread-exit-code.o  
	ar r yunothread.lib compiled/make-yunothread.o compiled/start-yunothread.o compiled/wait-yunothread.o compiled/close-yunothread.o compiled/get-yunothread-exit-code.o  

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
