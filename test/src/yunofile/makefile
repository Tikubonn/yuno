
.PHONY: clean
clean:
	rm -f compiled/test-yunofile.o
	rm -f compiled/test-yunofile1.o
	rm -f compiled/test-yunofile2.o
	rm -f compiled/test-yunofile3.o
	rm -f compiled/test-seek-yunofile1.o
	rm -f compiled/test-yunofile4.o
	rm -f yunofile.lib

.PHONY: lib
lib:
	make yunofile.lib 

yunofile.lib: compiled/test-yunofile.o compiled/test-yunofile1.o compiled/test-yunofile2.o compiled/test-yunofile3.o compiled/test-seek-yunofile1.o compiled/test-yunofile4.o
	ar r yunofile.lib compiled/test-yunofile.o compiled/test-yunofile1.o compiled/test-yunofile2.o compiled/test-yunofile3.o compiled/test-seek-yunofile1.o compiled/test-yunofile4.o

compiled/test-yunofile.o: src/test-yunofile.c 
	gcc $(CFLAGS) -c src/test-yunofile.c -o compiled/test-yunofile.o

compiled/test-yunofile1.o: src/test-yunofile1.c 
	gcc $(CFLAGS) -c src/test-yunofile1.c -o compiled/test-yunofile1.o

compiled/test-yunofile2.o: src/test-yunofile2.c 
	gcc $(CFLAGS) -c src/test-yunofile2.c -o compiled/test-yunofile2.o

compiled/test-yunofile3.o: src/test-yunofile3.c 
	gcc $(CFLAGS) -c src/test-yunofile3.c -o compiled/test-yunofile3.o

compiled/test-seek-yunofile1.o: src/test-seek-yunofile1.c 
	gcc $(CFLAGS) -c src/test-seek-yunofile1.c -o compiled/test-seek-yunofile1.o

compiled/test-yunofile4.o: src/test-yunofile4.c 
	gcc $(CFLAGS) -c src/test-yunofile4.c -o compiled/test-yunofile4.o
