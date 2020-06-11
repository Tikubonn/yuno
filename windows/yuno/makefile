
.PHONY: clean
clean:
	rm -f yuno.h 

.PHONY: h
h: 
	make yuno.h 

yuno.h: yuno.p src/setup-yuno.h
	cat yuno.p src/setup-yuno.h > yuno.h 
