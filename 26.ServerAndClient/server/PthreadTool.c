#include "head.h"
void *PthreadPool(void *arg){
    Res_t *res = (Res_t *)arg;
    while(1){
        pthread_mutex_lock(&res->mutex);
        while(res->fdcount <= 0){
            if(res->flag == 1){
                printf("exit\n");
                pthread_mutex_unlock(&res->mutex);
                pthread_exit(NULL);
            }
            pthread_cond_wait(&res->cond, &res->mutex);
        }
        -- res->fdcount; 
        int netfd = res->pqueue->pRear->netfd;
        pthread_cond_broadcast(&res->cond);
        pthread_mutex_unlock(&res->mutex);
        SendFile(netfd, res->pathname);
        printf("Is sending file to client %d\n", netfd);
        //sleep(1);
    }
    pthread_exit(NULL);
}
int PthreadInit(int pidnum, pthread_t *pid, Res_t *res){
    pthread_cond_init(&res->cond, NULL);
    pthread_mutex_init(&res->mutex, NULL);
    res->flag = 0;
    res->fdcount = 0;
    for(int i = 0; i < pidnum; ++i){
        pthread_create(&pid[i], NULL, PthreadPool, res);
        printf("pid == %ld is ready\n", pid[i]);
    }
    return 0;
}
