## 編譯方法
```
make clean 
make
```

## 執行方法
```
./run.sh
```

`run.sh`內容
```
#!/bin/bash
SEMAPHORES=$(ipcs -s | awk -v user="$USER" '$3 == user {print $2}')

if [ -z "$SEMAPHORES" ]; then
    echo "No semaphores found."
    exit 0
fi

# 遍歷所有找到的 semaphore ID，並刪除
for semid in $SEMAPHORES; do
    echo "Removing semaphore ID: $semid"
    ipcrm -s $semid
done

./p1 &
./p2 &
./p3 &
```
如果run.sh無法執行 請直接手動執行
```
./p1 &
./p2 &
./p3 &
```

## 程式新增部分
以下我針對這些問題去做解釋
1. 為何這樣設定sem的值可以保證p1先執行，然後換p2，最後換p3
  - p1一定先執行
為了保證p1一定要在p2,p3之前執行，所以我先把`sem_B`,`sem_C`的值設為0。
以下說明為何`sem_A`可以保證先被執行
考慮下面情況
    - p1先執行，由於`sem_A`的value一開始是1，故一定可以順利執行一次。
    - p2先執行，因為p2的value一開始是0，所以會被block，只有等換A執行時才會wake up B。(同理p3也是) 
  - p2 一定第二個執行
考慮下面情況
    - p1 執行，當p1執行完prinf後，會執行`V(sem_8)`，之後就算是p1先執行到`P(Sem_A)`，他也會被卡在`P(sem_A)`。唯有p3執行完才會將`sem_A`
的value做+1
    - p3執行，因為只有p1會把`sem_C`的value做增加，所以加上上面討論，第2個一定要讓p2執行(否則`sem_C`不會被釋放)。
  - p3 一定第三個執行
    - p2 執行，當p2執行完prinf後，他會將`sem_C`的vlaue做++，**注意在p2的程式中是有連續兩個`V(sem_C)`**，這樣可以保證p3一定會連續被執行兩次，當p2執行完`i++`他會被卡在`P(sem_B)`中
    - p1 執行，p1一定要等到p3連續印出兩次後，才會執行`V(sem_A)`

2. 為甚麼先執行p2或p3程式還是成功運作

- `create_sem`是由p1執行，p2和p3只是取得已創建的semaphore
- 若p2 先執行，他會卡在P(sem_B);

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
