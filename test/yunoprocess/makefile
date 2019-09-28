
all:
	make yunoprocess.lib

clean:
	rm -f yunoprocess.lib
	rm -f compiled/test-yunoprocess.o
	rm -f compiled/test-make-yunoprocess.o
	rm -f compiled/test-make-yunoprocess2.o

yunoprocess.lib: compiled/test-yunoprocess.o compiled/test-make-yunoprocess.o compiled/test-make-yunoprocess2.o
	ar r yunoprocess.lib compiled/test-yunoprocess.o compiled/test-make-yunoprocess.o compiled/test-make-yunoprocess2.o

compiled/test-yunoprocess.o: src/test-yunoprocess.c 
	gcc $(CFLAGS) -c src/test-yunoprocess.c -o compiled/test-yunoprocess.o

compiled/test-make-yunoprocess.o: src/test-make-yunoprocess.c 
	gcc $(CFLAGS) -c src/test-make-yunoprocess.c -o compiled/test-make-yunoprocess.o

compiled/test-make-yunoprocess2.o: src/test-make-yunoprocess2.c 
	gcc $(CFLAGS) -c src/test-make-yunoprocess2.c -o compiled/test-make-yunoprocess2.o
