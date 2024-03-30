//
// Created by fire on 2024/3/29.
//

typedef char *sds;

typedef struct sdshdr{
    int len;
    int free;
    char buf[];
} sdshdr;

static inline int sdslen(const sds s) {
    // 内存写入是从低地址到高地址，所有第一个元素在低地址，最后一个元素在高地址
    struct sdshdr *sh = (void *)(s - sizeof(struct sdshdr));
    return sh->len;
}
static inline int sdsavail(const sds s)
{
    struct sdshdr *sh = (void *)(s - sizeof(struct sdshdr));
    return sh->free;
}

sds sdsnew(const char *init);
sds sdsnewlen(const char *init, size_t initLen);
int sdslen(const sds s);
int sdsavail(const sds s);