//
// Created by fire on 2024/4/22.
//
#include <stdio.h>
#include "base.h"

#ifndef TEST_SDS
    #define TEST_SDS 1
#endif

#if TEST_SDS==0
void TestSDS(){}
#else
void TestSDS(){
    // charPrint("hello");
    // fmtPrint("hello");
    printf("hello");
}
#endif

void testSdsNew(){

}