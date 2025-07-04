//
// Created by fire on 2025/5/24.
//


#include "sds.h"

sds sdsnew(const char* init) {
    size_t initlen = (init == NULL) ? 0 : strlen(init);
    return sdsnewlen(init, initlen);
};

sds sdsnewlen(const char *init, size_t initlen) {
    sdshdr *sh;
    if (init) {
        sh = malloc(sizeof(*sh) + initlen + 1);
    } else {
        sh = calloc(1, sizeof(*sh) + initlen + 1);
    }
    if (sh == NULL) return NULL;
    if (init && initlen > 0) {
        memcpy(sh->buf, init, initlen);
    }
    sh->len = (int)initlen;
    sh->free = 0;
    sh->buf[initlen] = '\0';
    return (sds)sh->buf;
}

sds sdsempty(void){
    return sdsnewlen("", 0);
}

sds sdsdup(sds s) {
    return sdsnewlen(s, sdslen(s));
}

void sdsfree(sds s){
    if (s == NULL) return;
    free(s - sizeof(sdshdr));
}

sds sdsgrowzero(sds s, size_t len){
    sdshdr *sh = (sdshdr*)(s - sizeof(sdshdr));
    if (len <= sh->len) return s;
    s = sdsMakeRoomFor(s, len-sh->len);
    if (s == NULL) return NULL;
    sh = (sdshdr*)(s - sizeof(sdshdr));
    memset(s+sh->len, 0, len-sh->len+1);
    size_t totlen = sh->len + sh->free;
    sh->len = (int)len;
    sh->free = (int)totlen - sh->len;
    return s;
}

sds sdsMakeRoomFor(sds s, size_t addlen){
    sdshdr *sh, *newsh;
    sh = (sdshdr*)(s-sizeof(sdshdr));
    if (sh->free >= addlen)  return s;
    size_t len = sdslen(s);
    size_t newLen = len+addlen;
    if (addlen <= SDS_MAX_PREALLOC) {
        newLen *= 2;
    } else {
        newLen += SDS_MAX_PREALLOC;
    }
    newsh = realloc(sh, sizeof(*newsh) + newLen + 1);
    if (newsh == NULL) return NULL;
    newsh->free = (int)(newLen - len);
    return (sds)newsh->buf;
}

sds sdscatlen(sds s, const void *t, size_t len) {
    sdshdr *sh;
    size_t curlen = sdslen(s);

    s = sdsMakeRoomFor(s, len);
    sh = (sdshdr*)(s- sizeof(sdshdr));
    memcpy(s+curlen, t, len);
    sh->len = (int)(len + curlen);
    sh->free = sh->free - (int)len;
    sh->buf[len + curlen] = '\0';
    return s;
}

sds sdscat(sds s, const char *t){
    return sdscatlen(s, t, strlen(t));
}

sds sdscatsds(sds s, sds t) {
    return sdscatlen(s, t, sdslen(t));
}

sds sdscpylen(sds s, const char *t, size_t len){
    sdshdr *sh = (void *)(s - sizeof(sdshdr));
    if (sh->len + sh->free < len) {
        s = sdsMakeRoomFor(s, len - sh->len);
        if (s == NULL) return NULL;
        sh = (void *)(s - sizeof(sdshdr));
    }
    int totlen = sh->len = sh->free;
    memcpy(sh->buf, t, len);
    sh->len = (int)len;
    sh->free = totlen - (int)len;
    sh->buf[len] = '\0';
    return (sds)sh->buf;
}

sds sdscpy(sds s, const char *t) {
    return sdscpylen(s, t,strlen(t));
}

sds sdstrim(sds s, const char *cset) {
    sdshdr *sh = (void *)(s - sizeof(sdshdr));
    char *sp, *ep, *start, *end;
    sp = start = s;
    end = ep = s + sh->len;
    while (sp <= end && strchr(cset, *sp)) sp++;
    while (ep > start && strchr(cset, *ep)) ep--;
    size_t len = (sp > ep) ? 0 : (ep - sp) + 1;
    if (sp != s) memcpy(s, sp, len);
    sh->free = sh->free + sh->len - (int)len;
    sh->len = (int)len;
    sh->buf[len] = '\0';
    return s;
}

void sdsrange(sds s, int start, int end) {
    sdshdr *sh = (void *)(s - sizeof(sdshdr));
    if (sh->len == 0) return;
    if (start < 0) {
        start = sh->len + start;
        if (start < 0) start = 0;
    }
    if (end < 0) {
        end = sh->len + end;
        if (end < 0) end = 0;
    }
    if (end >= sh->len) end = sh->len - 1;
    int len = (start > end) ? 0 : end - start + 1;
    if (start && len) memcpy(s, s + start, len);
    sh->free = sh->free + sh->len - len;
    sh->len = len;
    sh->buf[len] = '\0';
}

void sdsclear(sds s) {
    sdshdr *sh = (void *)(s - sizeof(sdshdr));
    sh->free += sh->len;
    sh->len = 0;
    sh->buf[0] = '\0';
}

int sdscmp(sds s1, sds s2) {
    int l1, l2, minlen, cmp;
    l1 = sdslen(s1);
    l2 = sdslen(s2);
    minlen = l1 <= l2 ? l1 : l2;
    cmp = memcmp(s1, s2, minlen);
    if (cmp == 0) {
        return l1 - l2;
    }
    return cmp;
}

sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count) {
    int elements = 0, slots = 5 ,start = 0;
    sds *tokens;
    if (len < 0 || seplen <= 0) return NULL;
    tokens = malloc(sizeof(sds)*slots);
    if (tokens == NULL) return NULL;
    if (len == 0) {
        *count = 0;
        return tokens;
    }

    for (int i=0; i < len - seplen - 1; i++) {
        if (elements+2 > slots) {
            sds *newtokens;
            slots *= 2;
            newtokens = realloc(tokens, sizeof(sds)*slots);
            if (newtokens == NULL) goto cleanup;
            tokens = newtokens;
        }
        if (seplen == 1 && *(s+i) == sep[0] || memcmp(s+i, sep, seplen) == 0) {
            tokens[elements] = sdsnewlen(s+start, i-start);
            if (tokens[elements] == NULL) goto cleanup;
            elements++;
            start = i + seplen;
            i = i+seplen-1;
        }
    }
    tokens[elements] = sdsnewlen(s+start, len-start);
    if (tokens[elements] == NULL) goto cleanup;
    elements++;
    *count = elements;
    return tokens;

cleanup:
    {
        for (int i=0; i<elements; i++) sdsfree(tokens[i]);
        free(tokens);
        *count = 0;
        return NULL;
    }
}

void sdsfreesplitres(sds *tokens, int count) {
    if (!tokens) return;
    while(count--)
        sdsfree(tokens[count]);
    free(tokens);
}

void sdstolower(sds s) {
    if (s == NULL) return;
    int len = sdslen(s);
    for (int i = 0; i < len; i++) s[i] = tolower(s[i]);
}

void sdstoupper(sds s) {
    if (s == NULL) return;
    int len = sdslen(s);
    for (int i = 0; i < len; i++) s[i] = toupper(s[i]);
}