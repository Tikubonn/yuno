
.always:

clean: .always
	rm -f yunotime.private
	rm -f yunotime.public
	rm -f yunotime.a
	rm -f compiled/yunosleep.o

yunotime.private: yunotime.p
	cp yunotime.p yunotime.private

yunotime.public: yunotime.p
	cp yunotime.p yunotime.public 

yunotime.a: compiled/yunosleep.o
	ar r yunotime.a compiled/yunosleep.o

compiled/yunosleep.o: src/yunosleep.c
	gcc $(CFLAGS) -c src/yunosleep.c -o compiled/yunosleep.o

