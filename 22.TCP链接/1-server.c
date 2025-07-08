#include <my_header.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
/* Usage:
 * 第一步实现双人通信
 * 第二步实现通过服务器的双人通信
 * 第三步实现通过服务器的多人聊天
 * 第四步实现30秒不通讯退出
 * 第五步实现私聊
 */
void TimeNow(){
    time_t now=time(NULL);
    struct tm *time_now=localtime(&now);
    printf("[北京时间:%02d:%02d:%02d]",time_now->tm_hour,time_now->tm_min,time_now->tm_sec);
}
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc,3);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"error socket");
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr=inet_addr(argv[1]);
    //n十进制转二进制
    int res_addr = 1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&res_addr,sizeof(int));
    int b_ret=bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    ERROR_CHECK(b_ret,-1,"bind error");
    int lis=listen(sockfd,50);
    ERROR_CHECK(lis,-1,"listen error");
    printf("服务器开机，正在监听网络:%s:%d\n",inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port));
    struct sockaddr_in client_addr;
    socklen_t client_len=sizeof(client_addr);
    int cli_sockfd;

    fd_set monitorset; //监听集合
    fd_set readyset; //就绪集合
    FD_ZERO(&monitorset);
    FD_SET(sockfd,&monitorset);
    char buf[4068]={0};
    while(1){
        memcpy(&readyset,&monitorset,sizeof(fd_set));
        select(1024,&readyset,NULL,NULL,NULL);
        if(FD_ISSET(sockfd,&readyset)){
            cli_sockfd=accept(sockfd,(struct sockaddr*)&client_addr,&client_len);
            ERROR_CHECK(cli_sockfd,-1,"error accept");
            printf("客户端%d已连接\n",cli_sockfd);
            send(cli_sockfd,&client_addr.sin_port,sizeof(client_addr.sin_port),0);
            FD_CLR(sockfd,&monitorset);
            FD_SET(cli_sockfd,&monitorset);
            FD_SET(STDIN_FILENO,&monitorset);
        }
        if(FD_ISSET(cli_sockfd,&readyset)){
            ssize_t ret=recv(cli_sockfd,buf,sizeof(buf),0);
            TimeNow();
            printf("buf==%s\n",buf);
            if(ret==0||strcmp(buf,"exit\n")==0){
                TimeNow();
                printf("端口号%d客户端%d下线了，等待新的客户端\n",ntohs(client_addr.sin_port),cli_sockfd);
                FD_SET(sockfd,&monitorset);
                FD_CLR(cli_sockfd,&monitorset);
                FD_CLR(STDIN_FILENO,&monitorset);
            }
            memset(buf,0,sizeof(buf));
        }
        if(FD_ISSET(STDIN_FILENO,&readyset)){
            int ret=read(STDIN_FILENO,buf,sizeof(buf));
            ERROR_CHECK(ret,-1,"error read");
            if(ret==0||strcmp(buf,"exit\n")==0){
                TimeNow();
                printf("准备脱水\n");
                send(cli_sockfd,"serverexit",10,0);
                return 0;
            }
            send(cli_sockfd,buf,ret,0);
            memset(buf,0,sizeof(buf));
        }
    }
    close(cli_sockfd);
    close(sockfd);
    return 0;
}

