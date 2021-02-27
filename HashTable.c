#include <stdio.h>
#include <stdlib.h>

// 散列表查找
// ===============================================================

#define M 997 // 散列表表长, 一般 M 为一个素数
#define NULLKEY -32768 // 空单元默认存储值

// 线性探查法
// ===============================================================

typedef int KeyType;
typedef char DataType;

// 散列表结点
typedef struct {
    KeyType key;
    DataType data;
} NodeType;

// 散列表
typedef NodeType HashTable[M];

/**
 * p.218: 散列函数 (采用除余法)
 */
int h(KeyType K, int m) {
    return K % m;
}

/**
 * p.218: 查找
 * 在长度为 m 的散列表 HT 中查找关键字值为 K 的元素位置
 */
int HashSearch1(HashTable HT, KeyType K, int m) {
    int d, temp;
    d = h(K, m); // 初始散列地址
    temp = d; // 作为哨兵, 防止进入重复循环
    while (HT[d].key != NULLKEY) { // 不为空则循环
        if (HT[d].key == K) { // 查找成功
            return d;
        } else { // 探查下一单元
            d = (d+1) % m;
        }
        if (d == temp) { // 查找一周仍无空位置, 返回 -1 表示失败
            return -1;
        }
    }
    return d; // 遇到空单元, 查找失败, 返回空单元地址
}

/**
 * p.219: 插入
 * 在 HT 表中插入一个新结点 s
 */
int HashInsert1(HashTable HT, NodeType s, int m) {
    int d;
    d = HashSearch1(HT, s.key, m);  // 查找插入位置
    if (d == -1) {                  // 表满, 不能插入
        return -1;
    } else {
        if (HT[d].key == s.key) {   // 表中已有该结点
            return 0;
        } else {                    // 插入新结点
            HT[d] = s;
            return 1;
        }
    }
}

// 拉链法
// ===============================================================

// 结点
typedef struct node {
    KeyType key;
    DataType data;
    struct node *next;
} HTNode;

// 散列表
typedef HTNode *HT[M];

/**
 * p.219: 查找
 * 在长度为 m 的散列表 T 中查找关键字值为 K 的元素位置
 */
HTNode *HashSearch2(HT T, KeyType K, int m) {
    HTNode *p = T[h(K, m)]; // 去 K 所在链表的头指针
    while (p != NULL && p->key != K) { // 顺链查找
        p = p->next;
    }
    return p;
}

/**
 * p.219: 插入
 * 采用头插法在 T 表上插入一个新结点 s
 */
int HashInsert2(HT T, HTNode *s, int m) {
    int d;
    HTNode *p = HashSearch2(T, s->key, m); // 查找表中有无待插入结点
    if (p != NULL) { // 已有该结点
        return 0;
    } else { // 将 s 插入在相应链表表头
        d = h(s->key, m);
        s->next = T[d];
        T[d] = s;
        return 1;
    }
}

// 测试
// ===============================================================

void initHashTable(HashTable HT, int m) {
    for (int i = 0; i < m; i++) {
        HT[i].key = NULLKEY;
    }
}

void dump(HashTable HT, int m) {
    printf("HashTable:\n");
    for (int i = 0; i < m; i++) {
        printf("%d: %d\n", i, HT[i].key);
    }
}

void dumpHT(HT T, int m) {
    printf("HT:\n");
    for (int i = 0; i < m; i++) {
        printf("%d: ", i);
        HTNode *p = T[i];
        while (p != NULL) {
            printf("%d->", p->key);
            p = p->next;
        }
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    HashTable T1;
    initHashTable(T1, 11);

    int sample[9] = {27, 13, 55, 32, 18, 49, 24, 38, 43}; // p.216 例 8.6
    NodeType s;
    for (int i = 0; i < 9; i++) {
        NodeType s = {sample[i], ' '};
        HashInsert1(T1, s, 11);
    }
    dump(T1, 11);

    HT T2 = { NULL };
    for (int i = 0; i < 9; i++) {
        HTNode *s = (HTNode *) malloc(sizeof(HTNode));
        s->key = sample[i];
        HashInsert2(T2, s, 11);
    }
    dumpHT(T2, 11);
}