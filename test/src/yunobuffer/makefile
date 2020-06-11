
.PHONY: clean
clean:
	rm -f compiled/test-yunobuffer.o
	rm -f compiled/test-yunobuffer1.o
	rm -f compiled/test-seek-yunobuffer1.o
	rm -f compiled/test-set-yunobuffer-end1.o
	rm -f compiled/test-clear-yunobuffer1.o
	rm -f yunobuffer.lib

.PHONY: lib
lib:
	make yunobuffer.lib

yunobuffer.lib: compiled/test-yunobuffer.o compiled/test-yunobuffer1.o compiled/test-seek-yunobuffer1.o compiled/test-set-yunobuffer-end1.o compiled/test-clear-yunobuffer1.o
	ar r yunobuffer.lib compiled/test-yunobuffer.o compiled/test-yunobuffer1.o compiled/test-seek-yunobuffer1.o compiled/test-set-yunobuffer-end1.o compiled/test-clear-yunobuffer1.o

compiled/test-yunobuffer.o: src/test-yunobuffer.c 
	gcc $(CFLAGS) -c src/test-yunobuffer.c -o compiled/test-yunobuffer.o

compiled/test-yunobuffer1.o: src/test-yunobuffer1.c 
	gcc $(CFLAGS) -c src/test-yunobuffer1.c -o compiled/test-yunobuffer1.o

compiled/test-seek-yunobuffer1.o: src/test-seek-yunobuffer1.c 
	gcc $(CFLAGS) -c src/test-seek-yunobuffer1.c -o compiled/test-seek-yunobuffer1.o

compiled/test-set-yunobuffer-end1.o: src/test-set-yunobuffer-end1.c 
	gcc $(CFLAGS) -c src/test-set-yunobuffer-end1.c -o compiled/test-set-yunobuffer-end1.o

compiled/test-clear-yunobuffer1.o: src/test-clear-yunobuffer1.c 
	gcc $(CFLAGS) -c src/test-clear-yunobuffer1.c -o compiled/test-clear-yunobuffer1.o
