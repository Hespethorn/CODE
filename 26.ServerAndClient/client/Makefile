clean: client 
	rm -rf recv.o client.o
client: client.o recv.o
	gcc client.o recv.o -o client
client.o: client.c
	gcc -c client.c -g -Wall -o client.o
recv.o: recv.c
	gcc -c recv.c -g -Wall -o recv.o
