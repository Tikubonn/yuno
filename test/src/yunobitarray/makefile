
.PHONY: clean
clean:
	rm -f compiled/test-yunobitarray.o
	rm -f compiled/test-yunobitarray1.o
	rm -f compiled/test-find-yunobitarray-filled-area1.o
	rm -f compiled/test-find-yunobitarray1.o
	rm -f compiled/test-fill-yunobitarray1.o
	rm -f yunobitarray.lib 

.PHONY: lib
lib:
	make yunobitarray.lib 

yunobitarray.lib: compiled/test-yunobitarray.o compiled/test-yunobitarray1.o compiled/test-find-yunobitarray-filled-area1.o compiled/test-find-yunobitarray1.o compiled/test-fill-yunobitarray1.o
	ar r yunobitarray.lib compiled/test-yunobitarray.o compiled/test-yunobitarray1.o compiled/test-find-yunobitarray-filled-area1.o compiled/test-find-yunobitarray1.o compiled/test-fill-yunobitarray1.o

compiled/test-yunobitarray.o: src/test-yunobitarray.c 
	gcc $(CFLAGS) -c src/test-yunobitarray.c -o compiled/test-yunobitarray.o

compiled/test-yunobitarray1.o: src/test-yunobitarray1.c 
	gcc $(CFLAGS) -c src/test-yunobitarray1.c -o compiled/test-yunobitarray1.o

compiled/test-find-yunobitarray-filled-area1.o: src/test-find-yunobitarray-filled-area1.c 
	gcc $(CFLAGS) -c src/test-find-yunobitarray-filled-area1.c -o compiled/test-find-yunobitarray-filled-area1.o

compiled/test-find-yunobitarray1.o: src/test-find-yunobitarray1.c 
	gcc $(CFLAGS) -c src/test-find-yunobitarray1.c -o compiled/test-find-yunobitarray1.o

compiled/test-fill-yunobitarray1.o: src/test-fill-yunobitarray1.c
	gcc $(CFLAGS) -c src/test-fill-yunobitarray1.c -o compiled/test-fill-yunobitarray1.o
