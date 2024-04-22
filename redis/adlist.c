//
// Created by fire on 2024/3/28.
// 2021.1
// 2023.1.6
//

#include <stdlib.h>
#include "adlist.h"
#include <stdio.h>
#include "sds.h"

char *listPrint(list *list)
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
    return NULL;
}

list *listCreate(void)
{
    list *list;
    if ((list = malloc(sizeof(*list))) == NULL)
        return NULL;
    list->len = 0;
    list->head = list->tail = NULL;
    list->dup = NULL;
    list->free = NULL;
    list->match = NULL;
    return list;
}

list *listAddNodeHead(struct list *list, void *value)
{
    listNode *node;
    if ((node = malloc(sizeof(*node))) == NULL) {
        return NULL;
    }
    node->value = value;
    if (list->len == 0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->prev = NULL;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->len++;
    return list;
}