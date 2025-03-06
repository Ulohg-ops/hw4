#include <stdio.h>
#include "awk_sem.h"

int main() {
    int i = 0;
    int sem_A, sem_B, sem_C;

    // p1 為系統初始化者，創建所有 semaphore
    sem_A = create_sem("awk_sem.h", 'A', 1);  // p1 初始可執行
    sem_B = create_sem("awk_sem.h", 'B', 0);  // p2 初始等待
    sem_C = create_sem("awk_sem.h", 'C', 0);  // p3 初始等待

    while (i < 100) {
         P(sem_A);   // 等待信號，確保 p1 的執行權
         printf("P1111111111 is here\n");
         V(sem_B);   // 通知 p2 可以執行
         i++;
    }
    return 0;
}
