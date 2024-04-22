//
// Created by fire on 2024/4/22.
//

#define fmtPrint(x) _Generic((x), \
list*:listPrint,                  \
default:printPanic)(x)

void printPanic(void *x) {}
