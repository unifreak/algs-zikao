#include <stdlib.h>
#include <stdio.h>

/**
 * p.75: 循环队列
 */
#define QUEUESIZE 20

typedef char DataType;

typedef struct {
    DataType data[QUEUESIZE];
    int front, rear;
} CirQueue;

/**
 * p.75: 置空队列
 */
void InitQueue(CirQueue *Q) {
    Q->front = Q->rear = 0;
}

/**
 * p.76: 判队空
 */
int QueueEmpty(CirQueue *Q) {
    return Q->rear == Q->front;
}

/**
 * p.76: 判队满
 */
int QueueFull(CirQueue *Q) {
    return (Q->rear + 1) % QUEUESIZE == Q->front;
}

/**
 * p.76: 入队列
 */
void EnQueue(CirQueue *Q, DataType x) {
    if (QueueFull(Q)) {
        printf("Queue overflow\n");
    } else {
        Q->data[Q->rear] = x;
        Q->rear = (Q->rear + 1) % QUEUESIZE; // 使用其余运算实现循环意义下的加 1
    }
}

/**
 * p.76: 取队头元素
 */
DataType GetFront(CirQueue *Q) {
    if (QueueEmpty(Q)) {
        printf("Queue empty\n");
        exit(0);
    } else {
        return Q->data[Q->front];
    }
}

/**
 * p.76: 出队列
 */
DataType DeQueue(CirQueue *Q) {
    DataType x;
    if (QueueEmpty(Q)) {
        printf("Queue empty\n");
        exit(0);
    }
    x = Q->data[Q->front];
    Q->front = (Q->front + 1) % QUEUESIZE;
    return x;
}
