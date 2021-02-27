#include <stdlib.h>

// B 树
// ===============================================================

#define M 10 // B 树的阶. 结点中关键字最多可有 M-1 个

typedef int KeyType;
typedef struct node {
    int keynum;         // 关键字个数
    KeyType key[M];     // 关键字向量, key[0] 不用
    struct node *parent;     // 指向双亲结点
    struct node *ptr[M];// 子树指针向量
} BTNode;

typedef BTNode *BTree;

/**
 * p.211: 查找关键字为 K 的对应结点的存储地址及 K 在其中的位置 *pos
 */
BTNode* SearchBTree(BTree T, KeyType K, int *pos) {
    int i;
    BTNode *p = T;
    while (p != NULL) { // 从根结点开始一次向下层查找
        i = p->keynum;
        p->key[0] = K;  // 设置哨兵
        while (K < p->key[i]) { // 从后向前查找第一个小于等于 K 的关键字
            i--;
        }
        if (K == p->key[i] && i > 0) { // 找到
            *pos = i;
            return p;
        } else {        // 未找到
            p = p->ptr[i];
        }
    }
    return NULL;
}

int main(void) {

}