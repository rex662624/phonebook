#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

#if defined(POOL)
    init_memory_pool(sizeof(entry) * 350000);
#endif

    /* build the entry */
    entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;



#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif

#if defined(HASH)//method1:hash
    entry *table[MOD];
    initTable(table);
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        append(line, table);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);
#elif defined (BST)//method2:BST
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        e = append(line, e);
    }
    /* Build BST from a sorted linked-list */
    treeNode *root = BuildBST(&pHead, Length(pHead));
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);
#else
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        e = append(line, e);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);
#endif

    /* close file as soon as possible */
    fclose(fp);

    e = pHead;

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
	//char input[MAX_LAST_NAME_SIZE] = "arriba";
    e = pHead;
    /*
        assert(findName(input, e) &&
               "Did you implement findName() in " IMPL "?");
        assert(0 == strcmp(findName(input, e)->lastName, "zyxel"));
    */
#if defined (FUZZY)
printf("please enter the last name you want search: ");
scanf("%s",input);
printf("-------------------\n");
#endif

#if defined (SMAZ)
    char input_compressed[100];
    memset(input_compressed,sizeof(input_compressed),'\0');
	smaz_compress(input, strlen(input), input_compressed, sizeof(input_compressed));
#endif

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif

    /* compute the execution time */

#if defined(HASH)
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, table);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
#elif defined(BST)

    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, root);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
#elif defined(SMAZ)
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input_compressed,e);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
#else
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, e);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
#endif

//--------------------------------output
    FILE *output;
#if defined(OPT)
    output = fopen("opt.txt", "a");
#elif defined(HASH)
    output = fopen("hash.txt", "a");
#elif defined(BST)
    output = fopen("bst.txt", "a");
#elif defined(POOL)
    output = fopen("memorypool.txt", "a");
#elif defined(SMAZ)
	output = fopen("smaz.txt","a");
#else
    output = fopen("orig.txt", "a");
#endif
//-------------------------------------
    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);

#if defined(POOL)
    free_memory_pool();
#else
    if(pHead!=NULL) {
        if (pHead->pNext) free(pHead->pNext);
        free(pHead);
    }
#endif
    return 0;
}
