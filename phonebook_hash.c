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
    e -> pNext = table[nHash];
    if(!table[nHash]) {
        table[nHash] = e;
    } else {
        table[nHash] -> pNext = e;
    }
    strcpy(e -> lastName, lastName);
}
/*
hash function
*/
unsigned hash(char name[])
{
    unsigned sum;
    int i;
    for (sum = 1, i = 0; i < 16 && name[i] > 0; i++) {
        sum = sum * name[i] - i * name [i];
    }
    return sum % MOD;
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
