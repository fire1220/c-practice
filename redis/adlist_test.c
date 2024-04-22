//
// Created by fire on 2024/4/22.
//

// 测试文件
#include "print.h"
#include "adlist_test.h"
#include "adlist.h"
#include "sds.h"


#if TEST_AD_LIST==0
void TestAdList() {}
#else
void TestAdList() {
    testListAddNodeHead();
    testListAddNodeTail();
}
#endif

// 头部插入
void testListAddNodeHead()
{
    list *l = listCreate();
    l = listAddNodeHead(l, sdsnew("篮球1"));
    l = listAddNodeHead(l, sdsnew("足球2"));
    l = listAddNodeHead(l, sdsnew("排球3"));
    fmtPrint(l);
}

// 从尾部加入
void testListAddNodeTail()
{
    list *l = listCreate();
    l = listAddNodeTail(l, sdsnew("苹果1"));
    l = listAddNodeTail(l, sdsnew("草莓2"));
    l = listAddNodeTail(l, sdsnew("荔枝3"));
    fmtPrint(l);
}