#include <my_header.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <wait.h>
/* Usage:服务端接收并且给工人进程传文件 */
typedef struct Train{
    int size;
    char data[1024];
}Train;
typedef struct WorkerData{
    pid_t pid;
    int status; // 1 忙 0 闲
    int pipefd; //进程通信管道
}WorkerData;

int exitPipe[2];//全局变量 handler可以访问

void handler(int signum){
    printf("signum = %d\n", signum);
    write(exitPipe[1],"1",1);
}

//实现进程间通信
int sendfd(int sockfd, int flag, int fdtosend){
    // sockfd是传输介质 fdtosend是待发送的文件对象的fd
    struct msghdr hdr; //消息结构
    bzero(&hdr,sizeof(hdr)); // name 填NULL和0
    //消息的正文
    // 准备一个iovec数组
    struct iovec iov[1];
    iov[0].iov_base = &flag;
    iov[0].iov_len = sizeof(flag);
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 1;
    // 消息的控制字段 data要放一个fd，是一个int
    struct cmsghdr *pcmsg = (struct cmsghdr *)malloc(CMSG_LEN(sizeof(int)));
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int)); //总长度
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS; // 传文件对象
    *(int *)CMSG_DATA(pcmsg) = fdtosend; //求data首地址-->转int*-->解引用赋值
    hdr.msg_control = pcmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));
    int ret = sendmsg(sockfd, &hdr, 0);
    ERROR_CHECK(ret,-1,"sendmsg");
    free(pcmsg); // 释放动态分配的内存
    return 0;
}

int recvfd(int sockfd, int *pflag, int *pfdtorecv){
    // sockfd是传输介质 fdtosend是待发送的文件对象的fd
    struct msghdr hdr; //消息结构
    bzero(&hdr, sizeof(hdr)); // name 填NULL和0
    struct iovec iov[1];
    iov[0].iov_base = pflag;
    iov[0].iov_len = sizeof(int);
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 1;
    struct cmsghdr *pcmsg = (struct cmsghdr *)malloc(CMSG_LEN(sizeof(int)));
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int)); //总长度
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS; // 传文件对象
    hdr.msg_control = pcmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));
    int ret = recvmsg(sockfd, &hdr, 0);
    ERROR_CHECK(ret,-1,"recvmsg");
    *pfdtorecv = *(int *)CMSG_DATA(pcmsg);
    printf("flag = %d, fdtorecv = %d\n", *pflag, *pfdtorecv);
    free(pcmsg); // 释放动态分配的内存
    return 0;
}
void TansFile(int netfd){
    //要传输的文件
    char name[] = "text.txt";
    int size = strlen(name);
    //假设这个乱码文件
    int fd = open(name, O_RDWR);
    ERROR_CHECK(fd, -1,"open");
    struct stat st;
    fstat(fd, &st);
    int filesize = st.st_size;
    //发送文件名，大小，内容；
    send(netfd, &size, sizeof(int), MSG_NOSIGNAL);
    send(netfd, name, strlen(name), MSG_NOSIGNAL);
    send(netfd, &filesize, sizeof(int), MSG_NOSIGNAL);
    
    int num = 0;
    while(num < filesize){
        char buf[1024] = {0};
        int ret = read(fd, buf, sizeof(buf));
        send(netfd, &ret, sizeof(int), MSG_NOSIGNAL);
        send(netfd, buf, ret, MSG_NOSIGNAL);
        num += ret;
        sleep(1);
    }
    close(fd);
    return;
}
//工人进程干了什么
void MakeWorker(int workernum, WorkerData * workerArr){
    for(int i = 0; i < workernum; ++i){
        int pipe[2];
        socketpair(AF_LOCAL, SOCK_STREAM, 0, pipe);
        pid_t pid = fork();
        if(pid == 0){
            // 只有子进程
            while(1){
                close(pipe[0]);
                int netfd;
                int flag;
                recvfd(pipe[1], &flag, &netfd);
                if(flag == 1){
                    printf("I am going to exit!\n");
                    exit(0);
                }
                TansFile(netfd);
                printf("netfd = %d finish send\n", netfd);
                // 工人完成业务
                close(netfd);
                pid_t pid = getpid();
                write(pipe[1], &pid, sizeof(pid));
            }
            // 子进程离不开死循环，不会调用下次fork
        }
        close(pipe[1]);
        // 只有父进程才能走到这里
        workerArr[i].pid = pid;
        workerArr[i].status = 0;
        workerArr[i].pipefd = pipe[0];
        printf("i = %d, pid = %d, pipefd = %d\n", i, pid, pipe[0]);
    }
    return;
}
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 4);
    
    //创建几个工人进程
    int workernum = atoi(argv[3]);
    WorkerData *worker = (WorkerData *)calloc(workernum, sizeof(WorkerData));

    //创建一根管道
    pipe(exitPipe);
    // signal要在fork之后
    signal(SIGUSR1, handler);

    MakeWorker(workernum,worker);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "error socket");
    //创建套接字
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    //设置IP
    // 设置地址可重用
    int opt = 1;
    ERROR_CHECK(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)), -1, "setsockopt");
    int bret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(bret, -1, "bind");
    listen(sockfd, 50);
    //建立监听

    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");
    struct epoll_event event;
    struct epoll_event readyset[1024];
    event.events = EPOLLIN;
    event.data.fd = sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
    event.data.fd = exitPipe[0];
    epoll_ctl(epfd, EPOLL_CTL_ADD, exitPipe[0], &event);
    for(int i = 0; i < workernum; ++i){
        event.data.fd = worker[i].pipefd;
        epoll_ctl(epfd, EPOLL_CTL_ADD, worker[i].pipefd, &event);
    }

    while(1){
        int readynum = epoll_wait(epfd, readyset, 1024, -1);
        for(int i = 0; i < readynum; ++i){
            if(readyset[i].data.fd == sockfd){
                int netfd = accept(sockfd, NULL, NULL);
                //接收客户端的信号
                printf("1 client connect, netfd = %d\n", netfd);
                for(int j = 0; j < workernum; ++j){
                    if(worker[j].status == 0){
                        int flag = 0; // flag为0 说明不用退出
                        sendfd(worker[j].pipefd,flag,netfd);
                        worker[j].status = 1;
                        break;
                    }
                }
                close(netfd);
            }else if(readyset[i].data.fd == exitPipe[0]){
                printf("Process pool is going to exit!\n");
                //关闭所有的工人
                for(int j = 0; j < workernum; ++j){
                    int flag = 1;
                    sendfd(worker[j].pipefd, flag, 0);
                }
                for(int j = 0; j < workernum; ++j){
                    wait(NULL);//等待子进程终止并回收内核资源
                }
                printf("All worker has been killed!\n");
                free(worker);
                exit(0);
            }else{
                for(int j = 0; j < workernum; ++j){
                    if(readyset[i].data.fd == worker[j].pipefd){
                        pid_t pid;
                        read(readyset[i].data.fd, &pid, sizeof(pid));
                        printf("worker %d is finished!\n", pid);
                        worker[j].status = 0;
                        break;
                    }
                }
            }
        }
    }
    close(sockfd);
    close(epfd);
    return 0;
}

#include <my_header.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
/* Usage: 客户端传输文件 */
typedef struct Train{
    int size;
    char data[1024];
}Train;
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 3);
    //检查是否三个输入
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "error socket");
    //创建套接字
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    //设置IP
    int cret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(cret, -1, "connect");
    printf("Server is connecting\n");
    //建立连接
    //    int epfd = epoll_create(1);
    //    ERROR_CHECK(epfd, -1, "epoll_create");
    //    struct epoll_event event;
    //    struct epoll_event readyset[2];
    //    event.events = EPOLLIN;
    //    event.data.fd = sockfd;
    //    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
    ////  event.data.fd = STDIN_FILENO;
    ////  epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    //    //添加监控 输入和输出

    //    while(1){
    //        int readynum = epoll_wait(epfd, readyset, 2,-1);
    //        for(int i = 0; i < readynum; ++i){
    //            memset(buf, 0, sizeof(buf));
    //            if(readyset[i].data.fd == STDIN_FILENO){
    //                ssize_t ret = read(STDIN_FILENO, buf, sizeof(buf));
    //                int sret = send(sockfd, buf, ret, 0);
    //                ERROR_CHECK(sret, -1, "send");
    //            }else{
    //第一次告知名称
    Train *train = (Train*)malloc(sizeof(Train));
    int ret = recv(sockfd, &train->size, sizeof(int), 0);
    ERROR_CHECK(ret, -1, "recv");

    char *name = (char*)malloc(train->size);
    memset(name, 0, train->size);
    recv(sockfd, name, train->size, 0);
    fflush(stdout);
    //第二次告知文件大小
    ret = recv(sockfd, &train->size, sizeof(int), 0);
    int size = train->size;
    ERROR_CHECK(ret, -1, "recv");
    printf("file name == %s\t, filesize == %d\n", name, size);
    fflush(stdout);

    int fd = open(name, O_WRONLY|O_CREAT|O_TRUNC, 0666);
    ERROR_CHECK(fd, -1, "OPEN");
    
    //记录已经读取的长度
    int num = 0;
    while(num < size){
        //将要发送的长度
        recv(sockfd, &train->size, sizeof(int), 0);
        ret = recv(sockfd, &train->data, train->size, 0);
        
        write(fd, train->data, ret);
        while(ret < train->size){
            ret += recv(sockfd, &train->data, sizeof(train->data)-ret, 0);
            write(fd, train->data, strlen(train->data));
        }
        num += ret;
        double result = (double) num / size * 100;
        for(int i = 0; i < result / 10; ++i){
            printf("-");
        }
        printf("%5.02lf%%\r", result);
        fflush(stdout);
        //sleep(1);
    }
    printf("\n");
    free(train);
    close(fd);
    close(sockfd);
    return 0;
}

