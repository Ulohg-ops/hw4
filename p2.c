#include <stdio.h>
#include "awk_sem.h"

int main() {
    int i = 0;
    int sem_B, sem_C;

    sem_B = get_sem("awk_sem.h", 'B'); 
    printf("%d \n", sem_B);
    sem_C = get_sem("awk_sem.h", 'C');

    while (i < 100) {
         P(sem_B);
         printf("P222222222 is here\n");
         // 通知 p3 執行兩次：連續釋放兩個信號
         V(sem_C);
         V(sem_C);
         i++;
    }
    return 0;
}
