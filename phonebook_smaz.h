#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

#include "smaz.h"

typedef struct __PHONE_INFO {
    char firstName[MAX_LAST_NAME_SIZE];
    char email[MAX_LAST_NAME_SIZE];
    char phone[10];
    char cell[10];
    char addr1[MAX_LAST_NAME_SIZE];
    char addr2[MAX_LAST_NAME_SIZE];
    char city[MAX_LAST_NAME_SIZE];
    char state[2];
    char zip[5];
} info;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_INFO *information;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif
