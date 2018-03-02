#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define MOD 1024

/* original version */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __ENTRY_DETAIL *pDetail;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

typedef struct __ENTRY_DETAIL {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detail;

entry *findName(char lastname[], entry *table[]);
void append(char lastName[], entry *table[]);
void initTable(entry *table[]);
unsigned hash(char lastName[]);
#endif
