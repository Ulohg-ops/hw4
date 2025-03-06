#include <stdio.h>
#include "awk_sem.h"

int main() {
    int i = 0;
    int sem_A, sem_C;

    // 取得由 p1 建立的 semaphore
    sem_C = get_sem("awk_sem.h", 'C');
    sem_A = get_sem("awk_sem.h", 'A');

    while (i < 200) {  // 由於 p3 每週期需打印兩次，共執行 200 次
         P(sem_C);   // 等待 p2 的通知
         printf("P3333333 is here\n");
         // 每兩次打印後（即當 i 為奇數時）通知 p1開始下一週期
         if (i & 1) {
             V(sem_A);
         }
         i++;
    }
    return 0;
}
