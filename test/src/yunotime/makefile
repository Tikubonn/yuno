
.PHONY: clean
clean:
	rm -f compiled/test-yunotime.o
	rm -f compiled/test-yunotime1.o
	rm -f compiled/test-yunosleep1.o
	rm -f yunotime.lib

.PHONY: lib
lib:
	make yunotime.lib 

yunotime.lib: compiled/test-yunotime.o compiled/test-yunotime1.o compiled/test-yunosleep1.o
	ar r yunotime.lib compiled/test-yunotime.o compiled/test-yunotime1.o compiled/test-yunosleep1.o

compiled/test-yunotime.o: src/test-yunotime.c 
	gcc $(CFLAGS) -c src/test-yunotime.c -o compiled/test-yunotime.o

compiled/test-yunotime1.o: src/test-yunotime1.c 
	gcc $(CFLAGS) -c src/test-yunotime1.c -o compiled/test-yunotime1.o

compiled/test-yunosleep1.o: src/test-yunosleep1.c 
	gcc $(CFLAGS) -c src/test-yunosleep1.c -o compiled/test-yunosleep1.o
