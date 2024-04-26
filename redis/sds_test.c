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
    // testSdsNew();
    testFreeSdsNew();
}
#endif

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
    printf("new s4\n");
    fmtPrint(&s4);
    printf("已经free后的s1\n");
    printf("pointer s1 %p\n",s1);
    fmtPrint(&s1); // 此时s1和s4值是一样的，因为s1内存回收后被s4使用了，所以回收后的地址禁止使用
}