#include <stdlib.h>
#include <stdio.h>

// p.80: 循环链队列
// - 只设指向队尾结点的指针 rear, 不设头指针
// - rear->next 始终指向头结点
// @todo: 测试用例不通过
// ===============================================================

typedef char DataType;

typedef struct queuenode {
    DataType data;
    struct queuenode *next;
} QueueNode;

/**
 * p.80: 初始化空队列
 */
QueueNode *InitQueue(QueueNode *rear) {
    rear = (QueueNode *) malloc(sizeof(QueueNode)); // 头结点
    rear->next = rear; // 这也是判空的条件
    return rear;
}

/**
 * p.80: 入队列
 */
void EnQueue(QueueNode *rear, DataType x) {
    QueueNode *s = (QueueNode *) malloc(sizeof(QueueNode));
    s->data = x;
    s->next = rear->next; // s 指向头结点
    rear->next = s;       // s 链入尾结点之后
    rear = s;             // 尾指针指向 s
}

/**
 * p.80: 出队列
 */
DataType DeQueue(QueueNode *rear) {
    QueueNode *s, *t;
    DataType x;
    if (rear->next == rear) {       // 队空
        printf("Queue Empty\n");
        exit(0);
    } else {
        s = rear->next;             // s 指向头结点
        rear->next = s->next;       // 删除原头结点, 令队头结点成为新的头结点
        t = s->next;                // t 指向队头结点
        x = t->data;                // 保存队头结点的数据值
        free(s);                    // 释放被删除的头结点
        return x;                   // 返回删除的数据值
    }
}

// 测试
// ===============================================================

int main(void) {
    QueueNode Q, *rear = &Q;
    InitQueue(rear);
    EnQueue(rear, 'a');
    EnQueue(rear, 'b');
    EnQueue(rear, 'c'); // a, b, c
    printf("ch: %c, ch: %c\n", DeQueue(rear), DeQueue(rear)); // a, b
    EnQueue(rear, 'd'); // c, d
    printf("ch: %c, ch: %c\n", DeQueue(rear), DeQueue(rear)); // c, d
}