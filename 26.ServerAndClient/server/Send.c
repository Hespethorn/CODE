#include "head.h"
int SendMsg(Queue_t *queue, int netfd, Train *msg){
    Node_t *p = queue->pFront;
    while(p != NULL){
        if(p->netfd != netfd){
            send(p->netfd, msg, sizeof(Train), MSG_NOSIGNAL);
        }
        p = p->next;
    }
    return 1;
}
int SendFile(const int netfd, const char* pathname){
    Train *msg = (Train *)malloc(sizeof(Train));
    memset(msg->data, 0, sizeof(msg->data));
    msg->num = -1;
    strcpy(msg->data, pathname); 
    send(netfd, msg, sizeof(Train), 0);
    printf("pathname == %s\n",msg->data);
    int fd = open(pathname, O_RDONLY);
    struct stat st;
    fstat(fd, &st);
    
    int num = st.st_size;
    send(netfd, &num, sizeof(int), MSG_NOSIGNAL);
    char *buf = (char*)malloc(num);
    printf("size==%d\n",num);
    int total = 0;
    while(1){
        int ret = read(fd, buf + total, num - total);
        total += ret;
        send(netfd, buf, num, MSG_NOSIGNAL);
        if(total >= num){
            break;
        }
    }
    printf("SendFile finished\n");
    free(buf);
    close(fd);
    return 1;
}

