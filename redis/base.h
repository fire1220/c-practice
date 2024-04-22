//
// Created by fire on 2024/4/22.
//
#ifndef C_PRACTICE_BASE_H
#define C_PRACTICE_BASE_H

#include <stdio.h>
#include "adlist.h"
#include "sds.h"
typedef struct people {
    int age;
    char *name ;
}people;

#define fmtPrint(x) _Generic((x), \
list*:listPrint,                  \
sds*:sdsPrint,                    \
size_t:sizeTPrint,                \
int:intPrint,                     \
char*:charPrint)(x)

static void charPrint(char *s)
{
    printf("%s\n", s);
}

static void sizeTPrint(size_t i)
{
    printf("%zu\n", i);
}

static void intPrint(int i)
{
    printf("%d\n", i);
}

#endif //C_PRACTICE_BASE_H