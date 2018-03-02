#include <stdlib.h>
#include <string.h>

#include "phonebook_memorypool.h"

static memory_pool *pool = NULL;

//---------memory pool----------------------
memory_pool *pool_init(int size)
{
    memory_pool *pool = (memory_pool *) malloc(sizeof(memory_pool));

    pool->begin = pool->next = (char *) calloc(1, size);
    pool->end = pool->begin + size;

    return pool;
}

void *pool_alloc(memory_pool *pool, int size)
{
    if (pool->end - pool->next < size)
        return NULL;

    void *result = pool->next;
    pool->next += size;

    return result;
}

void pool_free(memory_pool *pool)
{
 	
   	free(pool->begin);
	free(pool);
	
}



//---------opt.c----------------------------
void init_memory_pool(int size)
{
    pool = pool_init(size);
}

void free_memory_pool(void)
{
    pool_free(pool);
}

entry *findName(char lastname[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    e->pNext = (entry *) pool_alloc(pool, sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    e->pDetail = NULL;

    return e;
}
