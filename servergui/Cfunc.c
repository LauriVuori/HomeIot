#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
void exit_signal(int sig);


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

void main(int **ar) {
    for(int i = 0; i < 5; i++) {
        **ar = 'a';
        *ar++;
    }
    signal(SIGINT, exit_signal); 
    printf("SLEEP\n");
    sleep(1);

}

void exit_signal(int sig) {
    printf("CTRL-C exit");
    exit(1);
}