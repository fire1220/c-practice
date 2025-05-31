//
// Created by fire on 2024/4/22.
//
#include <stdio.h>
#include "print.h"
#include "sds.h"
#include "sds_test.h"

#if TEST_SDS==0
void TestSDS(){}
#else
void TestSDS(){
    testSDSsplitlen();
    // testSDScmp();
    // testSDSrange();
    // testSDStrim();
    // testSdsCatSds();
    // testSdsCat();
    //testSdsgrowzero();
    // testSdsNew();
    // testFreeSdsNew();
}
#endif

void testSDSsplitlen(){
    const char *s = "he llo wo rld";
    const char *sep = " ";
    int count;
    sds *st = sdssplitlen(s, strlen(s), sep, strlen(sep), &count);
    if (st == NULL) {
        printf("什么都没有");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("%s,%zu,%zu\n", st[i], sdslen(st[i]), sdsvail(st[i]));
    }
}

void testSDScmp(){
    sds s1 = sdsnew("hello wo");
    printf("%s,%zu,%zu\n", s1, sdslen(s1), sdsvail(s1));

    sds s2 = sdsnew("hello world");
    printf("%s,%zu,%zu\n", s2, sdslen(s2), sdsvail(s2));

    int cmp = sdscmp(s1, s2);
    printf("%d\n", cmp);
}

void testSDSrange(){
    sds s = sdsnew("hello world");
    printf("%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));

    s = sdsnew("hello world");
    sdsrange(s, 0, -1);
    printf("0, -1:%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));

    s = sdsnew("hello world");
    sdsrange(s, 0, 3);
    printf("0, 3:%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));

    s = sdsnew("hello world");
    sdsrange(s, 2, 3);
    printf("2, 3:%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));

    s = sdsnew("hello world");
    sdsrange(s, 2, -1);
    printf("2, -1:%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));

    s = sdsnew("hello world");
    sdsrange(s, 3, -3);
    printf("3, -3:%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));

    s = sdsnew("hello world");
    sdsrange(s, -3, -1);
    printf("-3, -1:%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));

    s = sdsnew("hello world");
    sdsrange(s, -3, 9);
    printf("-3, 9:%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));

    s = sdsnew("hello world");
    sdsrange(s, 15, -1);
    printf("15, -1:%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));

    s = sdsnew("hello world");
    sdsrange(s, 0, 15);
    printf("0, 15:%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));
}

void testSDStrim(){
    sds s = sdsnew("AA...AA.a.aa.aHelloWorld     :::");
    s = sdstrim(s,"A. :");
    printf("%s\n", s);
}

void testSdsCatSds(){
    sds s1 = sdsnew("hello");
    printf("%s,%zu,%zu\n", s1, sdslen(s1), sdsvail(s1));
    sds s2 = sdsnew(" world");
    printf("%s,%zu,%zu\n", s2, sdslen(s2), sdsvail(s2));
    sds s = sdscatsds(s1, s2);
    printf("%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));
}

void testSdsCat(){
    sds s = sdsnew("hello");
    printf("%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));
    s = sdscat(s, " world");
    printf("%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));
}

void testSdsgrowzero(){
    sds s = sdsnew("hello world");
    printf("%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));
    s = sdsgrowzero(s, 20);
    printf("%s,%zu,%zu\n", s, sdslen(s), sdsvail(s));
}

void testSdsNew(){
    sds s1 = sdsnew("hello world old");
    printf("pointer %p\n",s1);
    fmtPrint(&s1);
    sds s2 = sdsdup(s1);
    printf("pointer %p\n",s2);
    fmtPrint(&s2);
    sds s3 = sdsempty();
    fmtPrint(&s3);
    printf("free s1\n");
    sdsfree(s1);
    printf("s1\n");
    fmtPrint(&s1);
    sds s4 = sdsnew("hello world new");
    printf("new s4\n");
    fmtPrint(&s4);
    printf("s1\n");
    fmtPrint(&s1); // 此时s1和s4值是一样的，因为s1内存回收后被s4使用了，所以回收后的地址禁止使用
}

void testFreeSdsNew(){
    sds s1 = sdsnew("hello world old"); // 新建s1
    printf("pointer s1 %p\n",s1);
    fmtPrint(&s1);
    sds s2 = sdsdup(s1);                // 复制s1到s2里
    printf("pointer s2 %p\n",s2);
    fmtPrint(&s2);
    printf("free s1\n");
    sdsfree(s1);                        // free s1
    printf("free后s1\n");
    fmtPrint(&s1);
    sds s4 = sdsnew("hello world new"); // 新建s4
    printf("pointer s4 %p\n",s1);           // s4的内存地址和s1是相同，说明 mallic 把地址重新分配给s4了
    printf("new s4\n");
    fmtPrint(&s4);
    printf("已经free后的s1\n");
    printf("pointer s1 %p\n",s1);
    fmtPrint(&s1); // 此时s1和s4值是一样的，因为s1内存回收后被s4使用了，所以回收后的地址禁止使用
}