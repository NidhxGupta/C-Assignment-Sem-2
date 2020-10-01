output: pwck_main.o pwck_server.o
	gcc pwck_main.o pwck_server.o -o output
pwck_main.o: pwck_main.c pwck_server.h
	gcc -c pwck_main.c
pwck_server.o: pwck_server.c pwck_server.h
	gcc -c pwck_server.c
clean:
	rm output pwck_main.o pwck_server.o 