
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno

ifeq ($(target), windows)
executefile=yunoallocator.exe
else
ifeq ($(target), linux)
executefile=yunoallocator
else
endif
endif

test: .always
	make $(executefile)
	gdb $(executefile) --batch --eval-command=run --quiet

clean: .always
	rm -f compiled/main.o 
	rm -f compiled/test-calculate-yunoallocator-size.o
	rm -f compiled/test-calculate-yunoallocator-size-by-request.o
	rm -f compiled/test-allocate-yunoallocator.o
	rm -f compiled/test-free-yunoallocatorp.o
	rm -f compiled/test-yunoallocator-allocated-addressp.o

ifeq ($(target), windows)
yunolib=yuno.dll
else
ifeq ($(target), linux)
yunolib=yuno.so
else
endif
endif

$(yunolib): $(rootdir)/dist/$(yunolib)
	cp $(rootdir)/dist/$(yunolib) $(yunolib)

compiled/main.o: src/main.c $(yunolib)
	gcc $(CFLAGS) -c src/main.c -o compiled/main.o

compiled/test-calculate-yunoallocator-size.o: src/test-calculate-yunoallocator-size.c $(yunolib) 
	gcc $(CFLAGS) -c src/test-calculate-yunoallocator-size.c -o compiled/test-calculate-yunoallocator-size.o

compiled/test-calculate-yunoallocator-size-by-request.o: src/test-calculate-yunoallocator-size-by-request.c $(yunolib) 
	gcc $(CFLAGS) -c src/test-calculate-yunoallocator-size-by-request.c -o compiled/test-calculate-yunoallocator-size-by-request.o

compiled/test-allocate-yunoallocator.o: src/test-allocate-yunoallocator.c $(yunolib) 
	gcc $(CFLAGS) -c src/test-allocate-yunoallocator.c -o compiled/test-allocate-yunoallocator.o

compiled/test-free-yunoallocatorp.o: src/test-free-yunoallocatorp.c $(yunolib) 
	gcc $(CFLAGS) -c src/test-free-yunoallocatorp.c -o compiled/test-free-yunoallocatorp.o

compiled/test-yunoallocator-allocated-addressp.o: src/test-yunoallocator-allocated-addressp.c $(yunolib) 
	gcc $(CFLAGS) -c src/test-yunoallocator-allocated-addressp.c -o compiled/test-yunoallocator-allocated-addressp.o

$(executefile): compiled/main.o compiled/test-calculate-yunoallocator-size.o compiled/test-calculate-yunoallocator-size-by-request.o compiled/test-allocate-yunoallocator.o compiled/test-free-yunoallocatorp.o compiled/test-yunoallocator-allocated-addressp.o
	gcc $(CFLAGS) compiled/main.o compiled/test-calculate-yunoallocator-size.o compiled/test-calculate-yunoallocator-size-by-request.o compiled/test-allocate-yunoallocator.o compiled/test-free-yunoallocatorp.o compiled/test-yunoallocator-allocated-addressp.o -o $(executefile)

.always:
