
.PHONY: clean
clean:
	rm -f compiled/init-yunoallocator.o
	rm -f compiled/allocate-yunoallocator.o
	rm -f compiled/free-yunoallocator.o
	rm -f compiled/yunoallocator-managed-addressp.o
	rm -f compiled/empty-yunoallocatorp.o
	rm -f compiled/yunoallocator-bitarray.o
	rm -f compiled/yunoallocator-array.o
	rm -f compiled/yunoallocator-size.o
	rm -f yunoallocator.h
	rm -f yunoallocator.lib

.PHONY: h
h:
	make yunoallocator.h

.PHONY: lib
lib:
	make yunoallocator.lib

yunoallocator.h: yunoallocator.p src/init-yunoallocator.h src/allocate-yunoallocator.h src/free-yunoallocator.h src/yunoallocator-managed-addressp.h src/empty-yunoallocatorp.h src/yunoallocator-bitarray.h src/yunoallocator-array.h src/yunoallocator-size.h
	cat yunoallocator.p src/init-yunoallocator.h src/allocate-yunoallocator.h src/free-yunoallocator.h src/yunoallocator-managed-addressp.h src/empty-yunoallocatorp.h src/yunoallocator-bitarray.h src/yunoallocator-array.h src/yunoallocator-size.h > yunoallocator.h

yunoallocator.lib: compiled/init-yunoallocator.o compiled/allocate-yunoallocator.o compiled/free-yunoallocator.o compiled/yunoallocator-managed-addressp.o compiled/empty-yunoallocatorp.o compiled/yunoallocator-bitarray.o compiled/yunoallocator-array.o compiled/yunoallocator-size.o
	ar r yunoallocator.lib compiled/init-yunoallocator.o compiled/allocate-yunoallocator.o compiled/free-yunoallocator.o compiled/yunoallocator-managed-addressp.o compiled/empty-yunoallocatorp.o compiled/yunoallocator-bitarray.o compiled/yunoallocator-array.o compiled/yunoallocator-size.o

compiled/init-yunoallocator.o: src/init-yunoallocator.c 
	gcc $(CFLAGS) -c src/init-yunoallocator.c -o compiled/init-yunoallocator.o

compiled/allocate-yunoallocator.o: src/allocate-yunoallocator.c 
	gcc $(CFLAGS) -c src/allocate-yunoallocator.c -o compiled/allocate-yunoallocator.o

compiled/free-yunoallocator.o: src/free-yunoallocator.c 
	gcc $(CFLAGS) -c src/free-yunoallocator.c -o compiled/free-yunoallocator.o

compiled/yunoallocator-managed-addressp.o: src/yunoallocator-managed-addressp.c 
	gcc $(CFLAGS) -c src/yunoallocator-managed-addressp.c -o compiled/yunoallocator-managed-addressp.o

compiled/empty-yunoallocatorp.o: src/empty-yunoallocatorp.c
	gcc $(CFLAGS) -c src/empty-yunoallocatorp.c -o compiled/empty-yunoallocatorp.o

compiled/yunoallocator-bitarray.o: src/yunoallocator-bitarray.c
	gcc $(CFLAGS) -c src/yunoallocator-bitarray.c -o compiled/yunoallocator-bitarray.o

compiled/yunoallocator-array.o: src/yunoallocator-array.c
	gcc $(CFLAGS) -c src/yunoallocator-array.c -o compiled/yunoallocator-array.o

compiled/yunoallocator-size.o: src/yunoallocator-size.c
	gcc $(CFLAGS) -c src/yunoallocator-size.c -o compiled/yunoallocator-size.o
