#include <my_header.h>
#include <unistd.h>
/* Usage:  */
typedef struct tickets{
    int ticket[20];
    int size;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}ticket_s;
void *sale1(void *arg){
    ticket_s *tic_p=(ticket_s*)arg;
    while(tic_p->size>0){
        pthread_mutex_lock(&tic_p->mutex);
        tic_p->ticket[tic_p->size-1]=0;
        tic_p->size--;
        printf("A刚卖了一张票，总共还剩下%d张票\n",tic_p->size);
        // 通知可能正在等待的线程
        pthread_cond_signal(&tic_p->cond);
        pthread_mutex_unlock(&tic_p->mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}
void *sale2(void *arg){
    ticket_s *tic_p=(ticket_s*)arg;
    while(tic_p->size>0){
        pthread_mutex_lock(&tic_p->mutex);
        tic_p->ticket[tic_p->size-1]=0;
        tic_p->size--;
        printf("B刚卖了一张票，总共还剩下%d张票\n",tic_p->size);
        // 通知可能正在等待的线程
        pthread_cond_signal(&tic_p->cond);
        pthread_mutex_unlock(&tic_p->mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}
int main(int argc, char *argv[]){  
    ticket_s *tic=(ticket_s*)calloc(1,sizeof(ticket_s));
    ERROR_CHECK(tic,NULL,"calloc fail");
    for(int i=0;i<20;i++){
        tic->ticket[i]=1;
        tic->size++;
    }
    printf("初始状态，总共%d张票\n\n",tic->size);
    //建立票据数组
    pthread_t thread1,thread2;
    pthread_mutex_init(&tic->mutex,NULL);
    pthread_cond_init(&tic->cond,NULL);
    pthread_create(&thread1,NULL,sale1,tic);
    pthread_create(&thread2,NULL,sale2,tic);
    pthread_mutex_lock(&tic->mutex);

    while(tic->size>9){
        pthread_cond_wait(&tic->cond,&tic->mutex);
    }
    pthread_mutex_unlock(&tic->mutex);
    pthread_mutex_lock(&tic->mutex);
    tic->size=10+tic->size;
    printf("\n补充10张票，总共还剩下%d张票\n\n",tic->size);
    for(int i=0;i<10;i++){
        tic->ticket[tic->size-i]=1;
    }
    pthread_mutex_unlock(&tic->mutex);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    return 0;
}

