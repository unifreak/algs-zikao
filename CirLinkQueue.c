#include <stdlib.h>
#include <stdio.h>

/**
 * p.80: 循环链队列
 *
 * @todo: 测试用例不通过
 */
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
        rear->next = s->next;       // 删除原头结点, 另队头结点成为新的头结点
        t = s->next;                // t 指向队头结点
        x = t->data;                // 保存队头结点的数据值
        free(s);                    // 释放被删除的头结点
        return x;                   // 返回删除的数据值
    }
}

int main(void) {
    // QueueNode *Q; initQueue(Q); 不行
    // 必须用以下方式才行: QueueNode Q; InitQueue(&Q);
    //
    // 而这种方式: QueueNode *Q = (QueueNode *) malloc(sizeof(QueueNode)); InitQueue(Q); 也不行.
    // 它会在第 65 行报错.
    QueueNode Q;
    InitQueue(&Q);
    EnQueue(&Q, 'a');
    EnQueue(&Q, 'b');
    EnQueue(&Q, 'c'); // a, b, c
    printf("ch: %c, ch: %c\n", DeQueue(&Q), DeQueue(&Q)); // a, b
    EnQueue(&Q, 'd'); // c, d
    printf("ch: %c, ch: %c\n", DeQueue(&Q), DeQueue(&Q)); // c, d
}