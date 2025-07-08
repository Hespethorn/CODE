#include "head.h"

int RecvFd(int sockfd, int *pfdtorecv){
    struct msghdr hdr;
    bzero(&hdr,sizeof(hdr));
    char buf[1024] = {0};
    struct iovec iov[1];
    iov->iov_base = buf;
    iov->iov_len = 1024;
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 1;
    
    struct cmsghdr *pmsg = (struct cmsghdr*)malloc(CMSG_LEN(sizeof(int)));
    pmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pmsg->cmsg_level = SOL_SOCKET;
    pmsg->cmsg_type = SCM_RIGHTS; //传文件对象

    hdr.msg_control = pmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));

    int ret = recvmsg(sockfd, &hdr, 0);
    ERROR_CHECK(ret, -1, "sendmsg");
    
    printf("buf == %s, fdtorecv == %d\n", buf,*(int*)CMSG_DATA(pmsg));
    *pfdtorecv = *(int*)CMSG_DATA(pmsg);
    return 0;
}
