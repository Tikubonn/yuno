
.PHONY: clean
clean:
	rm -f compiled/thread-yunoerror.o
	rm -f compiled/set-yunoerror.o
	rm -f compiled/reset-yunoerror.o
	rm -f compiled/get-yunoerror.o
	rm -f yunoerror.h
	rm -f yunoerror.lib

.PHONY: h
h:
	make yunoerror.h

.PHONY: lib
lib:
	make yunoerror.lib

yunoerror.h: src/thread-yunoerror.h src/set-yunoerror.h src/reset-yunoerror.h src/get-yunoerror.h
	cat src/thread-yunoerror.h src/set-yunoerror.h src/reset-yunoerror.h src/get-yunoerror.h > yunoerror.h 

yunoerror.lib: compiled/thread-yunoerror.o compiled/set-yunoerror.o compiled/reset-yunoerror.o compiled/get-yunoerror.o
	ar r yunoerror.lib compiled/thread-yunoerror.o compiled/set-yunoerror.o compiled/reset-yunoerror.o compiled/get-yunoerror.o

compiled/thread-yunoerror.o: src/thread-yunoerror.c 
	gcc $(CFLAGS) -c src/thread-yunoerror.c -o compiled/thread-yunoerror.o

compiled/set-yunoerror.o: src/set-yunoerror.c 
	gcc $(CFLAGS) -c src/set-yunoerror.c -o compiled/set-yunoerror.o

compiled/reset-yunoerror.o: src/reset-yunoerror.c 
	gcc $(CFLAGS) -c src/reset-yunoerror.c -o compiled/reset-yunoerror.o

compiled/get-yunoerror.o: src/get-yunoerror.c 
	gcc $(CFLAGS) -c src/get-yunoerror.c -o compiled/get-yunoerror.o
