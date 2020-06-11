
.PHONY: clean
clean:
	rm -f compiled/make-yunopipe.o
	rm -f yunopipe.h
	rm -f yunopipe.lib

.PHONY: h
h:
	make yunopipe.h 

.PHONY: lib
lib:
	make yunopipe.lib 

yunopipe.h: src/make-yunopipe.h
	cat src/make-yunopipe.h > yunopipe.h 

yunopipe.lib: compiled/make-yunopipe.o
	ar r yunopipe.lib compiled/make-yunopipe.o

compiled/make-yunopipe.o: src/make-yunopipe.c
	gcc $(CFLAGS) -c src/make-yunopipe.c -o compiled/make-yunopipe.o
