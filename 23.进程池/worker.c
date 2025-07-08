#include "head.h"

int MakeWorker(const int workernum, workerData_t *workaddr){                                  
    for(int i = 0; i < workernum; ++i){
        pid_t pid = fork();
        if(pid == 0){
            while(1){
                sleep(1);
            }
        }
     workaddr[i].pid = pid;
     workaddr[i].status = FREE;
     printf("i == %d\tpid == %d\n", i, workaddr[i].pid);
    }
    return 0;
}

