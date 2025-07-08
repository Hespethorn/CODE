#include "head.h"
int main(int argc, char *argv[]){                                  
    int fds[2];
    socketpair(AF_LOCAL, SOCK_STREAM, 0,fds);
    //父程序
    if(fork()){
        close(fds[0]);
        int fd = open("chat.txt", O_RDWR|O_CREAT|O_TRUNC, 0775);
        ERROR_CHECK(fd, -1, "open");
        printf("Father fd == %d\n", fd);
        write(fd, "Tell my monther",sizeof("Tell my monther"));
        SendFd(fds[1], fd);
        wait(NULL);
    }else{
        close(fds[1]);
        int fd = -1;
        RecvFd(fds[0], &fd);
        printf("childfd == %d\n",fd);
        ssize_t wret = write(fd, ", I am Ok!",sizeof("I am Ok!"));
        ERROR_CHECK(fd, -1, "RecvFd");
        ERROR_CHECK(wret, -1, "write");
    }
    return 0;
}

