//
// Created by fire on 2024/4/22.
//
#ifndef C_PRACTICE_BASE_H
#define C_PRACTICE_BASE_H

#include <stdio.h>
#include "adlist.h"
#include "sds.h"

#define fmtPrint(x) _Generic((x), \
list*:listPrint,                  \
sds*:sdsPrint,                    \
size_t:sizeTPrint,                \
int:intPrint,                     \
char*:charPrint)(x)

static void charPrint(const char *s)
{
    printf("%s\n", s);
}

static void sizeTPrint(const size_t i)
{
    printf("%zu\n", i);
}

static void intPrint(const int i)
{
    printf("%d\n", i);
}

static void sdsPrint(const sds *s)
{
    printf("sds struct {\n");
    printf("\t data : \"%s\"\n", *s);
    printf("\t len  : %zu\n", sdslen(*s));
    printf("\t free : %zu\n", sdsavail(*s));
    printf("}\n");
}

static void listPrint(const list *list)
{
    printf("list (%lu) {\n",  list->len);
    listNode *temp = list->head;
    for (int i = 0; i < list->len; i++) {
        printf("\t[%d] => \"%s\"", i, (sds)temp->value);
        temp = temp->next;
        if (temp == NULL) {
            printf("\n");
            break;
        }
        printf("\n");
    }
    printf("}\n");
}

#endif //C_PRACTICE_BASE_H