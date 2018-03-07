#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phonebook_fuzzy.h"

entry *findName(char lastname[], entry *pHead)
{
    fuzzySearch(lastname,pHead,SIMILARITY);
    if (strcasecmp(lastname, pHead->lastName) == 0)
        return pHead;
    printf("Sorry, not found\n");
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    e -> pNext = (entry *) malloc(sizeof(entry));
    e = e -> pNext;
    strcpy(e -> lastName, lastName);
    e -> pNext = NULL;

    return e;
}


int min(int a, int b, int c)
{
    int min = 0;
    if (a <= b) {
        min = a;
    } else {
        min = b;
    }
    if (c <= min) {
        min = c;
    }
    return min;
}

int wagnerFischer(const char *s, const char *t)
{
    int len_s = strlen(s), len_t = strlen(t);
    int distance[len_s + 1][len_t + 1];

    for (int i = 0; i <= len_s; i++) {
        distance[i][0] = i;
    }
    for (int j = 0; j <= len_t; j++) {
        distance[0][j] = j;
    }

    for (int j = 1; j <= len_t; j++) {
        for (int i = 1; i <= len_s; i++) {
            if (s[i - 1] == t[j - 1])
                distance[i][j] = distance[i - 1][j - 1];
            else
                distance[i][j] = min(
                                     distance[i-1][j] + 1,
                                     distance[i][j-1] + 1,
                                     distance[i-1][j-1] + 1);
        }
    }
    return distance[len_s][len_t];
}

entry *fuzzySearch(char lastName[],	entry *pHead,int similarity)
{

    int distance;
    while (pHead != NULL) {
        distance = wagnerFischer(lastName, pHead->lastName);
        if (distance == 0) {
            printf("\n\"%s\" has found!\n\n", lastName);
            return pHead;
        }
        if (distance <= similarity) {
            printf("%s\n", pHead->lastName);
        }
        pHead = pHead->pNext;
    }

    return NULL;
}
