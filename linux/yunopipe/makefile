
.always:

clean: .always
	rm -f yunopipe.lib
	rm -f yunopipe.private
	rm -f yunopipe.public

yunopipe.private: yunopipe.p
	cat yunopipe.p > yunopipe.private

yunopipe.public: yunopipe.p
	cat yunopipe.p > yunopipe.public

yunopipe.a:
	ar r yunopipe.a

