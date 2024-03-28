#include <stdio.h>
#include "adlist.h"

int main() {
    list x = createList();
    printf("%lu", x.len);
    return 0;
}
