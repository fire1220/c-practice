#include <stdio.h>

// 使用_Generic实现泛型的最大值函数
#define max(a, b) _Generic((a) + (b), \
                            int: max_int, \
                            double: max_double)(a, b)

// 整数最大值函数
int max_int(int a, int b) {
    return (a > b) ? a : b;
}

// 浮点数最大值函数
double max_double(double a, double b) {
    return (a > b) ? a : b;
}

int main() {
    int int_result = max(10, 20);
    double double_result = max(3.14, 2.71);

    printf("Max of integers: %d\n", int_result);
    printf("Max of doubles: %lf\n", double_result);

    return 0;
}
