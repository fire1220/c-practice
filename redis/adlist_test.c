//
// Created by fire on 2024/4/22.
//
#include <stdio.h>
#include "adlist_test.h"
#include "adlist.h"
#include "sds.h"

#ifndef TEST_AD_LIST
#define TEST_AD_LIST 1
#endif


#if TEST_AD_LIST==0
void TestAdList(){
    printf("没有启动测试");
}
#else
void TestAdList(){
    list *l = listCreate();
    l = listAddNodeHead(l, sdsnew("篮球1"));
    l = listAddNodeHead(l, sdsnew("足球2"));
    listPrint(l);
}
#endif