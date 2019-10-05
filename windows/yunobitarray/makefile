
.always:

clean: .always
	rm -f yunobitarray.private
	rm -f yunobitarray.public
	rm -f yunobitarray.lib
	rm -f compiled/init-yunobitarray.o
	rm -f compiled/get-yunobitarray.o
	rm -f compiled/set-yunobitarray.o
	rm -f compiled/fill-yunobitarray.o
	rm -f compiled/yunobitarray-length.o
	rm -f compiled/empty-yunobitarrayp.o

yunobitarray.private: yunobitarray.p src/init-yunobitarray.h src/get-yunobitarray.h src/set-yunobitarray.h src/fill-yunobitarray.h src/yunobitarray-length.h src/empty-yunobitarrayp.h
	cat yunobitarray.p src/init-yunobitarray.h src/get-yunobitarray.h src/set-yunobitarray.h src/fill-yunobitarray.h src/yunobitarray-length.h src/empty-yunobitarrayp.h > yunobitarray.private

yunobitarray.public: yunobitarray.p
	cp yunobitarray.p yunobitarray.public

yunobitarray.lib: compiled/init-yunobitarray.o compiled/get-yunobitarray.o compiled/set-yunobitarray.o compiled/fill-yunobitarray.o compiled/yunobitarray-length.o compiled/empty-yunobitarrayp.o
	ar r yunobitarray.lib compiled/init-yunobitarray.o compiled/get-yunobitarray.o compiled/set-yunobitarray.o compiled/fill-yunobitarray.o compiled/yunobitarray-length.o compiled/empty-yunobitarrayp.o

compiled/init-yunobitarray.o: src/init-yunobitarray.c 
	gcc $(CFLAGS) -c src/init-yunobitarray.c -o compiled/init-yunobitarray.o

compiled/get-yunobitarray.o: src/get-yunobitarray.c 
	gcc $(CFLAGS) -c src/get-yunobitarray.c -o compiled/get-yunobitarray.o

compiled/set-yunobitarray.o: src/set-yunobitarray.c 
	gcc $(CFLAGS) -c src/set-yunobitarray.c -o compiled/set-yunobitarray.o

compiled/fill-yunobitarray.o: src/fill-yunobitarray.c 
	gcc $(CFLAGS) -c src/fill-yunobitarray.c -o compiled/fill-yunobitarray.o

compiled/yunobitarray-length.o: src/yunobitarray-length.c 
	gcc $(CFLAGS) -c src/yunobitarray-length.c -o compiled/yunobitarray-length.o

compiled/empty-yunobitarrayp.o: src/empty-yunobitarrayp.c 
	gcc $(CFLAGS) -c src/empty-yunobitarrayp.c -o compiled/empty-yunobitarrayp.o
