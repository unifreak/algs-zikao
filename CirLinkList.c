#include <stdlib.h>
#include <stdio.h>

// p.56: 循环链表
// ===============================================================

typedef int DataType;

typedef struct node {
    DataType data;
    struct node *next;
} ListNode;

typedef ListNode *CirLinkList;

// 尾插法创建循环链表 
CirLinkList CreateCirListR() {
    CirLinkList head = (ListNode *) malloc(sizeof(ListNode));
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

// 用例
// ===============================================================

/**
 * p.57: 将值为 x 的新结点插入到有序循环链表中的适当位置, 保持其有序性
 *
 * 性能:
 * 最好情况: 循环一次也不执行
 * 最坏情况: 执行 n 次
 * 时间复杂度: O(n)
 */
void InsertList(CirLinkList L, int x) {
    ListNode *s, *p, *q;
    s = (ListNode *) malloc(sizeof(ListNode));
    s->data = x;
    p = L;
    q = p->next;
    // 注意循环链表判断是否表尾的条件: 是否等于头指针
    while (q->data > x && q != L) {
        p = p->next;
        q = p->next;
    }
    p->next = s;
    s->next = q;
}

void dump(CirLinkList La) {
    ListNode *p = La->next;
    int i = 0;
    while (p != La) {
        printf("|%d:%d| -> ", i++, p->data);
        p = p->next;
    }
    printf("\n");
}

// 测试
// ===============================================================

int main(void) {
    CirLinkList La = CreateCirListR(); // 不输入, 直接按回车
    InsertList(La, 5);
    InsertList(La, 4);
    InsertList(La, 8);
    InsertList(La, 1);
    dump(La); // 8->5->4->1
}