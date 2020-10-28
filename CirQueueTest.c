#include "CirQueue.c"

void dump(CirQueue *Q) {
    printf("{front->%d, rear->%d, data:[", Q->front, Q->rear);
    int i = Q->front;
    while (i < Q->rear ) {
        printf("%d:%c,", i, Q->data[i]);
        i++;
    }
    printf("]}\n");
}

int main(void) {
    CirQueue q, *Q = &q;
    InitQueue(Q);
    dump(Q); // []

    EnQueue(Q, 'a');
    EnQueue(Q, 'b');
    dump(Q); // [a, b]

    DataType ch = DeQueue(Q);
    printf("ch: %c\n", ch);
    EnQueue(Q, 'c'); // a
    dump(Q); // b, c

    printf("next: %c\n", GetFront(Q)); // b
}