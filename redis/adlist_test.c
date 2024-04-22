//
// Created by fire on 2024/4/22.
//

// 测试文件
#include "adlist.h"
#include "sds.h"

#ifndef TEST_AD_LIST
    #define TEST_AD_LIST 1
#endif

#if TEST_AD_LIST==0
void TestAdList() {
    printf("测试已经关闭了");
}
#else
void TestAdList() {
    list *l = listCreate();
    l = listAddNodeHead(l, sdsnew("篮球1"));
    l = listAddNodeHead(l, sdsnew("足球2"));

    listPrint(l);
}
#endif
