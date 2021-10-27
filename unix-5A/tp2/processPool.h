#ifndef __PROCESS_POOL_H__
#define __PROCESS_POOL_H__

#include <sys/types.h>

typedef struct {
    size_t capacity;
    size_t size;
    pid_t* pids;
} processPool;

processPool* newProcessPool(size_t capacity);
void deleteProcessPool(processPool* pp);
int reserveProcessPoolSlot(processPool* pp);
void waitForProcessesInPool(processPool* pp);

#endif