
export CFLAGS += -I$(CURDIR)

.PHONY: clean
clean: 
	make clean -C src
	make clean -f $(makefile) target=$(target)

.PHONY: test
test:
	make lib -C src
	make test -f $(makefile) target=$(target)
