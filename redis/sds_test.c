//
// Created by fire on 2024/4/22.
//
#include <stdio.h>
#include "base.h"
#include "sds.h"

#ifndef TEST_SDS
    #define TEST_SDS 1
#endif

#if TEST_SDS==0
void TestSDS(){}
#else
void TestSDS(){
    // charPrint("hello1");
    fmtPrint("hello world");
    // printf("hello");
}
#endif

void testSdsNew(){

}