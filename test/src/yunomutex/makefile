
.PHONY: clean
clean:
	rm -f compiled/test-yunomutex.o
	rm -f compiled/test-yunomutex1.o
	rm -f compiled/test-yunomutex2.o
	rm -f yunomutex.lib

.PHONY: lib 
lib:
	make yunomutex.lib 

yunomutex.lib: compiled/test-yunomutex.o compiled/test-yunomutex1.o compiled/test-yunomutex2.o
	ar r yunomutex.lib compiled/test-yunomutex.o compiled/test-yunomutex1.o compiled/test-yunomutex2.o

compiled/test-yunomutex.o: src/test-yunomutex.c 
	gcc $(CFLAGS) -c src/test-yunomutex.c -o compiled/test-yunomutex.o

compiled/test-yunomutex1.o: src/test-yunomutex1.c 
	gcc $(CFLAGS) -c src/test-yunomutex1.c -o compiled/test-yunomutex1.o

compiled/test-yunomutex2.o: src/test-yunomutex2.c 
	gcc $(CFLAGS) -c src/test-yunomutex2.c -o compiled/test-yunomutex2.o
