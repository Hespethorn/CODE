#include "head.h"

int SendFd(int sockfd, int fdtosend){
    struct msghdr hdr;
    bzero(&hdr,sizeof(hdr));
    
    char buf[] = "Tell my monther";
    struct iovec iov[1];
    iov->iov_base = buf;
    iov->iov_len = 15;
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 1;
    
    struct cmsghdr *pmsg = (struct cmsghdr*)malloc(CMSG_LEN(sizeof(int)));
    pmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pmsg->cmsg_level = SOL_SOCKET;
    pmsg->cmsg_type = SCM_RIGHTS;
    *(int*)CMSG_DATA(pmsg) = fdtosend;
    hdr.msg_control = pmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));
    int ret = sendmsg(sockfd, &hdr, 0);
    ERROR_CHECK(ret, -1, "sendmsg");
    return 0;
}
