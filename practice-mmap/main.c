#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t len = 1024;
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap1");
        exit(EXIT_FAILURE);
    }
    printf("%p\n", (char *)ptr);
    strcpy(ptr, "hello world!");
    printf("%s\n", (char *)ptr);
    printf("%p\n", (char *)ptr);
    if (munmap(ptr, len) == -1) {
        perror("munmap2");
        exit(EXIT_FAILURE);
    }
    void *p = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
    printf("%p\n", (char *)p);
    strcpy(p, "hello world!!");
    printf("%s\n", (char *)ptr);
    printf("%p\n", (char *)p);
    if ((munmap(p, len)) == -1) {
        perror("munmap3");
        exit(EXIT_FAILURE);
    }
    return 0;
}
