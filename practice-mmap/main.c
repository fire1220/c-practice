#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

void mmapAndFree();

int main() {
    mmapAndFree();
    return 0;
}

// 申请和释放内存案例
void mmapAndFree(){
    size_t len = 1024;
    // 申请内存
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap1");
        exit(EXIT_FAILURE);
    }
    printf("申请：ptr\n");
    printf("%p\n", (char *)ptr);
    strcpy(ptr, "hello world!");
    printf("%s\n", (char *)ptr);
    // 释放内存
    if (munmap(ptr, len) == -1) {
        perror("munmap2");
        exit(EXIT_FAILURE);
    }
    printf("释放：ptr\n");
    // 申请内存
    void *p = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
    printf("申请：p\n");
    printf("%p\n", (char *)ptr);
    strcpy(p, "hello world!!");
    printf("%s\n", (char *)ptr);
    // 释放内存
    if ((munmap(p, len)) == -1) {
        perror("munmap3");
        exit(EXIT_FAILURE);
    }
    printf("释放：p\n");
}
