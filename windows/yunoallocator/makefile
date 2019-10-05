
.always:

clean: .always
	rm -f yunoallocator.private
	rm -f yunoallocator.public
	rm -f yunoallocator.lib
	rm -f compiled/calculate-yunoallocator-size.o
	rm -f compiled/calculate-yunoallocator-size-by-request.o
	rm -f compiled/init-yunoallocator.o
	rm -f compiled/find-yunoallocator-free-space.o
	rm -f compiled/allocate-yunoallocator.o
	rm -f compiled/free-yunoallocator.o
	rm -f compiled/yunoallocator-allocated-addressp.o
	rm -f compiled/free-yunoallocatorp.o

yunoallocator.private: yunoallocator.p src/calculate-yunoallocator-size.h src/calculate-yunoallocator-size-by-request.h src/init-yunoallocator.h src/find-yunoallocator-free-space.h src/allocate-yunoallocator.h src/free-yunoallocator.h src/yunoallocator-allocated-addressp.h src/free-yunoallocatorp.h
	cat yunoallocator.p src/calculate-yunoallocator-size.h src/calculate-yunoallocator-size-by-request.h src/init-yunoallocator.h src/find-yunoallocator-free-space.h src/allocate-yunoallocator.h src/free-yunoallocator.h src/yunoallocator-allocated-addressp.h src/free-yunoallocatorp.h > yunoallocator.private

yunoallocator.public: yunoallocator.p
	cp yunoallocator.p yunoallocator.public

yunoallocator.lib: compiled/calculate-yunoallocator-size.o compiled/calculate-yunoallocator-size-by-request.o compiled/init-yunoallocator.o compiled/find-yunoallocator-free-space.o compiled/allocate-yunoallocator.o compiled/free-yunoallocator.o compiled/yunoallocator-allocated-addressp.o compiled/free-yunoallocatorp.o
	ar r yunoallocator.lib compiled/calculate-yunoallocator-size.o compiled/calculate-yunoallocator-size-by-request.o compiled/init-yunoallocator.o compiled/find-yunoallocator-free-space.o compiled/allocate-yunoallocator.o compiled/free-yunoallocator.o compiled/yunoallocator-allocated-addressp.o compiled/free-yunoallocatorp.o

compiled/calculate-yunoallocator-size.o: src/calculate-yunoallocator-size.c 
	gcc $(CFLAGS) -c src/calculate-yunoallocator-size.c -o compiled/calculate-yunoallocator-size.o

compiled/calculate-yunoallocator-size-by-request.o: src/calculate-yunoallocator-size-by-request.c 
	gcc $(CFLAGS) -c src/calculate-yunoallocator-size-by-request.c -o compiled/calculate-yunoallocator-size-by-request.o

compiled/init-yunoallocator.o: src/init-yunoallocator.c 
	gcc $(CFLAGS) -c src/init-yunoallocator.c -o compiled/init-yunoallocator.o

compiled/find-yunoallocator-free-space.o: src/find-yunoallocator-free-space.c 
	gcc $(CFLAGS) -c src/find-yunoallocator-free-space.c -o compiled/find-yunoallocator-free-space.o

compiled/allocate-yunoallocator.o: src/allocate-yunoallocator.c 
	gcc $(CFLAGS) -c src/allocate-yunoallocator.c -o compiled/allocate-yunoallocator.o

compiled/free-yunoallocator.o: src/free-yunoallocator.c 
	gcc $(CFLAGS) -c src/free-yunoallocator.c -o compiled/free-yunoallocator.o

compiled/yunoallocator-allocated-addressp.o: src/yunoallocator-allocated-addressp.c 
	gcc $(CFLAGS) -c src/yunoallocator-allocated-addressp.c -o compiled/yunoallocator-allocated-addressp.o

compiled/free-yunoallocatorp.o: src/free-yunoallocatorp.c 
	gcc $(CFLAGS) -c src/free-yunoallocatorp.c -o compiled/free-yunoallocatorp.o
