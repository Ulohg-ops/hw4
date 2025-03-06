## 編譯方法
```
make clean 
make
```

## 執行方法

法1
```
./p1 &
./p2 &
./p3 &
```
法2
```
./run.sh
```


## 程式新增部分
以下我針對這些問題去做解釋
1. 為何這樣設定sem的值可以保證A先執行，然後換B，最後換C

這樣設定可以保證`sem_A`一定要在`sem_B`,`sem_C`之前執行，所以把`sem_B`,`sem_C`的值設為0。
考慮下面情況
1. `sem_A`先執行，由於`sem_A`的value一開始是1，故一定可以順利執行一次。
2. `sem_B`先執行，因為`sem_B`的value一開始是0，所以會被block，只有等換A執行時才會wake up B。(同理C也是) 

當A執行完prinf後




### p1
```c
    int sem_A, sem_B, sem_C;
    sem_A = create_sem("awk_sem.h", 'A', 1);  
    sem_B = create_sem("awk_sem.h", 'B', 0);  
    sem_C = create_sem("awk_sem.h", 'C', 0);  

    while (i < 100) {
         P(sem_A);   
         printf("P1111111111 is here\n");
         V(sem_B);  
         i++;
    }

```

### p2
```c
    int sem_B, sem_C;

    sem_B = get_sem("awk_sem.h", 'B');
    sem_C = get_sem("awk_sem.h", 'C');

    while (i < 100) {
         P(sem_B);
         printf("P222222222 is here\n");
         V(sem_C);
         V(sem_C);
         i++;
    }
```

### p3
```c
    int i = 0;
    int sem_A, sem_C;

    sem_C = get_sem("awk_sem.h", 'C');
    sem_A = get_sem("awk_sem.h", 'A');

    while (i < 200) {  // 由於 p3 每週期需打印兩次，共執行 200 次
         P(sem_C);
         printf("P3333333 is here\n");
         // 每兩次打印後（即當 i 為奇數時）通知 p1開始下一週期
         if (i & 1) {
             V(sem_A);
         }
         i++;
    }

```
