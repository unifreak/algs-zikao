#include "PostExp.c"

int main(void) {
    CirQueue q, *Q = &q;
    InitQueue(Q);
    CTPostExp(Q); // 输入:  9-(2+4*7)/5+3#
    printf("result is %d\n", CPostExp(Q)); // 结果: 6
}