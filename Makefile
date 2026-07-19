.SILENT:

all:
	gcc src/ip.c -o build/main
	./build/main
