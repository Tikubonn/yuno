
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno

ifeq ($(target), windows)
executefile=yunobitarray.exe
else
ifeq ($(target), linux)
executefile=yunobitarray
else
endif
endif

test: .always
	make $(executefile)
	gdb $(executefile) --batch --eval-command=run --quiet

clean: .always
	rm -f compiled/main.o 
	rm -f compiled/test-set-get-yunobitarray.o
	rm -f compiled/test-fill-yunobitarray.o
	rm -f compiled/test-yunobitarray-length.o
	rm -f compiled/test-empty-yunobitarrayp.o

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

compiled/test-set-get-yunobitarray.o: src/test-set-get-yunobitarray.c $(yunolib)
	gcc $(CFLAGS) -c src/test-set-get-yunobitarray.c -o compiled/test-set-get-yunobitarray.o

compiled/test-fill-yunobitarray.o: src/test-fill-yunobitarray.c $(yunolib)
	gcc $(CFLAGS) -c src/test-fill-yunobitarray.c -o compiled/test-fill-yunobitarray.o

compiled/test-yunobitarray-length.o: src/test-yunobitarray-length.c $(yunolib)
	gcc $(CFLAGS) -c src/test-yunobitarray-length.c -o compiled/test-yunobitarray-length.o

compiled/test-empty-yunobitarrayp.o: src/test-empty-yunobitarrayp.c $(yunolib)
	gcc $(CFLAGS) -c src/test-empty-yunobitarrayp.c -o compiled/test-empty-yunobitarrayp.o

$(executefile): compiled/main.o compiled/test-set-get-yunobitarray.o compiled/test-fill-yunobitarray.o compiled/test-yunobitarray-length.o compiled/test-empty-yunobitarrayp.o $(yunolib)
	gcc $(CFLAGS) compiled/main.o compiled/test-set-get-yunobitarray.o compiled/test-fill-yunobitarray.o compiled/test-yunobitarray-length.o compiled/test-empty-yunobitarrayp.o -o $(executefile)

.always:
