#include "head.h"
int ExitPipe[2];
void InitMsg(Train *msg){
    msg->num = 0;
    memset(msg->data, 0, 1024);
}
void handle(int sig){
    write(ExitPipe[1], "1", 1);
}
int main(int argc, char *argv[]){
    //server 127.0.0.1 1234 pathname worker
    ARGS_CHECK(argc, 5);
    int sockfd = Ready(argv[1], argv[2]);
    signal(SIGUSR1, handle);
    signal(SIGINT, handle);
    //将文件描述符放入监听
    pipe(ExitPipe);
    if(fork()){
        close(ExitPipe[0]);
        wait(NULL);
        return 0;
    }  //父进程负责监听信号

    close(ExitPipe[1]);

    //下面部分由子进程执行
    int epfd = epoll_create(1);
    struct epoll_event readyset[1024];
    EpollAdd(epfd, sockfd);
    EpollAdd(epfd, STDIN_FILENO);
    EpollAdd(epfd, ExitPipe[0]);

    Train *msg = (Train*)malloc(sizeof(Train));
    Queue_t *queue = (Queue_t*)malloc(sizeof(Queue_t));
    int qret = QueueInit(queue);
    ERROR_CHECK(qret, -1, "QueueInit");

    int pidnum = atoi(argv[4]);
    pthread_t pid[pidnum];
    Res_t *res = (Res_t *)malloc(sizeof(Res_t));
    res->pqueue = queue;
    memset(res->pathname, 0, PATHLEN);
    memcpy(res->pathname, argv[3], strlen(argv[3]));
    PthreadInit(pidnum, pid, res);

    while(1){
        int readynum = epoll_wait(epfd, readyset, 2, -1);
        for(int i =0; i < readynum; ++i){
            //只存在收发消息两种情况
            InitMsg(msg);

            if(readyset[i].data.fd == sockfd){
                //接收客户端连接
                pthread_mutex_lock(&res->mutex);
                while(res->fdcount > pidnum){
                    pthread_cond_wait(&res->cond, &res->mutex);
                }
                ++ res->fdcount;
                int netfd = accept(sockfd, NULL, NULL);
                ERROR_CHECK(netfd, -1, "accept");
                EnQueue(queue, netfd);
                EpollAdd(epfd, netfd);
                printf("Clientfd == %d accept\n",netfd);
                pthread_cond_broadcast(&res->cond);
                pthread_mutex_unlock(&res->mutex);

            }else if(readyset[i].data.fd == STDIN_FILENO){
                //输入信息
                msg->num = read(STDIN_FILENO, &msg->data, sizeof(msg->data));
                if(msg->num <= 0){
                    strcpy(msg->data, "exit\n");
                }
                SendMsg(queue, 0, msg);
                if(strcmp(msg->data,"exit\n") == 0){
                    res->flag = 1;
                    goto end;
                }
            }else if(readyset[i].data.fd == ExitPipe[0]){
                strcpy(msg->data, "exit\n");
                msg->num = strlen(msg->data);
                SendMsg(queue, 0, msg);
                res->flag = 1;
                pthread_cond_broadcast(&res->cond);
                goto end;
            }else{
                Node_t *p = queue->pFront;
                while(p != NULL){
                    InitMsg(msg);
                    if(readyset[i].data.fd == p->netfd){
                        int ret = recv(p->netfd, msg, sizeof(Train), 0);
                        if(ret <= 0 || strcmp(msg->data, "exit\n") == 0){
                            EpollDel(epfd, p->netfd);
                            int netfd = p->netfd;
                            close(p->netfd);
                            p = p->next;
                            DeleNodeQueue(queue, netfd);
                            printf("Client %d exit\n", netfd);
                            continue;
                        }
                        printf("Client %d send %s\n", p->netfd, msg->data);
                        SendMsg(queue, p->netfd, msg);
                    }
                    p = p->next;
                }
            }
        }
    }
end:
    for(int i = 0; i < pidnum; ++i){
        pthread_join(pid[i], NULL);
        printf("pid == %ld exit\n", pid[i]);
    }
    close(sockfd);
    close(epfd);
    free(res);
    DeQueue(queue);
    return 0;
}

