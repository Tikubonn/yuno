
all:
	make yunothread.lib

clean:
	rm -f yunothread.lib
	rm -f compiled/test-yunothread.o
	rm -f compiled/test-make-yunothread.o
	rm -f compiled/test-make-yunothread2.o

yunothread.lib: compiled/test-yunothread.o compiled/test-make-yunothread.o compiled/test-make-yunothread2.o
	ar r yunothread.lib compiled/test-yunothread.o compiled/test-make-yunothread.o compiled/test-make-yunothread2.o

compiled/test-yunothread.o: src/test-yunothread.c 
	gcc $(CFLAGS) -c src/test-yunothread.c -o compiled/test-yunothread.o

compiled/test-make-yunothread.o: src/test-make-yunothread.c 
	gcc $(CFLAGS) -c src/test-make-yunothread.c -o compiled/test-make-yunothread.o

compiled/test-make-yunothread2.o: src/test-make-yunothread2.c 
	gcc $(CFLAGS) -c src/test-make-yunothread2.c -o compiled/test-make-yunothread2.o
