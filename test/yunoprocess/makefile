
export CFLAGS += -I$(CURDIR) -L$(CURDIR) -lyuno

ifeq ($(target), windows)
executefile=yunoprocess.exe
else
ifeq ($(target), linux)
executefile=yunoprocess
else
endif
endif

test: .always
	make $(executefile)
	gdb $(executefile) --batch --eval-command=run --quiet

clean: .always
	rm -f compiled/main.o
	rm -f compiled/test-make-yunoprocess.o
	rm -f compiled/test-make-yunoprocess2.o

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

compiled/test-make-yunoprocess.o: src/test-make-yunoprocess.c $(yunolib)
	gcc $(CFLAGS) -c src/test-make-yunoprocess.c -o compiled/test-make-yunoprocess.o

compiled/test-make-yunoprocess2.o: src/test-make-yunoprocess2.c $(yunolib)
	gcc $(CFLAGS) -c src/test-make-yunoprocess2.c -o compiled/test-make-yunoprocess2.o

$(executefile): compiled/main.o compiled/test-make-yunoprocess.o compiled/test-make-yunoprocess2.o $(yunolib)
	gcc $(CFLAGS) compiled/main.o compiled/test-make-yunoprocess.o compiled/test-make-yunoprocess2.o -o $(executefile)

.always:
