#include <stdlib.h>
#include <stdio.h>

/**
 * p.57: 带头结点的双向循环链表
 */
typedef char DataType;

typedef struct dlnode {
    DataType data;
    struct dlnode *prior, *next;
} DLNode;

typedef DLNode *DLinkList;

// 尾插法创建链表
DLinkList CreateDListR() {
    DLinkList head = (DLNode *) malloc(sizeof(DLNode));
    DLNode *p, *r;
    DataType ch;
    r = head; // 尾指针初始指向头结点
    while ((ch = getchar()) != '\n') {
        p = (DLNode *) malloc(sizeof(DLNode));
        p->data = ch;
        r->next = p;
        p->prior = r;
        r = p; // 尾指针指向新结点
    }
    r->next = head; // 终端结点指向头结点
    return head;
}

/**
 * p.58: 往给定结点前插入新结点
 */
void DLInsert(DLNode *p, DataType x) {
    DLNode *s = (DLNode *) malloc(sizeof(DLNode));
    s->data = x;
    s->prior = p->prior;
    s->next = p;
    p->prior->next = s;
    p->prior = s;
}

/**
 * p.58: 删除指定结点 p
 */
DataType DLDelete(DLNode *p) {
    p->prior->next = p->next;
    p->next->prior = p->prior;
    DataType x = p->data; // @err
    free(p);
    return x;
}

/**
 * p.59: 把 head 指向的循环链表修改为双向循环链表, 该循环链表有如下特征:
 * - 具有 prior, data, next 三个域
 * - 但是 prior 指针皆为 NULL
 * - 尾结点指向头结点
 */
void Trans(DLinkList head) {
    DLNode *p;
    p = head;
    while (p->next != head) {
        p->next->prior = p;
        p = p->next;
    }
    head->prior = p;    // head 的前趋指向表的终端结点
}

void dump(DLinkList L) {
    DLNode *p = L->next;
    int i = 0;
    while (p != L) {
        printf("%d: %c <- %c -> %c\n", i++, p->prior->data, p->data, p->next->data);
        p = p->next;
    }
    printf("\n");
}

int main(void) {
    DLinkList La = CreateDListR(); // 输入: abc
    dump(La); // a <-> b <-> c

    DLNode *p = La->next;
    DLInsert(p, 'd'); // d <-> a <-> b <-> c
    dump(La);

    p = La->next;
    DLDelete(p);
    dump(La); // a <-> b <-> c
}