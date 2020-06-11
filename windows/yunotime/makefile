
.PHONY: clean
clean:
	rm -f compiled/yunotime.o 
	rm -f compiled/yunosleep.o
	rm -f yunotime.h
	rm -f yunotime.lib

.PHONY: h
h:
	make yunotime.h 

.PHONY: lib
lib:
	make yunotime.lib

yunotime.h: src/yunotime.h src/yunosleep.h
	cat src/yunotime.h src/yunosleep.h > yunotime.h

yunotime.lib: compiled/yunotime.o compiled/yunosleep.o
	ar r yunotime.lib compiled/yunotime.o compiled/yunosleep.o

compiled/yunotime.o: src/yunotime.c 
	gcc $(CFLAGS) -c src/yunotime.c -o compiled/yunotime.o 

compiled/yunosleep.o: src/yunosleep.c 
	gcc $(CFLAGS) -c src/yunosleep.c -o compiled/yunosleep.o
