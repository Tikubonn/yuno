
.always:

clean: .always
	rm -f yunopipe.lib
	rm -f compiled/test-yunopipe.o
	rm -f compiled/test-make-yunopipe.o
	rm -f compiled/test-make-yunopipe2.o

yunopipe.lib: compiled/test-yunopipe.o compiled/test-make-yunopipe.o compiled/test-make-yunopipe2.o
	ar r yunopipe.lib compiled/test-yunopipe.o compiled/test-make-yunopipe.o compiled/test-make-yunopipe2.o

compiled/test-yunopipe.o: src/test-yunopipe.c
	gcc $(CFLAGS) -c src/test-yunopipe.c -o compiled/test-yunopipe.o

compiled/test-make-yunopipe.o: src/test-make-yunopipe.c
	gcc $(CFLAGS) -c src/test-make-yunopipe.c -o compiled/test-make-yunopipe.o

compiled/test-make-yunopipe2.o: src/test-make-yunopipe2.c
	gcc $(CFLAGS) -c src/test-make-yunopipe2.c -o compiled/test-make-yunopipe2.o
