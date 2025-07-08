#include <arpa/inet.h>
#include <my_header.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
/* Usage:  */
int main(int argc, char *argv[]){                                  
    //检查输入数据的正确性
    ARGS_CHECK(argc, 3);
    //创建SOCKET
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    //确定服务端网络地址
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    //链接服务端
    int cret = connect (sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    ERROR_CHECK(cret, -1, "connect");
    printf("Server %d is connected, stdin 'exit' to getout\n",ntohs(server_addr.sin_port));
    //创建epoll的位图，结构体的缘故union 导致event和后面readset指向同一个区域
    struct epoll_event event;
    struct epoll_event readyset[1024];
    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");
    //监听输入和sockfd
    event.events = EPOLLIN;
    event.data.fd = sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
    
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    //接收信息
    char buf[1024]={0};
    while(1){
        int readynum = epoll_wait(epfd, readyset, 2, -1);
        //就绪集合的长度
        memset(buf, 0, sizeof(buf));
        //清空信息
        for(int i = 0; i < readynum; ++i){
            //监听输入
            if(readyset[i].data.fd == STDIN_FILENO){
                int ret = read(STDIN_FILENO, buf, sizeof(buf));
                ERROR_CHECK(ret, -1 ,"read");
                //输入exit退出
                if(ret == 0 || strcmp(buf,"exit\n") == 0){
                    printf("Good bye\n");
                    send(sockfd, "exit\n", 5, 0);
                    close(sockfd);
                    return 0;
                }
                //发送信息
                send(sockfd, buf, strlen(buf), 0);
            }else{
                //监听收信
                int ret = recv(sockfd, buf, sizeof(buf), 0);
                if(ret <= 0){
                    printf("Something error, waiting for new connect\n");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    while(1){
                        //服务端退出后，等待链接
                        close(sockfd);
                        sleep(1);
                        sockfd = socket(AF_INET, SOCK_STREAM, 0);
                        if(connect (sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != -1){
                            printf("New server has been connected\n");
                            event.events = EPOLLIN;
                            event.data.fd = sockfd;
                            epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
                            break;
                        }
                    }
                    continue;
                }
                printf("%s\n", buf);
            }
        }
    }
    close(sockfd);
    return 0;
}

