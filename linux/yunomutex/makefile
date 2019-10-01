
.always:

clean: .always
	rm -f yunomutex.lib
	rm -f yunomutex.private
	rm -f yunomutex.public

yunomutex.private: yunomutex.p
	cat yunomutex.p > yunomutex.private

yunomutex.public: yunomutex.p
	cat yunomutex.p > yunomutex.public

yunomutex.a:
	ar r yunomutex.a

