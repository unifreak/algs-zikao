#include <stdlib.h>
#include <stdio.h>

// p.50: 单链表
// ===============================================================

typedef char DataType;

// 结点元素
typedef struct node {
    DataType data;      // 数据域
    struct node *next;  // 指针域
} ListNode;

typedef ListNode *LinkList; // 头指针

// 不带头结点
// ===============================================================

/**
 * p.51: 头插法建表
 *
 * 链表中结点的次序和输入顺序相反, 理解是不太直观.
 * 若需和输入次序一致, 可以使用尾插法 CreateListR()
 */
LinkList CreateListF() {
    LinkList head;
    ListNode *p;
    char ch;
    head = NULL;
    ch = getchar();
    while (ch != '\n') {
        p = (ListNode *) malloc(sizeof(ListNode));
        p->data = ch;
        p->next = head; // 第一个结点也是终端结点, 指针域赋 NULL
        head = p; // 头指针指向新结点
        ch = getchar();
    }
    return head;
}

/**
 * p.51: 尾插法建表
 */
LinkList CreateListR() {
    LinkList head, rear; // rear 始终指向终端结点
    ListNode *p;
    char ch;
    head = NULL;
    rear = NULL;
    ch = getchar();
    while (ch != '\n') {
        p = (ListNode *) malloc(sizeof(ListNode));
        p->data = ch;
        if (head == NULL) {
            head = p;
        } else {
            rear->next = p;
        }
        rear = p;
        ch = getchar();
    }
    if (rear != NULL) {
        rear->next = NULL; // 终端结点指针域置空
    }
    return head;
}

// 带头结点
// ===============================================================

/**
 * p.52: 带头结点的尾插法建表
 */
LinkList CreateListR1() {
    LinkList head = (ListNode *) malloc(sizeof(ListNode)); // 头结点
    ListNode *p, *r;
    DataType ch;
    r = head; // 尾指针初始指向头结点
    while ((ch = getchar()) != '\n') {
        p = (ListNode *) malloc(sizeof(ListNode));
        p->data = ch;
        r->next = p;
        r = p; // 尾指针指向新结点
    }
    r->next = NULL; // 终端结点指针域置空
    return head;
}

/**
 * p.53: 按结点序号查找 (带头结点), 若查找成功返回结点存储位置, 否则返回 NULL
 *
 * 注意: 头结点的序号是 0, 第一个结点序号为 1, 以此类推...
 *
 * 性能:
 * 基本操作是比较 j 和 i 以及后移指针
 * 语句频度与被查结点在链表中的位置相关
 * 等概率情况下, 平均时间复杂度为 O(n)
 */
ListNode *GetNode(LinkList head, int i) {
    ListNode *p;
    int j;
    p = head->next; // p 初始指向第一个结点 (表头结点/开始结点)
    j = 1;
    while (p != NULL && j < i) {
        p = p->next;
        ++j;
    }
    if (j == i) {   // 查找成功
        return p;
    } else {        // 查找失败: 还未查找到位置 i 已经到达表尾
        return NULL;
    }
}

/**
 * p.53: 按结点值查找 (带头结点)
 *
 * 性能:
 * 基本操作是查找操作, 最坏情况下执行 n 次
 * 时间复杂度为 O(n)
 */
ListNode *LocateNodeK(LinkList head, DataType k) {
    ListNode *p = head->next;
    while (p && p->data != k) {
        p = p->next;
    }
    return p;
}

/**
 * p.54: 在第 i 个位置上插入数据域值为 x 的新结点 (带头结点)
 * NOTE: i 从 1 开始
 *
 * 性能:
 * 不像顺序表一样需要移动结点, 基本操作仍然是查找操作
 * 时间复杂度为 O(n)
 */
void InsertList(LinkList head, int i, DataType x) {
    ListNode *p, *s;
    int j;
    p = head;
    j = 0;
    while (p != NULL && j < i - 1) {
        p = p->next;
        ++j;
    }
    if (p == NULL) {        // 插入位置超出队尾
        printf("Error\n");
        return;
    } else {
        s = (ListNode *) malloc(sizeof(ListNode));
        s->data = x;
        s->next = p->next;
        p->next = s;
    }
}

/**
 * p.54: 删除第 i 个结点 (带头结点)
 *
 * 性能:
 * 与插入算法的时间复杂度一样, 都是 O(n)
 */
DataType DeleteList(LinkList head, int i) {
    ListNode *p, *s;
    DataType x;
    int j;
    p = head;
    j = 0;
    while (p != NULL && j < i - 1) {
        p = p->next;
        ++j;
    }
    if (p == NULL) {        // 删除位置超出队尾
        printf("Position Error!\n");
        exit(0);
    } else {
        s = p->next;        // s 指向第 i 个结点
        p->next = s->next;  // 使 p->next 指向第 i+1 个结点
        x = s->data;        // 保存被删除的结点值
        free(s);            // 删除第 i 个结点
        return x;           // 返回结点值
    }
}


// 用例
// ===============================================================

/**
 * p.55: 按序号奇偶分解单链表 a, 奇数的结点仍挂在 a, 偶数的结点挂在 b (带头结点)
 * 注意 b 是一个带头结点的空链表
 *
 * 性能:
 * 需要扫描整表, 时间复杂度为 O(n)
 */
void Split(LinkList a, LinkList b) {
    ListNode *p, *r, *s;
    p = a->next; // p 指向表头结点
    r = a;       // r 指向 a 表的当前结点
    s = b;       // s 指向 b 表的当前结点
    while (p != NULL) {
        r->next = p;    // 序号为奇数的结点链接到 a 表上
        r = p;          // r 总是指向 a 表最后一个结点
        p = p->next;
        if (p) {
            s->next = p; // 序号为偶数的结点链接到 b 表上
            s = p;       // s 总是指向 b 表最后一个结点
            p = p->next;
        }
    }
    r->next = s->next = NULL;
}

/**
 * p.56: 归并两个有序链表 La, Lb 为有序链表 Lc
 *
 * 性能:
 * 需要扫描两个链表, 用一个循环
 * 时间复杂度为 O(n)
 */
LinkList MergeList(LinkList La, LinkList Lb) {
    ListNode *pa, *pb, *pc;
    LinkList Lc;
    pa = La->next; // pa, pb 分别指向两个链表的开始结点
    pb = Lb->next; 
    Lc = pc = La;  // 用 La 的头结点作为 Lc 的头结点
    while (pa != NULL && pb != NULL) { // 将较小者插入 Lc
        if (pa->data <= pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        } else {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa != NULL ? pa : pb;  // 插入链表剩余部分
    free(Lb);
    return Lc;
}

// 测试
// ===============================================================

void dumpLinkList(LinkList La) {
    ListNode *p = La;
    int i = 0;
    while (p != NULL) {
        printf("|%d:%c| -> ", i++, p->data);
        p = p->next;
    }
    printf("\n");
}