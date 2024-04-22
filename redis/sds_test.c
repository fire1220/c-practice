//
// Created by fire on 2024/4/22.
//
#include <stdio.h>
#include "base.h"
#include "sds.h"
#include "sds_test.h"
#include <stdlib.h>

#ifndef TEST_SDS
    #define TEST_SDS 1
#endif

#if TEST_SDS==0
void TestSDS(){}
#else
void TestSDS(){
    testSdsNew();
}
#endif

void testSdsNew(){
    sds s1 = sdsnew("hello world new");
    printf("pointer %p\n",s1);
    fmtPrint(&s1);
    sds s2 = sdsdup(s1);
    printf("pointer %p\n",s2);
    fmtPrint(&s2);
    sds s3 = sdsempty();
    fmtPrint(&s3);
}