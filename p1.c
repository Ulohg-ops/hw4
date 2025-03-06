#include <stdio.h>
#include "awk_sem.h"

int main() {
    int i = 0;
    int sem_A, sem_B, sem_C;

    sem_A = create_sem("awk_sem.h", 'A', 1); 
    sem_B = create_sem("awk_sem.h", 'B', 0);  
    sem_C = create_sem("awk_sem.h", 'C', 0);  

    while (i < 100) {
         P(sem_A); 
         printf("P1111111111 is here\n");
         V(sem_B);   // 通知 p2 可以執行
         i++;
    }
    return 0;
}
