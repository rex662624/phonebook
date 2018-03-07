#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_hash.h"
/*
要找的人先透過hash function看它應該收在哪個抽屜裡，如果那個抽屜裡從頭到尾都沒有表示電話簿裡根本沒有
*/
entry *findName(char lastname[], entry *table[])
{
    unsigned nHash = hash(lastname);
    entry *pHead = table[nHash];
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}
/*
經由hash function算出的index收到正確的抽屜裡（串到table[index]中）
*/
void append(char lastName[], entry *table[])
{
    unsigned nHash = hash(lastName);
    entry *e = (entry *) malloc(sizeof(entry));
    if(table[nHash]==NULL) {
        e -> pNext = NULL;
        table[nHash] = e;
    } else {
        e -> pNext = table[nHash]->pNext;
        table[nHash] -> pNext = e;
    }
    strcpy(e -> lastName, lastName);
}
/*
hash function
*/
unsigned hash(char name[])
{

//djb2
    /*
            unsigned long hash = 5381;
            int c;

            while (c = *name++)
                hash = ((hash << 5) + hash) + c; // hash * 33 + c

            return (hash%MOD);
    */

//bkdrhash
    unsigned int seed = 31;
    unsigned int hash = 0;
    while(*name)
        hash = hash * seed + (*name++);

    return (hash % MOD);

//workfunction(修課學長版本)
    /*
    	unsigned sum;
     	int i;
    	for (sum = 1, i = 0; i < 16 && name[i] > 0; i++) {
            sum = sum * name[i] - i * name [i];
        }
        return sum % MOD;
    */
}
/*
一開始就要把bucket準備好,table[0]代表第0個bucket,這裡的mod是30000代表30000個bucket
*/
void initTable(entry *table[])
{
    for(int i = 0; i < MOD; i++) {
        table[i]=NULL;
    }
}
