#include "head.h"

int main(int argc, char *argv[]){              
    ARGS_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr (argv[1]);
    int cret = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(cret, -1, "connect");
    printf("Server has been connected;\n");
    
    //将文件描述符放入监听
    int epfd = epoll_create(1);
    struct epoll_event event;
    struct epoll_event readyset[2];
    event.events = EPOLLIN;
    event.data.fd = sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    
    Train *msg = (Train*)malloc(sizeof(Train));
    
    while(1){
        int readynum = epoll_wait(epfd, readyset, 2, -1);
        for(int i =0; i < readynum; ++i){
            //只存在收发消息两种情况
            msg->num = 0;
            memset(msg->date, 0, 1024);
            if(readyset[i].data.fd == sockfd){
                //接收到消息 约定接到正数就是消息，-1就是文件
                int ret = recv(sockfd, msg, sizeof(Train), 0);
                ERROR_CHECK(ret, -1, "recv");
                //以结构体形式接发消息
                if(ret <= 0 || strcmp(msg->date, "exit\n") == 0){
                    printf("Server disconnect\n");
                    goto end;
                }
                if(msg->num > 0){
                    printf("%s\n", msg->date);
                }else{
                    //接文件
                    if(Recvfile(sockfd, msg)){
                        printf("Download file finished\n");
                    }else{
                        printf("error download file");
                    }
                }
            }else{
                msg->num = read(STDIN_FILENO, &msg->date, sizeof(msg->date));
                if(msg->num >= 0){
                    send(sockfd, msg, sizeof(Train), 0);
                }
                if(strcmp(msg->date, "exit\n") == 0 || msg->num <= 0){
                    printf("I will exit\n");
                    goto end;
                }
            }
        }
    }
    end:
    free(msg);
    close(sockfd);
    close(epfd);
    return 0;
}

