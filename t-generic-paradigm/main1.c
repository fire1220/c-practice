//
// Created by fire on 2024/4/15.
//

# include <stdio.h>

# define GENERIC_TYPE_MY(X) _Generic((X), \
int:"int" ,                      \
float:"float",                   \
double:"double",                 \
long:"long",                 \
char*:"char*",                 \
int*:"int*",                 \
default:"other"                 \
)

int test(_Generic(x, int:"int", float:"float") x) {
    printf("%d\n", x);
    return 0;
}

// 泛型
// 泛型选择表达式（generic selection expression）
int main(){
    int d = 5;
    test(d);
}