//
// Created by fire on 2024/3/29.
//
#include <string.h>
#include "sds.h"
#include <stdlib.h>

sds sdsnew(const char *init)
{
    size_t initLen = (init == NULL) ? 0 : strlen(init);
    return sdsnewlen(init, initLen);
}

sds sdsnewlen(const char *init, size_t initLen)
{
    struct sdshdr *sh;
    if (init) {
        sh = malloc(sizeof(*sh) + initLen + 1);
    } else {
        sh = calloc(1, sizeof(*sh) + initLen + 1);
    }
    if (initLen && init) {
        memcpy(sh->buf, init, initLen);
    }
    sh->len = (int)initLen;
    sh->free = 0;
    sh->buf[initLen] = '\0';
    return (char*)sh->buf;
}