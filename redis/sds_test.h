//
// Created by fire on 2024/4/22.
//
#ifndef C_PRACTICE_SDS_TEST_H
#define C_PRACTICE_SDS_TEST_H

// 是否开启测试：0否1是
#ifndef TEST_SDS
#define TEST_SDS 0
#endif

#include "sds.h"

void TestSDS();
void testSdsNew();
void testFreeSdsNew();
void testSdsgrowzero();
void testSdsCat();
void testSdsCatSds();
void testSDStrim();
void testSDSrange();
void testSDScmp();
void testSDSsplitlen();


#endif //C_PRACTICE_SDS_TEST_H
