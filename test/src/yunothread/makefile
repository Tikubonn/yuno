
.PHONY: clean
clean: 
	rm -f compiled/test-yunothread.o
	rm -f compiled/test-yunothread1.o
	rm -f compiled/test-yunothread2.o
	rm -f yunothread.lib 

.PHONY: lib
lib: 
	make yunothread.lib 

yunothread.lib: compiled/test-yunothread.o compiled/test-yunothread1.o compiled/test-yunothread2.o 
	ar r yunothread.lib compiled/test-yunothread.o compiled/test-yunothread1.o compiled/test-yunothread2.o 

compiled/test-yunothread.o: src/test-yunothread.c 
	gcc $(CFLAGS) -c src/test-yunothread.c -o compiled/test-yunothread.o

compiled/test-yunothread1.o: src/test-yunothread1.c 
	gcc $(CFLAGS) -c src/test-yunothread1.c -o compiled/test-yunothread1.o

compiled/test-yunothread2.o: src/test-yunothread2.c 
	gcc $(CFLAGS) -c src/test-yunothread2.c -o compiled/test-yunothread2.o
