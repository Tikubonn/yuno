
all:
	make yunofile.lib

clean:
	rm -f yunofile.lib
	rm -f compiled/test-yunofile.o
	rm -f compiled/test-open-yunofile.o
	rm -f compiled/test-open-async-yunofile.o
	rm -f compiled/test-open-async-yunofile2.o

yunofile.lib: compiled/test-yunofile.o compiled/test-open-yunofile.o compiled/test-open-async-yunofile.o compiled/test-open-async-yunofile2.o
	ar r yunofile.lib compiled/test-yunofile.o compiled/test-open-yunofile.o compiled/test-open-async-yunofile.o compiled/test-open-async-yunofile2.o

compiled/test-yunofile.o: src/test-yunofile.c 
	gcc $(CFLAGS) -c src/test-yunofile.c -o compiled/test-yunofile.o

compiled/test-open-yunofile.o: src/test-open-yunofile.c 
	gcc $(CFLAGS) -c src/test-open-yunofile.c -o compiled/test-open-yunofile.o

compiled/test-open-async-yunofile.o: src/test-open-async-yunofile.c 
	gcc $(CFLAGS) -c src/test-open-async-yunofile.c -o compiled/test-open-async-yunofile.o

compiled/test-open-async-yunofile2.o: src/test-open-async-yunofile2.c 
	gcc $(CFLAGS) -c src/test-open-async-yunofile2.c -o compiled/test-open-async-yunofile2.o
