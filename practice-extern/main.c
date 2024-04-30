#include <stdio.h>

// 声明外部变量
extern int globalVariable;

// 声明外部函数
extern void displayGlobalVariable();

// gcc main.c helper.c -o program
int main() {
    // 使用外部变量
    globalVariable = 10;

    // 调用外部函数
    displayGlobalVariable();

    return 0;
}
