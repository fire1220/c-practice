#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("hello world");
    size_t len = 1024;
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    strcpy(ptr, "hello world!");
    printf("%s\n", (char *)ptr);
    if (munmap(ptr, len) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
    return 0;
}
