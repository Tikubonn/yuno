
.PHONY: clean
clean:
	rm -f compiled/init-yunobitarray.o
	rm -f compiled/set-yunobitarray.o
	rm -f compiled/get-yunobitarray.o
	rm -f compiled/yunobitarray-length.o
	rm -f compiled/find-yunobitarray.o
	rm -f compiled/yunobitarray-array.o
	rm -f compiled/yunobitarray-size.o
	rm -f compiled/find-yunobitarray-filled-area.o
	rm -f compiled/fill-yunobitarray.o
	rm -f yunobitarray.h
	rm -f yunobitarray.lib

.PHONY: h
h:
	make yunobitarray.h 

.PHONY: lib
lib:
	make yunobitarray.lib

yunobitarray.h: yunobitarray.p src/init-yunobitarray.h src/set-yunobitarray.h src/get-yunobitarray.h src/yunobitarray-length.h src/find-yunobitarray.h src/yunobitarray-array.h src/yunobitarray-size.h src/find-yunobitarray-filled-area.h src/fill-yunobitarray.h
	cat yunobitarray.p src/init-yunobitarray.h src/set-yunobitarray.h src/get-yunobitarray.h src/yunobitarray-length.h src/find-yunobitarray.h src/yunobitarray-array.h src/yunobitarray-size.h src/find-yunobitarray-filled-area.h src/fill-yunobitarray.h > yunobitarray.h

yunobitarray.lib: compiled/init-yunobitarray.o compiled/set-yunobitarray.o compiled/get-yunobitarray.o compiled/yunobitarray-length.o compiled/find-yunobitarray.o compiled/yunobitarray-array.o compiled/yunobitarray-size.o compiled/find-yunobitarray-filled-area.o compiled/fill-yunobitarray.o
	ar r yunobitarray.lib compiled/init-yunobitarray.o compiled/set-yunobitarray.o compiled/get-yunobitarray.o compiled/yunobitarray-length.o compiled/find-yunobitarray.o compiled/yunobitarray-array.o compiled/yunobitarray-size.o compiled/find-yunobitarray-filled-area.o compiled/fill-yunobitarray.o

compiled/init-yunobitarray.o: src/init-yunobitarray.c 
	gcc $(CFLAGS) -c src/init-yunobitarray.c -o compiled/init-yunobitarray.o

compiled/set-yunobitarray.o: src/set-yunobitarray.c 
	gcc $(CFLAGS) -c src/set-yunobitarray.c -o compiled/set-yunobitarray.o

compiled/get-yunobitarray.o: src/get-yunobitarray.c 
	gcc $(CFLAGS) -c src/get-yunobitarray.c -o compiled/get-yunobitarray.o

compiled/yunobitarray-length.o: src/yunobitarray-length.c 
	gcc $(CFLAGS) -c src/yunobitarray-length.c -o compiled/yunobitarray-length.o

compiled/find-yunobitarray.o: src/find-yunobitarray.c 
	gcc $(CFLAGS) -c src/find-yunobitarray.c -o compiled/find-yunobitarray.o

compiled/yunobitarray-array.o: src/yunobitarray-array.c 
	gcc $(CFLAGS) -c src/yunobitarray-array.c -o compiled/yunobitarray-array.o

compiled/yunobitarray-size.o: src/yunobitarray-size.c 
	gcc $(CFLAGS) -c src/yunobitarray-size.c -o compiled/yunobitarray-size.o

compiled/find-yunobitarray-filled-area.o: src/find-yunobitarray-filled-area.c 
	gcc $(CFLAGS) -c src/find-yunobitarray-filled-area.c -o compiled/find-yunobitarray-filled-area.o

compiled/fill-yunobitarray.o: src/fill-yunobitarray.c
	gcc $(CFLAGS) -c src/fill-yunobitarray.c -o compiled/fill-yunobitarray.o
