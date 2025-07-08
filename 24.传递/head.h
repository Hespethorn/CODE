#include <my_header.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

enum{
    FREE,
    BUSY
};

typedef struct workerData_s{
    pid_t pid;
    int status;
}workerData_t;

int MakeWorker(const int workernum, workerData_t *workaddr);                                 
//使用sendmsg和recvmsg进行进程间文件描述符的传输
//需要管道来实现通信 管道一条可以实现全双工
//无法单纯使用管道来通信（无法传输文件描述符指向的对象） 所以使用函数socketpair
int SendFd(int sockfd, int fdtosend);
int RecvFd(int sockfd, int *pfdtorecv);
