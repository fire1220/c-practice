#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

// 申请和释放内存案例
void mmapAndFree();
// 申请和建议释放
void mmapAndAdviseFree();

int main() {
    // mmapAndFree();
    mmapAndAdviseFree();
    return 0;
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
    printf("建议释放：ptrA\n");
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
    printf("释放：ptrB\n");
}