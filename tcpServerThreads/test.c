#include <stdio.h>

int main(void) {
    int test[5] = {1,0,1,1,1};
    int i = 0;
    while (test[i] != 0){
        i++;
    } 
    printf("%d", i);
}