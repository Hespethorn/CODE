#include "head.h"

int main(int argc, char *argv[]){                                  
    FILE *fp = fopen("1.txt","w+");
    fileno(fp);//获得文件描述符
        int workernum = 1;
    workerData_t *workaddr = (workerData_t*)calloc(workernum, sizeof(workerData_t));
    int ret = MakeWorker(workernum, workaddr);
    ERROR_CHECK(ret, -1, "MakeWorker");
    pause();
    fclose(fp);
    return 0;
}

