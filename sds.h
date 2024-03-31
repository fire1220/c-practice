//
// Created by fire on 2024/3/29.
//

typedef char *sds;

typedef struct sdshdr{
    int len;
    int free;
    char buf[];
} sdshdr;

static inline size_t sdslen(const sds s) {
    // 内存写入是从低地址到高地址，所有第一个元素在低地址，最后一个元素在高地址
    struct sdshdr *sh = (void *)(s - sizeof(struct sdshdr));
    return sh->len;
}
static inline size_t sdsavail(const sds s)
{
    struct sdshdr *sh = (void *)(s - sizeof(struct sdshdr));
    return sh->free;
}

sds sdsnew(const char *init);
sds sdsnewlen(const char *init, size_t initLen);
sds sdsempty(void);
size_t sdslen(const sds s);
sds sdsdup(const sds s);
size_t sdsavail(const sds s);
void sdsfree(sds s);