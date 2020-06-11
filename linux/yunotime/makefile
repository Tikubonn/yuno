
.PHONY: clean
clean:
	rm -f compiled/yunosleep.o
	rm -f compiled/yunotime.o 
	rm -f yunotime.h 
	rm -f yunotime.lib 

.PHONY: h
h:
	make yunotime.h 

.PHONY: lib
lib:
	make yunotime.lib 

yunotime.h: src/yunosleep.h src/yunotime.h 
	cat src/yunosleep.h src/yunotime.h > yunotime.h 

yunotime.lib: compiled/yunosleep.o compiled/yunotime.o 
	ar r yunotime.lib compiled/yunosleep.o compiled/yunotime.o 

compiled/yunosleep.o: src/yunosleep.c 
	gcc $(CFLAGS) -c src/yunosleep.c -o compiled/yunosleep.o

compiled/yunotime.o: src/yunotime.c 
	gcc $(CFLAGS) -c src/yunotime.c -o compiled/yunotime.o 
