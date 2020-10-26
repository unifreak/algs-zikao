#include <stdlib.h>
#include <stdio.h>

typedef int DataType;

// p.56: 循环链表
typedef struct node {
    DataType data;
    struct node *next;
} ListNode;

typedef ListNode *CycleLinkList;

CycleLinkList CreateCycleListR() {
    CycleLinkList head = (ListNode *) malloc(sizeof(ListNode));
    ListNode *p, *r;
    DataType ch;
    r = head; // 尾指针初始指向头结点
    while ((ch = getchar()) != '\n') {
        p = (ListNode *) malloc(sizeof(ListNode));
        p->data = ch;
        r->next = p;
        r = p; // 尾指针指向新结点
    }
    r->next = head; // 终端结点指向头结点
    return head;
}

/**
 * p.57: 将值为 x 的新结点插入到有序循环链表中的适当位置, 保持其有序性
 *
 * 性能:
 * 最好情况: 循环一次也不执行
 * 最坏情况: 执行 n 次
 * 时间复杂度: O(n)
 */
void InsertList(CycleLinkList L, int x) {
    ListNode *s, *p, *q;
    s = (ListNode *) malloc(sizeof(ListNode));
    s->data = x;
    p = L;
    q = p->next;
    while (q->data > x && q != L) {
        p = p->next;
        q = p->next;
    }
    p->next = s;
    s->next = q;
}

void dump(CycleLinkList La) {
    ListNode *p = La->next;
    int i = 0;
    while (p != La) {
        printf("|%d:%d| -> ", i++, p->data);
        p = p->next;
    }
    printf("\n");
}

int main(void) {
    CycleLinkList La = CreateCycleListR(); // 不输入
    InsertList(La, 5);
    InsertList(La, 4);
    InsertList(La, 8);
    InsertList(La, 1);
    dump(La); // 8->5->4->1
}