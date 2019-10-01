
.always:

clean: .always
	rm -f yunofile-buffer.private
	rm -f yunofile-buffer.public
	rm -f compiled/default-yunofile-buffer.o
	rm -f compiled/init-yunofile-buffer.o
	rm -f compiled/map-yunofile-buffer.o
	rm -f compiled/yunofile-buffer-array.o
	rm -f compiled/yunofile-buffer-size.o
	rm -f compiled/yunofile-buffer-max-size.o

yunofile-buffer.private: yunofile-buffer.p src/default-yunofile-buffer.h src/init-yunofile-buffer.h src/map-yunofile-buffer.h src/yunofile-buffer-array.h src/yunofile-buffer-size.h src/yunofile-buffer-max-size.h
	cat yunofile-buffer.p src/default-yunofile-buffer.h src/init-yunofile-buffer.h src/map-yunofile-buffer.h src/yunofile-buffer-array.h src/yunofile-buffer-size.h src/yunofile-buffer-max-size.h > yunofile-buffer.private

yunofile-buffer.public: yunofile-buffer.p
	cp yunofile-buffer.p yunofile-buffer.public

yunofile-buffer.a: compiled/default-yunofile-buffer.o compiled/init-yunofile-buffer.o compiled/map-yunofile-buffer.o compiled/yunofile-buffer-array.o compiled/yunofile-buffer-size.o compiled/yunofile-buffer-max-size.o
	ar r yunofile-buffer.a compiled/default-yunofile-buffer.o compiled/init-yunofile-buffer.o compiled/map-yunofile-buffer.o compiled/yunofile-buffer-array.o compiled/yunofile-buffer-size.o compiled/yunofile-buffer-max-size.o

compiled/default-yunofile-buffer.o: src/default-yunofile-buffer.c 
	gcc $(CFLAGS) -c src/default-yunofile-buffer.c -o compiled/default-yunofile-buffer.o

compiled/init-yunofile-buffer.o: src/init-yunofile-buffer.c 
	gcc $(CFLAGS) -c src/init-yunofile-buffer.c -o compiled/init-yunofile-buffer.o

compiled/map-yunofile-buffer.o: src/map-yunofile-buffer.c 
	gcc $(CFLAGS) -c src/map-yunofile-buffer.c -o compiled/map-yunofile-buffer.o

compiled/yunofile-buffer-array.o: src/yunofile-buffer-array.c 
	gcc $(CFLAGS) -c src/yunofile-buffer-array.c -o compiled/yunofile-buffer-array.o

compiled/yunofile-buffer-size.o: src/yunofile-buffer-size.c 
	gcc $(CFLAGS) -c src/yunofile-buffer-size.c -o compiled/yunofile-buffer-size.o

compiled/yunofile-buffer-max-size.o: src/yunofile-buffer-max-size.c 
	gcc $(CFLAGS) -c src/yunofile-buffer-max-size.c -o compiled/yunofile-buffer-max-size.o
