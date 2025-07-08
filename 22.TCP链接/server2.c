#include <arpa/inet.h>
#include <fcntl.h>
#include <my_header.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <time.h>
/* Usage:  */
typedef struct List{
    int readyfd[1024];
    int fdtime[1024];
    int chatfd[1024];
}List;
void InitArr(int *arr){
    for(int i=0; i < 1024; ++i){
        arr[i] = -1;
    }
}
//设置时间参数
void Time(char *set_time){
    time_t now_t;
    time(&now_t);
    sprintf(set_time, "%s", ctime(&now_t));
}
//加入监控
void FdInSet(int fd, int epfd, struct epoll_event *event){
    event->events = EPOLLIN;
    event->data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, event);
}
void SendMes(){
    //广播，转发

}
void CloseFd(int *count, int index, int epfd, List *list){
    epoll_ctl(epfd, EPOLL_CTL_DEL, list->readyfd[index], NULL);
    close(list->readyfd[index]);
    (*count) --;
    //将对应位置
    list->fdtime[index] = -1;
    list->chatfd[index] = -1;
    list->readyfd[index] = -1;
}
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc, 3);
    //设置socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    //配置服务端基本信息
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    //地址重用
    int reuse = 1; // 申请了一个整数，数值是1
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    int bret = bind (sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    ERROR_CHECK(bret, -1, "bind");
    int lret = listen(sockfd, 50);
    ERROR_CHECK(lret, -1, "listen");
    printf("Server is listening \n");

    //创建epoll
    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");

    struct epoll_event event;
    struct epoll_event readyset[1024];
    FdInSet(sockfd, epfd, &event);
    FdInSet(STDIN_FILENO, epfd, &event);

    //用来存储接到的文件描述符
    List *list = (List*)malloc(sizeof(List));


    int num = 0;
    int count = 0;

    InitArr(list->chatfd);
    InitArr(list->fdtime);
    InitArr(list->readyfd);


    char buf[1024] = {0};
    char msg[2048] = {0};
    char time_now[64] = {0};
    
    Time(time_now);
    char path_n [128];
    sprintf(path_n,"history %s.txt",time_now);
    int openfd = open(path_n, O_RDWR|O_CREAT|O_TRUNC, 0775);
    ERROR_CHECK(openfd, -1, "open");
    //文件描述符
    int maxedfd = (sockfd > openfd ? sockfd : openfd) + 1;

    while(1){

        int readynum = epoll_wait(epfd, readyset, 1024, 1000);

        //超时退出
        for(int i=0; i < num; ++i){
            if(list->readyfd[i] != -1 && time(NULL)-list->fdtime[i] > 100){
                memset(msg, 0, sizeof(msg));
                Time(time_now);
                sprintf(msg, "%sClinet %d sleep too long\n", time_now, list->readyfd[i]);
                printf("%s\n", msg);
                CloseFd(&count, i, epfd, list);
            }
        }

        for(int i=0; i < readynum; ++i){
            memset(buf, 0, sizeof(buf));
            memset(msg, 0, sizeof(msg));
            memset(time_now, 0, sizeof(time_now));

            // 检测到接收情况
            if(readyset[i].data.fd == sockfd){
                //将accept获得的clientfd放入readyfd中，第几个就放在下标处
                int clientfd = accept(sockfd, NULL, NULL);
                ERROR_CHECK(clientfd, -1 ,"accept");

                if(num >= 1024){
                    Time(time_now);
                    printf("%sToo many clients\n", time_now);
                    close(clientfd);
                    continue;
                }

                //根据 fd 内容返回下标，通过一个数组记录
                list->readyfd[clientfd - maxedfd] = clientfd;
                //同一个 fd 放入同一个位置，下标是fd - 5；
                list->fdtime[clientfd - maxedfd] = time(NULL);
                FdInSet(clientfd, epfd, &event);
                num = num > (clientfd - maxedfd + 1) ? num : (clientfd - maxedfd + 1);
                Time(time_now);
                ++ count;
                printf("%sClient %d has been accepted, the num of them is %d\n", time_now, clientfd, count);
                //如果只想两人聊天，此处
                //epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,NULL);
            }else if(readyset[i].data.fd == STDIN_FILENO){
                //检测到输入情况
                int ret = read(STDIN_FILENO, buf, sizeof(buf));
                ERROR_CHECK(ret, -1 ,"read");
                if(ret == 0 || strcmp(buf, "exit\n") == 0){
                    goto end;
                }
                Time(time_now);
                sprintf(msg, "%sServer message: %s", time_now, buf);
                write(openfd, msg, strlen(msg));

                for(int j = 0; j < num; ++j){
                    //这个下标的节点未被删除
                    if(list->readyfd[j] != -1){
                        send(list->readyfd[j], msg, strlen(msg), 0);
                    }
                }
            }else{
                //接到消息并群发
                int clientfd = readyset[i].data.fd;
                int index = clientfd - maxedfd;
                list->fdtime[index] = time(NULL);
                int ret = recv(clientfd, buf, sizeof(buf), 0);

                if(ret <= 0 || strcmp(buf, "exit\n") == 0){
                    CloseFd(&count, index, epfd, list);
                    Time(time_now);
                    printf("%sClient %d exit, there are %d Clients\n", time_now, clientfd, count);
                    continue;

                } else if(strncmp(buf, "*chat ", 6) == 0){

                    int chatfd_n = atoi(buf + 6);
                    if(chatfd_n > num || chatfd_n == clientfd || chatfd_n - maxedfd < 0){
                        send(clientfd, "ERROR", 5, 0);
                        continue;
                    }
                    list->chatfd[index] = chatfd_n;
                    sprintf(msg, "You can send one mes to Client %d\n", chatfd_n);
                    send(clientfd, msg, strlen(msg), 0);
                }else{

                    Time(time_now);
                    //私聊
                    if(list->chatfd[index] != -1){
                        sprintf(msg, "%s[*chat] Client %d message to %d: %s", time_now, clientfd, list->chatfd[index], buf);
                        write(openfd, msg, strlen(msg));
                        printf("%s\n", msg);
                        send(list->chatfd[index], msg, strlen(msg), 0);
                        list->chatfd[index] = -1;
                    }else{
                        sprintf(msg, "%sClient %d message: %s", time_now, clientfd, buf);
                        write(openfd, msg, strlen(msg));
                        printf("%s\n", msg);
                        for(int j = 0; j < num; ++j){
                            //广播
                            if(list->readyfd[j] != -1 && list->readyfd[j] != clientfd){
                                send(list->readyfd[j], msg, strlen(msg), 0);
                            }

                        }
                    }
                }
            } //if    
        } //for
    } //while
    end:
    close(openfd);
    close(sockfd);
    return 0;
} 
