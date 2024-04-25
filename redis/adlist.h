//
// Created by fire on 2024/3/28.
//
#ifndef C_PRACTICE_ADLIST_H
#define C_PRACTICE_ADLIST_H

#define AL_START_HEAD 0
#define AL_START_TAIL 1

typedef struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode;

typedef struct list {
    struct listNode *head;
    struct listNode *tail;
    unsigned long len;

    void *(*dup)(void *ptr);

    void (*free)(void *ptr);

    int (*match)(void *ptr, void *key);
} list;

typedef struct listIter {
    struct listNode *next; // 当前好迭代的节点
    int direction;         // 迭代的方向
} listIter;


list *listCreate(void);

list *listAddNodeHead(list *list, void *value);

list *listAddNodeTail(list *list, void *value);

list *listInsertNode(list *list, listNode *old_node, void *value, int after);

void listDelNode(list *list, listNode *node);

listIter *listGetIterator(list *list, int direction);

listNode *listNext(listIter *iter);

void listReleaseIterator(listIter *iter);

list *listDup(list *orig);

listNode *listSearchKey(list *list, void *key);

listNode *listIndex(list *list, long index);

void listRewind(list *list, listIter *li);

void listRewindTail(list *list, listIter *li);

void listRotate(list *list);

#endif //C_PRACTICE_ADLIST_H
