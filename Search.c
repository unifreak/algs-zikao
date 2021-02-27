#include <stdio.h>
#include <stdlib.h>

// 顺序表的查找
// ===============================================================

#define N 20 // 最大记录数

// 顺序表
typedef int KeyType;
typedef char InfoType;
typedef struct {
    KeyType key;
    InfoType data;
} NodeType;

typedef NodeType SeqList[N+1]; // 0 号单元用作哨兵

// 顺序查找 / 线性查找
// ===============================================================

/**
 * p.197: 顺序查找
 *
 * 性能:
 * 查找成功时, 平均查找长度为 (n+1)/2, 即约表长的一半.
 * 查找不成功, 则需要全表扫描, 查找长度为 n+1.
 * 故成功和不成功机会相等时, 平均查找长度为 (3/4)(n+1)
 *
 * 特点:
 * 简单, 对表结构无要求, 无论顺序存储或链式存储, 是否有序, 都适用
 * 但是效率低
 */
int SeqSearch(SeqList R, KeyType k, int n) {
    R[0].key = k;     // R[0] 作为哨兵, 用 R[0] == k 作为循环下界的终结条件, 省略了对下标越界的检查
    int i = n;        // 从后往前扫描
    while (R[i].key != k) {
        i--;
    }
    return i;         // 返回下标. 若找不到则返回 0
}

/**
 * p.198: 有序表的顺序查找
 *
 * 性能:
 * 查找成功时, 平均查找长度基本与无序表一样, 即约表长的一半.
 * 查找失败时, 平均查找长度是表长的一半.
 * 故平均查找长度是 (n+1)/2
 */
int SeqSearch1(SeqList R, KeyType k, int n) {
    int i = n;
    while (R[i].key > k) { // 针对有序表的优化: 一旦小于或等于关键字时就结束循环
        i--;
    }
    if (R[i].key == k) {   // 找到, 返回小标
        return i;
    }
    return 0;              // 未找到, 返回 0
}

// 二分查找 / 折半查找
// ===============================================================

/**
 * p.198: 二分查找
 * 在区间 R[low..high] 中进行二分递归, 查找等于 k 的记录
 * low 的初始值为 1, high 的初始值为 n
 *
 * 性能:
 * 二分查找过程可用一颗二叉树来描述 (二叉判定树).
 * 树中每个子树的根结点对应当前查找区间的中间记录, 左子树和右子树分表对应区间的左子表和右子表.
 * 则关键字比较的次数恰好为该结点在树中的层数.
 * 因此二叉查找的最坏性能和平均性能相当接近, 都约为 logn
 */
int BinSearch(SeqList R, KeyType k, int low, int high) {
    int mid;
    if (low <= high) {
        mid = (low + high) / 2; // 计算中间记录的位置
        if (R[mid].key == k) {  // 查找成功
            return mid;
        }
        if (R[mid].key > k) {   // 左子表中继续查找
            return BinSearch(R, k, low, mid-1);
        } else {                // 右子表中继续查找
            return BinSearch(R, k, mid+1, high);
        }
    } else {
        return 0;               // 查找失败
    }
}

/**
 * p.199: 非递归实现的二分查找
 */
int BinSearch1(SeqList R, KeyType k, int n) {
    int low = 1, mid, high = n; // 初始化上下界
    while (low <= high) {
        mid = (low + high) / 2;
        if (R[mid].key == k) {  // 查找成功
            return mid;
        }
        if (R[mid].key > k) {   // 修改上界
            high = mid - 1;
        } else {                // 修改下界
            low = mid + 1;
        }
    }
    return 0;                   // 查找失败
}

/**
 * p.200: 利用二分查找插入新值, 并保持有序
 */
void BinInsert(SeqList R, KeyType x, InfoType y, int n) {
    int low = 1, high = n, mid, pos, i;
    int find = 0; // 是否找到相同关键字的记录
    while (low <= high && ! find) { // 二分查找
        mid = (low + high) /2 ;
        if (x < R[mid].key) {
            high = mid - 1;
        } else if (x > R[mid].key) {
            low = mid + 1;
        } else {
            find = 1;
        }
    }
    if (find) {   // 找到, 则 mid 为插入位置
        pos = mid;
    } else {      // 未找到, 则 low 为插入位置
        pos = low;
    }
    // 后移
    for (i = n; i >= pos; i--) {
        R[i+1] = R[i];
    }
    // 插入
    R[pos].key = x;
    R[pos].data = y;
}

// 二叉排序树 BST
// ===============================================================

// 二叉排序树结点
typedef struct node {
    KeyType key;    // 关键字
    InfoType other; // 其他数据域
    struct node *lchild, *rchild; // 左右子树指针
} BSTNode;

// 二叉排序树
typedef BSTNode *BSTree;


/**
 * p.203: 向 BST 中插入新结点
 */
BSTree InsertBST(BSTree T, BSTNode *S) {
    BSTNode *f, *p = T;
    // 往左子树或右子树中深入, 寻找插入位置
    while (p) {
        f = p; // f 指向 p 的双亲, 以便插入时使用
        if (S->key < p->key) {
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }
    // 插入新结点
    if (T == NULL) { // 空树
        T = S;
    } else if (S->key < f->key) { // 新结点较小
        f->lchild = S;
    } else { // 新结点较大
        f->rchild = S;
    }
    return T;
}

/**
 * p.204: 生成 BST
 *
 * 输入顺序不同, 得到的 BST 也不同
 */
BSTree CreateBST(void) {
    BSTree T = NULL; // 建立空树
    KeyType key;
    BSTNode *S;
    // 根据输入的关键字 (逗号分隔) 生成结点, 并加入树中
    scanf("%d, ", &key);
    while (key) { // 0 为输入结束
        // 生成新结点
        S = (BSTNode *) malloc(sizeof(BSTNode));
        S->key = key;
        S->lchild = S->rchild = NULL;
        // 插入树中
        T = InsertBST(T, S);
        scanf("%d, ", &key);
    }
    return T;
}


/**
 * p.205: 在 BST 中查找关键字为 x 的结点
 *
 * 性能:
 * 比较次数: 最少一次, 最多为树的深度, 所以平均查找次数小于树的深度.
 * 若 BST 是接近一颗平衡树, 则时间复杂度为 O(logn).
 * 若 BST 退化为一颗单支树, 则时间复杂度为 O(n).
 * 一般情况下, 时间复杂度为 O(logn)
 */
BSTNode* SearchBST(BSTree T, KeyType x) {
    if (T == NULL || T->key == x) {
        return T;
    }
    if (x < T->key) {
        return SearchBST(T->lchild, x);
    } else {
        return SearchBST(T->rchild, x);
    }
}

// 测试
// ===============================================================

void dump(int pos, char* name) {
    printf("%s: ", name);
    if (pos == 0) {
        printf("not found");
    } else {
        printf("found at position %d\n", pos);
    }
}

void dumpList(SeqList R, int n) {
    printf("Seq:\n");
    for (int i = 1; i <= n; i++) {
        printf("  %d: %d, %c\n", i, R[i].key, R[i].data);
    }
}

void dumpBSTSearch(BSTNode *r, int n) {
    printf("BSTSearch %d: ", n);
    if (r) {
        printf("found\n");
    } else {
        printf("not found\n");
    }
}

int main(void) {
    int pos;
    // R1 无序
    SeqList R1 = {{}, {46, ' '}, {39, ' '}, {17, ' '}, {23, ' '}, {28, ' '}, {55, ' '}, {18, ' '}, {46, ' '}};
    pos = SeqSearch(R1, 55, 8);
    dump(pos, "SeqSearch in unsort");

    // R2 有序
    SeqList R2 = {{}, {17, ' '}, {18, ' '}, {23, ' '}, {28, ' '}, {39, ' '}, {46, ' '}, {46, ' '}, {55, ' '}};
    pos = SeqSearch(R2, 55, 8);
    dump(pos, "SeqSearch in sorted");

    pos = BinSearch(R2, 55, 1, 8);
    dump(pos, "BinSearch with recursive");

    pos = BinSearch1(R2, 55, 8);
    dump(pos, "BinSearch without recursive");

    BinInsert(R2, 43, 'x', 8);
    dumpList(R2, 9);

    BSTree T = CreateBST(); // 输入图 8.6 例子: 35, 26, 53, 18, 32, 65, 0
    BSTNode* r = SearchBST(T, 26);
    dumpBSTSearch(r, 26);
    r = SearchBST(T, 27);
    dumpBSTSearch(r, 27);
}