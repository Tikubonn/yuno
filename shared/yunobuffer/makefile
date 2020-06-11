
.PHONY: clean
clean:
	rm -f compiled/init-yunobuffer.o
	rm -f compiled/clear-yunobuffer.o
	rm -f compiled/read-yunobuffer.o
	rm -f compiled/write-yunobuffer.o
	rm -f compiled/seek-yunobuffer.o
	rm -f compiled/tell-yunobuffer.o
	rm -f compiled/yunobuffer-array.o
	rm -f compiled/yunobuffer-size.o
	rm -f compiled/set-yunobuffer-end.o
	rm -f yunobuffer.h
	rm -f yunobuffer.lib

.PHONY: h
h:
	make yunobuffer.h 

.PHONY: lib
lib:
	make yunobuffer.lib

yunobuffer.h: yunobuffer.p src/init-yunobuffer.h src/clear-yunobuffer.h src/read-yunobuffer.h src/write-yunobuffer.h src/seek-yunobuffer.h src/tell-yunobuffer.h src/yunobuffer-array.h src/yunobuffer-size.h src/set-yunobuffer-end.h
	cat yunobuffer.p src/init-yunobuffer.h src/clear-yunobuffer.h src/read-yunobuffer.h src/write-yunobuffer.h src/seek-yunobuffer.h src/tell-yunobuffer.h src/yunobuffer-array.h src/yunobuffer-size.h src/set-yunobuffer-end.h > yunobuffer.h

yunobuffer.lib: compiled/init-yunobuffer.o compiled/clear-yunobuffer.o compiled/read-yunobuffer.o compiled/write-yunobuffer.o compiled/seek-yunobuffer.o compiled/tell-yunobuffer.o compiled/yunobuffer-array.o compiled/yunobuffer-size.o compiled/set-yunobuffer-end.o
	ar r yunobuffer.lib compiled/init-yunobuffer.o compiled/clear-yunobuffer.o compiled/read-yunobuffer.o compiled/write-yunobuffer.o compiled/seek-yunobuffer.o compiled/tell-yunobuffer.o compiled/yunobuffer-array.o compiled/yunobuffer-size.o compiled/set-yunobuffer-end.o

compiled/init-yunobuffer.o: src/init-yunobuffer.c 
	gcc $(CFLAGS) -c src/init-yunobuffer.c -o compiled/init-yunobuffer.o

compiled/clear-yunobuffer.o: src/clear-yunobuffer.c 
	gcc $(CFLAGS) -c src/clear-yunobuffer.c -o compiled/clear-yunobuffer.o

compiled/read-yunobuffer.o: src/read-yunobuffer.c 
	gcc $(CFLAGS) -c src/read-yunobuffer.c -o compiled/read-yunobuffer.o

compiled/write-yunobuffer.o: src/write-yunobuffer.c 
	gcc $(CFLAGS) -c src/write-yunobuffer.c -o compiled/write-yunobuffer.o

compiled/seek-yunobuffer.o: src/seek-yunobuffer.c 
	gcc $(CFLAGS) -c src/seek-yunobuffer.c -o compiled/seek-yunobuffer.o

compiled/tell-yunobuffer.o: src/tell-yunobuffer.c 
	gcc $(CFLAGS) -c src/tell-yunobuffer.c -o compiled/tell-yunobuffer.o

compiled/yunobuffer-array.o: src/yunobuffer-array.c 
	gcc $(CFLAGS) -c src/yunobuffer-array.c -o compiled/yunobuffer-array.o

compiled/yunobuffer-size.o: src/yunobuffer-size.c 
	gcc $(CFLAGS) -c src/yunobuffer-size.c -o compiled/yunobuffer-size.o

compiled/set-yunobuffer-end.o: src/set-yunobuffer-end.c 
	gcc $(CFLAGS) -c src/set-yunobuffer-end.c -o compiled/set-yunobuffer-end.o
