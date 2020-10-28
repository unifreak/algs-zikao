#include <stdlib.h>
#include <stdio.h>

/**
 * p.65: 顺序栈
 */
#define STACKSIZE 100

typedef char DataType;

typedef struct {
    DataType data[STACKSIZE]; // 存放表结点
    int top;                  // 栈顶指针
} SeqStack;

/**
 * p.66: 置空
 */
void InitStack(SeqStack *S) {
    S->top = -1; // 元素从 0 开始存储, -1 表示空栈
}

/**
 * p.66: 判断栈空
 */
int StackEmpty(SeqStack *S) {
    return S->top == -1;
}

/**
 * p.66: 判断栈满
 */
int StackFull(SeqStack *S) {
    return S->top == STACKSIZE - 1;
}

/**
 * p.66: 进栈
 */
void Push(SeqStack *S, DataType x) {
    if (StackFull(S)) {
        printf("stack overflow\n");
    } else {
        S->top = S->top + 1;
        S->data[S->top] = x;
    }
}

/**
 * p.66: 退栈
 */
DataType Pop(SeqStack *S) {
    if (StackEmpty(S)) {
        printf("stack underflow\n");
        exit(0);
    } else {
        return S->data[S->top--];
    }
}

/**
 * p.66: 取栈顶元素 (不改变栈顶指针)
 */
DataType GetTop(SeqStack *S) {
    if (StackEmpty(S)) {
        printf("stack empty\n");
        exit(0);
    } else {
        return S->data[S->top];
    }
}

// 用例
// ===============================================================

/**
 * p.69: 检验圆括号是否匹配
 */
int Expr() {
    SeqStack S;
    DataType ch, x;
    InitStack(&S);
    ch = getchar();
    while (ch != '\n') {
        if (ch == '(') { // 遇左括号进栈
            Push(&S, ch);
        } else {
            if (ch == ')') { // 遇右括号出栈
                if (StackEmpty(&S)) {
                    return 0;
                } else {
                    x = Pop(&S);
                }
            }
        }
        ch = getchar();
    }
    if (StackEmpty(&S)) { // 最后栈空则代表匹配
        return 1;
    } else {
        return 0;
    }
}

/**
 * p.70: 字符串回文判断
 * 回文指字符串具有中心对称, 如 abcba
 */
int symmetry(char str[]) {
    SeqStack S;
    int j, k, i = 0;
    InitStack(&S);
    while (str[i] != '\0') { // 求串长度
        i++;
    }
    for (j = 0; j < i / 2; j++) { // 前一半字符入栈
        Push(&S, str[j]);
    }
    k = (i + 1) / 2; // 后一般字符在串中的起始位置
    for (j = k; j < i; j++) { // 后一半字符与栈中字符比较
        if (str[j] != Pop(&S)) {
            return 0; // 有不同字符, 即不对称
        }
    }
    return 1;
}

/**
 * p.70: 数值转换
 * 将非负的十进制整数 N 转换成 d 进制, 如 3553 转换成八进制:
 * N        N/8         N%8
 * 3553     444         1
 * 444      55          4
 * 55       6           7
 * 6        0           6
 * 结果为 6741
 * 可以看出计算过程是从低位到高位顺序产生八进制各位, 而打印输出一般从高位到低位进行, 正好与计算
 * 过程相反. 故可利用栈输出.
 */
void conversion(int N, int d) {
    SeqStack S;
    int i;
    InitStack(&S);
    while (N) {
        Push(&S, N % d);
        N = N / d;
    }
    while (!StackEmpty(&S)) {
        i = Pop(&S);
        printf("%d", i);
    }
}
