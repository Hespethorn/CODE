/* Usage: 服务端，主线程发送请求，子线程负责接收文件，采用一次性接收的方式 */
#ifndef CLIENT
#define CLIENT

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <wait.h>
#include <my_header.h>
#define PATHLEN 20
typedef struct Train{
    int num; //接收信息大小
    char data[1024]; //接受的信息
}Train;
typedef struct Node{
    int netfd;
    struct Node *next;
}Node_t;
typedef struct Queue{
    Node_t *pFront;
    Node_t *pRear;
    int queuesize;
}Queue_t;
typedef struct Resource{
    Queue_t *pqueue;
    int fdcount;
    int flag;
    char pathname[PATHLEN]; //路径
    Train *msg;
    pthread_cond_t cond; //信号
    pthread_mutex_t mutex; //锁
}Res_t;
int Ready(char *ip, char *port);
int EpollAdd(int epfd, int netfd);
int EpollDel(int epfd, int netfd);
int QueueInit(Queue_t *queue);
int EnQueue(Queue_t *queue, int netfd);
int DeQueue(Queue_t *queue);
int VisitQueue(Queue_t *queue);
int SendMsg(Queue_t *queue, int netfd, Train *msg);
int SendFile(const int netfd, const char *pathname);
int DeleNodeQueue(Queue_t *queue, const int netfd);
int PthreadInit(int pidnum, pthread_t *pid, Res_t *res);
#endif
