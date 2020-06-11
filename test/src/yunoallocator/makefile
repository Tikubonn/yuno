
.PHONY: clean
clean:
	rm -f compiled/test-yunoallocator.o
	rm -f compiled/test-yunoallocator1.o
	rm -f compiled/test-yunoallocator2.o
	rm -f yunoallocator.lib 

.PHONY: lib
lib:
	make yunoallocator.lib 

yunoallocator.lib: compiled/test-yunoallocator.o compiled/test-yunoallocator1.o compiled/test-yunoallocator2.o
	ar r yunoallocator.lib compiled/test-yunoallocator.o compiled/test-yunoallocator1.o compiled/test-yunoallocator2.o

compiled/test-yunoallocator.o: src/test-yunoallocator.c 
	gcc $(CFLAGS) -c src/test-yunoallocator.c -o compiled/test-yunoallocator.o

compiled/test-yunoallocator1.o: src/test-yunoallocator1.c 
	gcc $(CFLAGS) -c src/test-yunoallocator1.c -o compiled/test-yunoallocator1.o

compiled/test-yunoallocator2.o: src/test-yunoallocator2.c 
	gcc $(CFLAGS) -c src/test-yunoallocator2.c -o compiled/test-yunoallocator2.o
