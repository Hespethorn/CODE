clean: Server
	rm -rf *.o
Server: Server.o Queue.o Epoll.o Send.o Ready.o PthreadTool.o
	gcc Server.o Queue.o Epoll.o Send.o Ready.o PthreadTool.o -lpthread -o Server
Epoll.o: Epoll.c
	gcc -c Epoll.c -g -Wall -o Epoll.o
PthreadTool.o: PthreadTool.c
	gcc -c PthreadTool.c -g -Wall -o PthreadTool.o
Queue.o: Queue.c
	gcc -c Queue.c -g -Wall -o Queue.o
Ready.o: Ready.c
	gcc -c Ready.c -g -Wall -o Ready.o
Send.o: Send.c
	gcc -c Send.c -g -Wall -o Send.o
Server.o: Server.c 
	gcc -c Server.c -g -Wall -o Server.o

