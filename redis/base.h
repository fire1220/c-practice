//
// Created by fire on 2024/4/22.
//
#ifndef C_PRACTICE_BASE_H
#define C_PRACTICE_BASE_H

#include <stdio.h>

#define fmtPrint(x) _Generic((x), \
list*:listPrint \
)(x)

static void charPrint(char *s) {
    printf("%s\n", s);
}
#endif //C_PRACTICE_BASE_H