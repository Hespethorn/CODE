#include "head.h"
int recvn(const int sockfd, char *buf, size_t bufsize, int flag, const int len){
    int total = 0;
    while(total < len){
        ssize_t ret = recv(sockfd, buf + total, len - total, flag);
        total += ret;
    }
    return 0;
}
int Recvfile(int sockfd, Train *msg){
    //获得文件名和大小，准备写入
    int fd = open(msg->date, O_WRONLY|O_CREAT|O_TRUNC, 0775);
    
    int num;
    recv(sockfd, &num, sizeof(int), 0);
    //根据大小创建空间
    char *buf = (char*)malloc(num);
    recvn(sockfd, buf, num, 0, num);
    
    //写入文件
    int ret  = write(fd, buf, num);
    ERROR_CHECK(ret, -1, "write");
    free(buf);
    close(fd);
    return 1;
}

