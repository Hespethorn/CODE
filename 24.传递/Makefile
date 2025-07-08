server: main.o recv.o send.o
	gcc main.o recv.o send.o -o server -lpthread
main.o: main1.c
	gcc -c main1.c -o main.o -g -Wall
send.o: send.c
	gcc -c send.c -o send.o -g -Wall 
recv.o: recv.c
	gcc -c recv.c -o recv.o -g -Wall 
