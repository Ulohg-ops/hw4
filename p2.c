#include <stdio.h>
#include "awk_sem.h"

int main() {
    int i = 0;
    int sem_B, sem_C;

    // 取得由 p1 建立的 semaphore
    sem_B = get_sem("awk_sem.h", 'B');
    sem_C = get_sem("awk_sem.h", 'C');

    while (i < 100) {
         P(sem_B);   // 等待 p1 完成
         printf("P222222222 is here\n");
         // 通知 p3 執行兩次：連續釋放兩個信號
         V(sem_C);
         V(sem_C);
         i++;
    }
    return 0;
}
