
.PHONY: clean
clean: 
	rm -f compiled/test-yunopipe.o
	rm -f compiled/test-yunopipe1.o
	rm -f compiled/test-yunopipe2.o
	rm -f yunopipe.lib 

.PHONY: lib
lib: 
	make yunopipe.lib 

yunopipe.lib: compiled/test-yunopipe.o compiled/test-yunopipe1.o compiled/test-yunopipe2.o
	ar r yunopipe.lib compiled/test-yunopipe.o compiled/test-yunopipe1.o compiled/test-yunopipe2.o

compiled/test-yunopipe.o: src/test-yunopipe.c 
	gcc $(CFLAGS) -c src/test-yunopipe.c -o compiled/test-yunopipe.o

compiled/test-yunopipe1.o: src/test-yunopipe1.c 
	gcc $(CFLAGS) -c src/test-yunopipe1.c -o compiled/test-yunopipe1.o

compiled/test-yunopipe2.o: src/test-yunopipe2.c 
	gcc $(CFLAGS) -c src/test-yunopipe2.c -o compiled/test-yunopipe2.o
