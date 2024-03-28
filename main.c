#include <stdio.h>
#include "adlist.h"

int main() {
    list *x = listCreate();
    printf("%lu\n", x->len);
    return 0;
}
