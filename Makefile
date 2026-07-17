.SILENT:

all:
	gcc src/interface.c -o build/main
	./build/main
