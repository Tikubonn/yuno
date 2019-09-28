
.always:

clean:
	rm -f yunopipe.lib
	rm -f yunopipe.private
	rm -f yunopipe.public
	rm -f compiled/make-yunopipe-manually.o
	rm -f compiled/make-yunopipe.o

yunopipe.private: yunopipe.p
	cp yunopipe.p yunopipe.private

yunopipe.public: yunopipe.p
	cp yunopipe.p yunopipe.public

yunopipe.lib: compiled/make-yunopipe-manually.o compiled/make-yunopipe.o
	ar r yunopipe.lib compiled/make-yunopipe-manually.o compiled/make-yunopipe.o

compiled/make-yunopipe-manually.o: src/make-yunopipe-manually.c
	gcc $(CFLAGS) -c src/make-yunopipe-manually.c -o compiled/make-yunopipe-manually.o

compiled/make-yunopipe.o: src/make-yunopipe.c
	gcc $(CFLAGS) -c src/make-yunopipe.c -o compiled/make-yunopipe.o
