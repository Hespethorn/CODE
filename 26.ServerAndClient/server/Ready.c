#include "head.h"

/* Usage:  */
int Ready(char *ip,char *port){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    int flag = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr (ip);
    int bret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    ERROR_CHECK(bret, -1, "bind");
    listen(sockfd, 10);
    printf("Server is listening\n");
    return sockfd;
}
