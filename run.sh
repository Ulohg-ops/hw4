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