//
// Created by fire on 2024/3/29.
//

typedef char *sds;

typedef struct sdshdr{
    int len;
    int free;
    char buf[];
} sdshdr;

sds sdsnew(const char *init);
sds sdsnewlen(const char *init, size_t initlen);
