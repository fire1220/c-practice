#include <stdio.h>
#include "adlist.h"
#include "sds.h"

int main() {
    // list *x = listCreate();
    // x = listAddNodeHead(x, "sdfs");
    // listPrint(x);
    sds s = sdsnew("hello world");
    printf("%s\n", s);
    printf("%s\n", );

    return 0;
}
