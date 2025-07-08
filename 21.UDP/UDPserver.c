#include <my_header.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
/* Usage:通过UDP实现通信  */
int main(int argc, char *argv[]){                                  
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(sockfd,-1,"error socket");

    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(atoi(argv[2]));
    addr.sin_addr.s_addr=inet_addr(argv[1]);
    //32位所以需要转为二进制
    bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    printf("UDP服务器已启动，监听 %s:%s\n", argv[1], argv[2]);
    char buf[1024]={0};
    struct sockaddr_in client_addr;
    socklen_t socklen=sizeof(client_addr);
    //接收用的sockaddr
    fd_set sockset;
    printf("等待UDP客户端发送信息\n");
    while(1){
        FD_ZERO(&sockset);
        FD_SET(STDIN_FILENO,&sockset);
        FD_SET(sockfd,&sockset);
        select(1024,&sockset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&sockset)){
            int ret=read(STDIN_FILENO,buf,sizeof(buf));
            sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
            bzero(buf,ret);
        }
        if(FD_ISSET(sockfd,&sockset)){
            ssize_t ret_r=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&client_addr,&socklen);
            if(strcmp(buf,"exit\n")==0||ret_r==0){
                printf("对面退出聊天\n");
                exit(1);
            }
            printf("buf = %sip = %s,port = %d\n",buf,inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            bzero(buf,ret_r);
        }
    }
    close(sockfd);    
    return 0;
}
