
.always:

clean: .always
	rm -f yunosemaphore.lib
	rm -f yunosemaphore.private
	rm -f yunosemaphore.public

yunosemaphore.private: yunosemaphore.p
	cat yunosemaphore.p > yunosemaphore.private

yunosemaphore.public: yunosemaphore.p
	cat yunosemaphore.p > yunosemaphore.public

yunosemaphore.a:
	ar r yunosemaphore.a

