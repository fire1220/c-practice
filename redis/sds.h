//
// Created by fire on 2025/5/24.
//

#ifndef TEXTC_SDS_H
#define TEXTC_SDS_H

#define SDS_MAX_PREALLOC (1024*1024)

#include <string.h>
#include <stdlib.h>


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
sds sdscatlen(sds s, const void *t, size_t len);
sds sdscat(sds s, const char *t);
sds sdscatsds(sds s, sds t);
sds sdscpylen(sds s, const char *t, size_t len);
sds sdstrim(sds s, const char *cset);
void sdsrange(sds s, int start, int end);
void sdsclear(sds s);
int sdscmp(sds s1, sds s2);
sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count);

#endif //TEXTC_SDS_H
