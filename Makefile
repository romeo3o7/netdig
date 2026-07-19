.SILENT:

ip:
	gcc src/ip.c -o build/main
	./build/main

interface:
	gcc src/interface.c -o build/main
	./build/main
