#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
void exit_signal(int sig);


void print(int arr[],int flag[]) {
    while(flag[0] == 1) {
        printf("C PRINT\n");
        for (int i = 0; i < 3; i++) {
            printf("<%d>\n", arr[i]);
            arr[i] += 10;
        }
        printf("C PRINT END\n");
        sleep(2);
    }
}

int test(int **ar,int *lens,int n_ar){
    int ii,jj,kk;
    for (ii=0;ii<n_ar;ii++){
        for (jj=0;jj<lens[ii];jj++){
            printf("%d\t",ar[ii][jj]);
        }  
        printf("\n");
        fflush(stdout);
    }
    return 0;
}

void main(int arr[]) {
    printf("%d", arr[0]);
    signal(SIGINT, exit_signal); 
    printf("SLEEP\n");
    sleep(1);

}

void exit_signal(int sig) {
    printf("CTRL-C exit");
    exit(1);
}