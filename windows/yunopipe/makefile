
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

yunopipe.h: yunopipe.p src/make-yunopipe.h src/setup-yunopipe.h
	cat yunopipe.p src/make-yunopipe.h src/setup-yunopipe.h > yunopipe.h

yunopipe.lib: compiled/make-yunopipe.o
	ar r yunopipe.lib compiled/make-yunopipe.o

compiled/make-yunopipe.o: src/make-yunopipe.c
	gcc $(CFLAGS) -c src/make-yunopipe.c -o compiled/make-yunopipe.o
