#include <stdlib.h>
#include <stdio.h>

/**
 * p.77: 链队列 (带头结点)
 */
typedef char DataType;

typedef struct qnode {
    DataType data;
    struct qnode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} LinkQueue; // @?: 为什么不用 *LinkQueue, 以后不用特意用 &Q ?
             // @?: 为什么按照上述想法改完, 报错 ?

/**
 * p.78: 构造空队列
 */
void InitQueue(LinkQueue *Q) {
    Q->front = (QueueNode *) malloc(sizeof(QueueNode)); // 申请头结点
    Q->rear = Q->front; // 尾指针也指向头结点
    Q->rear->next = NULL;
}

/**
 * p.78: 判队空
 */
int QueueEmpty(LinkQueue *Q) {
    return Q->rear == Q->front;
}

/**
 * p.78: 入队列
 */
void EnQueue(LinkQueue *Q, DataType x) {
    QueueNode *p = (QueueNode *) malloc(sizeof(QueueNode));
    p->data = x;
    p->next = NULL;
    Q->rear->next = p; // *p 链到原队尾结点之后
    Q->rear = p; // 队尾指针指向新的队尾结点
}

/**
 * p.79: 取队头元素
 */
DataType GetFront(LinkQueue *Q) {
    if (QueueEmpty(Q)) {
        printf("Queue underflow\n");
        exit(0);
    } else {
        return Q->front->next->data; // 因为有头结点, 故需 -> next
    }
}

/**
 * p.79: 出队列
 *
 * 删除操作的一种方式是, 通过修改头结点的指针域, 但是这种方式对于队列长度是否大于 1 需要分开处理:
 * - 长度大于 1 时: 只需修改头结点指针域
 * - 长度等于 1 时: 还需修改尾指针, 另其指针域为 NULL
 *
 * 这种方式比较麻烦, 所以以下实现用了一种改进方式, 以统一处理.
 * 改进方式通过删除头结点, 使队头结点成为新的头结点实现.
 */
DataType DeQueue(LinkQueue *Q) {
    QueueNode *p;
    if (QueueEmpty(Q)) {
        printf("Queue underflow\n");
        exit(0);
    } else {
        p = Q->front;               // p 指向头结点
        Q->front = Q->front->next;  // 头指针指向原队头结点
        free(p);                    // 删除释放原头结点
        return(Q->front->data);     // 返回原对头结点的数据值
    }
}

void dump(LinkQueue *Q) {
    QueueNode *p = Q->front->next;
    printf("{");
    if (! QueueEmpty(Q)) {
        while (p != Q->rear) {
            printf("%c, ", p->data);
            p = p->next;
        }
        printf("%c, ", p->data);
    }
    printf("}\n");
}

int main(void) {
    LinkQueue Q;
    InitQueue(&Q);
    dump(&Q); // {}

    EnQueue(&Q, 'a');
    EnQueue(&Q, 'b');
    dump(&Q); // {a, b}

    DataType ch = DeQueue(&Q);
    printf("ch: %c\n", ch);
    EnQueue(&Q, 'c'); // a
    dump(&Q); // b, c

    printf("next: %c\n", GetFront(&Q)); // b
}