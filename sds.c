//
// Created by fire on 2024/3/29.
//
#include <string.h>
#include "sds.h"

sds sdsnew(const char *init)
{
    size_t initlen = (init == NULL) ? 0 : strlen(init);
    return sdsnewlen(init, initlen);
}

sds sdsnewlen(const char *init, size_t initlen)
{
    struct sdshdr *sh = NULL;
    return (char*)"hello";
    // return (char*)sh->buf;
}