#include "head.h"

/* Usage: 实现入队与出队 */
int QueueInit(Queue_t *queue){
    bzero(queue,sizeof(Queue_t));
    return 0;
}
int EnQueue(Queue_t *queue, int netfd){
    Node_t *pNew = (Node_t *)calloc(1,sizeof(Node_t));
    pNew->netfd = netfd;
    if(queue->queuesize == 0){
        queue->pFront = pNew;
        queue->pRear = pNew;
    }
    else{
        queue->pRear->next = pNew;
        queue->pRear = pNew;
    }
    ++queue->queuesize;
    return 0;
}
int DeleNodeQueue(Queue_t *queue, const int netfd){
    Node_t *pcur = queue->pFront;
    Node_t *prev = pcur;
    while(pcur != NULL){
        if(pcur->netfd == netfd){
            //判断特殊位置 头尾节点 以及 如果只剩头的情况
            if(queue->queuesize > 1){
                if(pcur == queue->pFront){
                    queue->pFront = queue->pFront->next;
                }else if(pcur == queue->pRear){
                    queue->pRear = prev;
                }
                prev->next = pcur->next;
            }
            free(pcur);
            --queue->queuesize;
            break;
        }
        prev = pcur;
        pcur = pcur->next;
    }
    return 0;
}
int DeQueue(Queue_t *queue){
    Node_t *pcur = queue->pFront;
    queue->pFront = pcur->next;
    if(queue->queuesize == 1){
        queue->pRear = NULL;
    }
    free(pcur);
    --queue->queuesize;
    return 0;
}
int VisitQueue(Queue_t *queue){
    Node_t *pcur = queue->pFront;
    while(pcur){
        printf("%3d", pcur->netfd);
        pcur = pcur->next;
    }
    printf("\n");
    return 0;
}
