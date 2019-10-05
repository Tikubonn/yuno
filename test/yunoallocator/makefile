
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno
export LD_LIBRARY_PATH += $(CURDIR)

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

$(YUNODLL): $(rootdir)/dist/$(YUNODLL)
	cp $(rootdir)/dist/$(YUNODLL) $(YUNODLL)

compiled/main.o: src/main.c $(YUNODLL)
	gcc $(CFLAGS) -c src/main.c -o compiled/main.o

compiled/test-calculate-yunoallocator-size.o: src/test-calculate-yunoallocator-size.c $(YUNODLL) 
	gcc $(CFLAGS) -c src/test-calculate-yunoallocator-size.c -o compiled/test-calculate-yunoallocator-size.o

compiled/test-calculate-yunoallocator-size-by-request.o: src/test-calculate-yunoallocator-size-by-request.c $(YUNODLL) 
	gcc $(CFLAGS) -c src/test-calculate-yunoallocator-size-by-request.c -o compiled/test-calculate-yunoallocator-size-by-request.o

compiled/test-allocate-yunoallocator.o: src/test-allocate-yunoallocator.c $(YUNODLL) 
	gcc $(CFLAGS) -c src/test-allocate-yunoallocator.c -o compiled/test-allocate-yunoallocator.o

compiled/test-free-yunoallocatorp.o: src/test-free-yunoallocatorp.c $(YUNODLL) 
	gcc $(CFLAGS) -c src/test-free-yunoallocatorp.c -o compiled/test-free-yunoallocatorp.o

compiled/test-yunoallocator-allocated-addressp.o: src/test-yunoallocator-allocated-addressp.c $(YUNODLL) 
	gcc $(CFLAGS) -c src/test-yunoallocator-allocated-addressp.c -o compiled/test-yunoallocator-allocated-addressp.o

$(executefile): compiled/main.o compiled/test-calculate-yunoallocator-size.o compiled/test-calculate-yunoallocator-size-by-request.o compiled/test-allocate-yunoallocator.o compiled/test-free-yunoallocatorp.o compiled/test-yunoallocator-allocated-addressp.o $(YUNODLL)
	gcc $(CFLAGS) compiled/main.o compiled/test-calculate-yunoallocator-size.o compiled/test-calculate-yunoallocator-size-by-request.o compiled/test-allocate-yunoallocator.o compiled/test-free-yunoallocatorp.o compiled/test-yunoallocator-allocated-addressp.o -o $(executefile)

.always:
