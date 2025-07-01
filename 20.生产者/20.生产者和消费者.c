#include <my_header.h>
#include <time.h>
#include <unistd.h>
//产品结构体
typedef struct Production{
    int val; //编号
    struct Production *next;
}Pro;
//资源池结构体
typedef struct Resourse{
    Pro *head; //链表头指针
    Pro *tail; //尾指针
    int size;  //链表尺寸
    pthread_mutex_t mutex; //互斥锁
    pthread_cond_t condp;  //生产者条件变量
    pthread_cond_t condc;  //消费者条件变量
}Res;
//生成编号
int num(){
    return rand()%100;
}
//打印当前链表
void printf_res(Res *res){
    printf("目前总共%d个产品是：",res->size);
    Pro *p=res->head;
    while(p->next!=NULL){
        printf("%d->",p->val);
        p=p->next;
    }
    printf("%d\n",res->tail->val);
}
//生产者线程函数
void *product(void* arg){
    Res *res_p=(Res*)arg;
    while(1){
        pthread_mutex_lock(&res_p->mutex);
        while(res_p->size==10){
            pthread_cond_wait(&res_p->condp,&res_p->mutex);
        }
        if(res_p->size==0){
            res_p->head=(Pro*)calloc(1,sizeof(Pro));
            res_p->head->val=num();
            res_p->tail=res_p->head;
        }else{
        res_p->tail->next=(Pro*)calloc(1,sizeof(Pro));
        res_p->tail->next->val=num();
        res_p->tail=res_p->tail->next;
        }
        res_p->size++;
        printf("生产者 %lu 生产了一个产品%d，", pthread_self()%10, res_p->tail->val);
        printf_res(res_p);
        pthread_cond_signal(&res_p->condc);
        pthread_mutex_unlock(&res_p->mutex);
        sleep(3);
    }
    pthread_exit(NULL);
}
void *consume(void* arg){
    Res *res_c=(Res*)arg;
    sleep(5);
    while(1){
        pthread_mutex_lock(&res_c->mutex);
        while(res_c->size==0){
            pthread_cond_wait(&res_c->condc,&res_c->mutex);
        }
        Pro *p=res_c->head;
        if(res_c->head!=res_c->tail){
        res_c->head=res_c->head->next;
        }
        free(p);
        res_c->size--;
        printf("消费者 %lu 消费了一个产品", pthread_self()%10);
        if(res_c->size!=0){
            printf_res(res_c);
        }else{
            printf("\n");
        }
        pthread_cond_signal(&res_c->condp);
        pthread_mutex_unlock(&res_c->mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}
int main(int argc, char *argv[]){                                  

    pthread_t threadp1,threadp2,threadp3;
    pthread_t threadc1,threadc2;
    Res *res=(Res*)calloc(1,sizeof(Res));
    ERROR_CHECK(res,NULL,"calloc res");
    pthread_mutex_init(&res->mutex,NULL);
    pthread_cond_init(&res->condp,NULL);
    pthread_cond_init(&res->condc,NULL);
    //设置三个生产者，两个消费者
    res->head=(Pro*)calloc(1,sizeof(Pro));
    res->head->val=num();
    res->size=1;
    res->tail=res->head;
    //设置产品链表
    for(int i=1;i<8;i++){
        res->tail->next=(Pro*)calloc(1,sizeof(Pro));
        res->tail->next->val=num();
        res->tail=res->tail->next;
        res->size++;
    }
    //将尾指针指向最后一个
    //p指向头指针
    printf_res(res);
    //准备工作完成
    //分别进入生产者和消费者进程
    pthread_create(&threadp1,NULL,product,res);
    pthread_create(&threadp2,NULL,product,res);
    pthread_create(&threadp3,NULL,product,res);
    pthread_create(&threadc1,NULL,consume,res);
    pthread_create(&threadc2,NULL,consume,res);

    pthread_join(threadp1,NULL);
    pthread_join(threadp2,NULL);
    pthread_join(threadp3,NULL);
    pthread_join(threadc1,NULL);
    pthread_join(threadc2,NULL);
    free(res);
    return 0;
}

