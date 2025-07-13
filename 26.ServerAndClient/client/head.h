/* Usage: 客户端，主线程发送请求，子线程负责接收文件，采用一次性接收的方式 */
#ifndef CLIENT
#define CLIENT

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <my_header.h>

typedef struct Train{
    int num; //接收信息大小
    char date[1024]; //接受的信息
}Train;
typedef struct File{
    int num;
    char *data;
}File_t;
int recvn(const int sockfd, char *buf, size_t bufsize, int flag, const int len);
int Recvfile(int sockfd, Train *msg);

#endif
