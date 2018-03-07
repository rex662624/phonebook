#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define SIMILARITY 2
#define MAX_LAST_NAME_SIZE 16

typedef struct __OTHER_INFO {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} otherInfo;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    otherInfo *detail;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;


// fuzzy search
entry *fuzzySearch(char lastName[],	entry *pHead,int similarity);
int min(int a, int b, int c);
int wagnerFischer(const char *s, const char *t);

#endif
