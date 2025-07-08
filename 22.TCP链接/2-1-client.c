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
struct sockaddr_in GetServerSockfd(char* addr,char* port){
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(atoi(port));
    server_addr.sin_addr.s_addr=inet_addr(addr);
    return server_addr;
}
void TimeNow(){
    time_t now=time(NULL);
    struct tm *time_n=localtime(&now);
    printf("[%02d:%02d:%02d]",time_n->tm_hour,time_n->tm_min,time_n->tm_sec);
}
int main(int argc, char *argv[]){                                  
    ARGS_CHECK(argc,3);
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"error socket");
    struct sockaddr_in server_addr=GetServerSockfd(argv[1],argv[2]);
    //server_addr.sin_family=AF_INET;
    //erver_addr.sin_port=htons(atoi(argv[2]));
    //server_addr.sin_addr.s_addr=inet_addr(argv[1]);
    //十进制转二进制
    int con=connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    ERROR_CHECK(con,-1,"error connect");
    fd_set sockset;
    int port;
    recv(sockfd,&port,sizeof(int),0);
    printf("已经与服务端链接，输入exit退出;\n你的端口号是:%d\n",ntohs(port));
    char buf[4068]={0};
    while(1){
        FD_ZERO(&sockset);
        FD_SET(sockfd,&sockset);
        FD_SET(STDIN_FILENO,&sockset);
        int max_fd=1+((sockfd>STDIN_FILENO)?sockfd:STDIN_FILENO);
        select(max_fd,&sockset,NULL,NULL,NULL);
        if(FD_ISSET(sockfd,&sockset)){
            recv(sockfd,buf,sizeof(buf),0);
            TimeNow();
            printf("%s\n",buf);
            if(strcmp(buf,"exit\n")==0){
                TimeNow();
                printf("对面已经脱水\n");
            }
            if(strcmp(buf,"serverexit\n")==0||strlen(buf)==0){
                TimeNow();
                printf("服务器下线,将循环寻找服务器，直到新链接建立\n");
                while(1){
                    int new_sockfd=socket(AF_INET,SOCK_STREAM,0);
                    ERROR_CHECK(new_sockfd,-1,"creat newfd");
                    if(connect(new_sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))!=-1){
                        //这种方式可以考虑网络连接 recv(sockfd,client_addr,sizeof(client_addr),0);
                        close (sockfd);
                        sockfd=new_sockfd;
                        recv(sockfd,&port,sizeof(int),0);
                        printf("已经与服务端链接，输入exit退出;\n你的端口号是:%d\n",ntohs(port));
                        break;
                    }else{
                        close(new_sockfd);
                    }
                    sleep(1);
                }
            }
            memset(buf,0,sizeof(buf));
        }
        if(FD_ISSET(STDIN_FILENO,&sockset)){
            int ret=read(STDIN_FILENO,buf,sizeof(buf));
            ERROR_CHECK(ret,-1,"error read");
            send(sockfd,buf,ret,0);
            if(ret==0||strcmp(buf,"exit\n")==0){
                TimeNow();
                printf("脱水\n");
                return 0;
            }
            memset(buf,0,sizeof(buf));
        }
    }
    close(sockfd);
    return 0;
}

