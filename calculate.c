#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("orig.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (!fp) {
        printf("ERROR opening input file orig.txt\n");
        exit(0);
    }
    int i = 0;
    char append[50], find[50];
    double orig_sum_a = 0.0, orig_sum_f = 0.0, orig_a, orig_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find,&orig_a, &orig_f);
        orig_sum_a += orig_a;
        orig_sum_f += orig_f;
    }
    fclose(fp);

    fp = fopen("opt.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double opt_sum_a = 0.0, opt_sum_f = 0.0, opt_a, opt_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find,&opt_a, &opt_f);
        opt_sum_a += opt_a;
        opt_sum_f += opt_f;
    }

    fp = fopen("hash.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file hash.txt\n");
            exit(0);
        }
    }
    double hash_sum_a = 0.0, hash_sum_f = 0.0, hash_a, hash_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find,&hash_a, &hash_f);
        hash_sum_a += hash_a;
        hash_sum_f += hash_f;
    }

//-----------------------------bst
    FILE *fp_bst = fopen("bst.txt", "r");
    if (!fp_bst) {
        printf("ERROR opening input file bst.txt\n");
        exit(0);
    }
    double bst_sum_a = 0.0, bst_sum_f = 0.0, bst_a, bst_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp_bst)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp_bst, "%s %s %lf %lf\n", append, find, &bst_a, &bst_f);
        bst_sum_a += bst_a;
        bst_sum_f += bst_f;
    }

//---------------------memorypool----
    FILE *fp_memorypool;
    fp_memorypool = fopen("memorypool.txt", "r");
    if (!fp_memorypool) {
        if (!fp) {
            printf("ERROR opening input file memorypool.txt\n");
            exit(0);
        }
    }
    double memorypool_sum_a = 0.0, memorypool_sum_f = 0.0, memorypool_a, memorypool_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp_memorypool)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp_memorypool, "%s %s %lf %lf\n", append, find,&memorypool_a, &memorypool_f);
        memorypool_sum_a += memorypool_a;
        memorypool_sum_f += memorypool_f;
    }
//----------------------------------smaz
    FILE *fp_smaz;
    fp_smaz = fopen("smaz.txt", "r");
    if (!fp_smaz) {
        fp_smaz = fopen("smaz.txt", "r");
        if (!fp_smaz) {
            printf("ERROR opening input file smaz.txt\n");
            exit(0);
        }
    }
    double smaz_sum_a = 0.0, smaz_sum_f = 0.0, smaz_a, smaz_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp_smaz)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp_smaz, "%s %s %lf %lf\n", append, find,&smaz_a, &smaz_f);
        smaz_sum_a += smaz_a;
        smaz_sum_f += smaz_f;
    }
//----------------------------------
    fprintf(output, "append() %lf %lf %lf %lf %lf %lf\n",orig_sum_a / 100.0, opt_sum_a / 100.0, hash_sum_a / 100.0,bst_sum_a / 100.0,memorypool_sum_a / 100.0,smaz_sum_a / 100.0);
    fprintf(output, "findName() %lf %lf %lf %lf %lf %lf", orig_sum_f / 100.0, opt_sum_f / 100.0, hash_sum_f / 100.0,bst_sum_f / 100.0,memorypool_sum_f / 100.0,smaz_sum_f / 100.0);

    fclose(output);
    fclose(fp_memorypool);
    fclose(fp_bst);
    fclose(fp_smaz)
    fclose(fp);
    return 0;
}
