//
// Created by fire on 2024/3/28.
// 2021.1
// 2023.1.6
//

#include <stdlib.h>
#include "adlist.h"
#include <stdio.h>
#include "sds.h"


list *listCreate(void) {
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

// 释放列表内存
void listRelease(list *list) {
    listNode *current, *next;
    unsigned long len = list->len;
    current = list->head;
    while (len--) {
        next = current->next;
        if (list->free) {
            list->free(current->value);
        } else {
            free(current->value);
        }
        free(current);
        current = next;
    }
    free(list);
}

// 链表头位置插入
list *listAddNodeHead(struct list *list, void *value) {
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

// 链表尾部加入
list *listAddNodeTail(list *list, void *value) {
    listNode *node;
    if ((node = malloc(sizeof(listNode))) == NULL) {
        return NULL;
    }
    node->value = value;
    if (list->len == 0) {
        node->next = node->prev = NULL;
        list->head = list->tail = node;
    } else {
        node->next = NULL;
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->len++;
    return list;
}

list *listInsertNode(list *list, listNode *old_node, void *value, int after) {
    listNode *node;
    if ((node = malloc(sizeof(*node))) == NULL) {
        return NULL;
    }
    node->value = value;
    // 前面插入
    if (after) {
        node->prev = old_node;
        node->next = old_node->next;
        if (list->tail == old_node) {
            list->tail = node;
        }
    } else {
        node->prev = old_node->prev;
        node->next = old_node;
        if (list->head == old_node) {
            list->head = node;
        }
    }
    if (node->prev != NULL) {
        node->prev->next = node;
    }
    if (node->next != NULL) {
        node->next->prev = node;
    }
    list->len++;
    return list;
}

void listDelNode(list *list, listNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    list->len--;
}

listIter *listGetIterator(list *list, int direction) {
    listIter *iter;
    if ((iter = malloc(sizeof(*iter))) == NULL) {
        return NULL;
    }
    if (direction == AL_START_HEAD) {
        iter->next = list->head;
    } else {
        iter->next = list->tail;
    }
    iter->direction = direction;
    return iter;
}

listNode *listNext(listIter *iter) {
    listNode *current = iter->next;
    if (current != NULL) {
        if (iter->direction == AL_START_HEAD) {
            iter->next = current->next;
        } else {
            iter->next = current->prev;
        }
    }
    return current;
}

void listReleaseIterator(listIter *iter) {
    free(iter);
}