//
// Created by fire on 2024/3/28.
//

#include <stdlib.h>
#include "adlist.h"

list createList(void)
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

