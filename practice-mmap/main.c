#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// 申请和释放内存案例
void mmapAndFree();
// 申请和建议释放
void mmapAndAdviseFree();
// 申请大内存并添加大量的数据
void mmapAdd();

void mmapM();

int main() {
    // mmapAndFree();
    // mmapAndAdviseFree();
    mmapM();
    return 0;
}

void mmapM() {
    size_t len = 10240;
    // 申请内存
    void *ptrA = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (ptrA == MAP_FAILED) {
        perror("mmap1");
        exit(EXIT_FAILURE);
    }
    madvise(ptrA, 1024, MADV_HUGEPAGE);
    printf("申请：ptrA\n");
    printf("%p\n", (char *)ptrA);
    strcpy(ptrA, "hello world!");
    printf("%s\n", (char *)ptrA);
    // 释放内存
    if (munmap(ptrA, len) == -1) {
        perror("munmap2");
        exit(EXIT_FAILURE);
    }
    printf("释放：ptrA\n");
    sleep(100);
}

// 申请和释放内存案例
void mmapAndFree(){
    size_t len = 1024;
    // 申请内存
    void *ptrA = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (ptrA == MAP_FAILED) {
        perror("mmap1");
        exit(EXIT_FAILURE);
    }
    printf("申请：ptrA\n");
    printf("%p\n", (char *)ptrA);
    strcpy(ptrA, "hello world!");
    printf("%s\n", (char *)ptrA);
    // 释放内存
    if (munmap(ptrA, len) == -1) {
        perror("munmap2");
        exit(EXIT_FAILURE);
    }
    printf("释放：ptrA\n");
    // 申请内存
    void *ptrB = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
    printf("申请：ptrB\n");
    printf("%p\n", (char *)ptrB);
    strcpy(ptrB, "hello world!!");
    printf("%s\n", (char *)ptrB);
    // 释放内存
    if ((munmap(ptrB, len)) == -1) {
        perror("munmap3");
        exit(EXIT_FAILURE);
    }
    printf("释放：ptrB\n");
}

// 申请和建议释放内存
// 建议释放后，内存是否释放有操作系统控制，即便释放后也可以继续使用，使用时系统会自动映射上，好处是内存地址没有变更
void mmapAndAdviseFree(){
    size_t len = 1024;
    // 申请内存
    void *ptrA = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (ptrA == MAP_FAILED) {
        perror("mmap1");
        exit(EXIT_FAILURE);
    }
    printf("申请：ptrA\n");
    printf("%p\n", (char *)ptrA);
    strcpy(ptrA, "hello world!");
    printf("%s\n", (char *)ptrA);
    // 建议释放内存
    if (madvise(ptrA, len, MADV_DONTNEED) == -1) {
        perror("madvise2");
        exit(EXIT_FAILURE);
    }
    printf("建议释放：ptrA\n\n");

    // 申请内存
    void *ptrB = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
    printf("申请：ptrB\n");
    printf("%p\n", (char *)ptrB);
    strcpy(ptrB, "hello world!!!");
    printf("%s\n", (char *)ptrB);
    // 释放内存
    if ((munmap(ptrB, len)) == -1) {
        perror("munmap3");
        exit(EXIT_FAILURE);
    }
    printf("释放：ptrB\n\n");

    // 调用其他方法消耗内存
    printf("调用其他方法消耗内存-Begin\n");
    for (int i = 0; i < 10000; i++) {
        mmapAdd();
    }
    printf("调用其他方法消耗内存-End\n");

    printf("ptrA地址,并重新赋值\n");
    printf("%p\n", (char *)ptrA);
    printf("old：%s\n", (char *)ptrA);
    strcpy(ptrA, "hello world!!");
    printf("new：%s\n", (char *)ptrA);
}

// 申请大内存并添加大量的数据
void mmapAdd(){
    size_t len = 10240000;
    // 申请内存
    void *ptrA = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (ptrA == MAP_FAILED) {
        perror("mmap1");
        exit(EXIT_FAILURE);
    }
    printf("申请：ptrA\n");
    printf("%p\n", (char *)ptrA);
    strcpy(ptrA, "hello world!");
    for (int i = 0; i < 10000; i++) {
        strcat(ptrA, "hello world!");
    }
    // printf("%s\n", (char *)ptrA);
}