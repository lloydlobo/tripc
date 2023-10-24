build:
	gcc src/main.c -o tripc

run:
	make build && ./tripc

dbgrun:
	make build && valgrind ./tripc

