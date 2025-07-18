#include "head.h"
/* Usage:增减监听  */
int EpollAdd(int epfd, int fd){
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    return 0;
}
int EpollDel(int epfd, int fd){
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    return 0;
}

