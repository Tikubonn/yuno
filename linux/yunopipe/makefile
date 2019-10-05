
.always:

clean: .always
	rm -f yunopipe.lib
	rm -f yunopipe.private
	rm -f yunopipe.public
	rm -f compiled/make-yunopipe-manually.o
	rm -f compiled/make-yunopipe.o

yunopipe.private: yunopipe.p
	cat yunopipe.p > yunopipe.private

yunopipe.public: yunopipe.p
	cat yunopipe.p > yunopipe.public

yunopipe.a: compiled/make-yunopipe-manually.o compiled/make-yunopipe.o
	ar r yunopipe.a compiled/make-yunopipe-manually.o compiled/make-yunopipe.o

compiled/make-yunopipe.o: src/make-yunopipe.c
	gcc $(CFLAGS) -c src/make-yunopipe.c -o compiled/make-yunopipe.o

compiled/make-yunopipe-manually.o: src/make-yunopipe-manually.c
	gcc $(CFLAGS) -c src/make-yunopipe-manually.c -o compiled/make-yunopipe-manually.o

