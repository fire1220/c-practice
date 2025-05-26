//
// Created by fire on 2025/5/24.
//

#ifndef TEXTC_SDS_H
#define TEXTC_SDS_H

#define SDS_MAX_PREALLOC (1024*1024)

#include <string.h>

typedef char* sds;
typedef struct {
    int len;
    int free;
    char buf[];
}sdshdr;
static inline size_t sdslen(sds s) {
    sdshdr *sh = (void *)(s - sizeof(sdshdr));
    return sh->len;
}
static inline size_t sdsvail(sds s) {
    sdshdr *sh = (sdshdr*)(s - sizeof(sdshdr));
    return sh->free;
}
sds sdsnew(const char* str);
sds sdsnewlen(const char *init, size_t initlen);
sds sdsempty(void);
size_t sdslen(sds s);
sds sdsdup(sds s);
void sdsfree(sds s);
size_t sdsvail(sds s);
sds sdsgrowzero(sds s, size_t len);
sds sdsMakeRoomFor(sds s, size_t addlen);

#endif //TEXTC_SDS_H
