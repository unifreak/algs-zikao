#include <stdlib.h>
#include <stdio.h>

/**
 * p.67: 链栈
 * - 不必设置头结点
 * - 不用 top 指示栈顶位置, 栈顶即 top, 一个用于代表栈的 stacknode
 */
typedef char DataType;

typedef struct stacknode {
    DataType data;
    struct stacknode *next;
} StackNode;

typedef StackNode *LinkStack;

/**
 * p.67: 判断栈空
 */
int StackEmpty(LinkStack top) {
    return top == NULL;
}

/**
 * p.68: 进栈
 */
LinkStack Push(LinkStack top, DataType x) {
    StackNode *p;
    p = (StackNode *) malloc(sizeof(StackNode));
    p->data = x;
    p->next = top;
    top = p;
    return top;
}

/**
 * p.68: 退栈
 */
LinkStack Pop(LinkStack top, DataType *x) {
    StackNode *p = top;
    if (StackEmpty(top)) {
        printf("stack empty\n");
        exit(0);
    } else {
        *x = p->data;
        top = p->next; // 退到最终一个元素 (栈底) 时, top 值变为 NULL
        free(p);
        return top;
    }
}

/**
 * p.68: 取栈顶元素
 */
DataType GetTop(LinkStack top) {
    if (StackEmpty(top)) {
        printf("stack empty\n");
        exit(0);
    } else {
        return top->data;
    }
}

void dump(LinkStack S) {
    StackNode *p = S;
    printf("[");
    while (p != NULL) {
        printf("%c, ", p->data);
        p = p->next;
    }
    free(p);
    printf("]\n");
}

int main(void) {
    // 如何初始化一个链栈: 赋值 NULL 给它
    // 如果只写 LinkStack S; 因为没有为其分配内存, 会报 segment fault 错误
    LinkStack S = NULL;
    dump(S);

    S = Push(S, 'a'); // 调用时, 必须使用赋值保存新的栈顶, 以供后续使用
    S = Push(S, 'b');
    printf("top: %c\n", GetTop(S)); // b

    char ch, *p = &ch;
    S = Pop(S, p);
    printf("got: %c, top: %c\n", ch, GetTop(S)); // b, a
}