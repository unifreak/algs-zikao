#define LISTSIZE 100
#include <stdio.h>
#include <stdlib.h>

// p.45: 顺序表
// ===============================================================

typedef int DataType;

typedef struct {
    DataType data[LISTSIZE];
    int length;
} SeqList;

/**
 * 构造一个空线性表 L
 */
void InitList(SeqList *L) {
    L->length = 0;
}

/**
 * 返回 L 表长
 */
int ListLength(SeqList *L) {
    return L->length;
}

/**
 * 返回第 i 个元素. i 从 1 开始.
 */
DataType GetNode(SeqList *L, int i) {
    if (i < 1 || i > L->length) {
        printf("position error");
        return 0;
    }
    return L->data[i-1];
}

/**
 * 查找第一个值为 x 的元素, 并返回该元素的位置. 如果没有则返回 0
 */
int LocateNode(SeqList *L, DataType x) {
    for (int i = 0; i < L->length; i++) {
        if (L->data[i] == x) {
            return i + 1;
        }
    }
    return 0;
}

/**
 * p.46: 在第 i 个元素之前插入值为 x 的新元素
 *
 * 性能:
 * 取决于移动元素的次数. 而移动元素的平均次数为 n/2;
 * 线性阶, 平均时间复杂度为 O(n)
 */
void InsertList(SeqList *L, int i, DataType x) {
    int j;
    if (i < 1 || i > L->length + 1) { // i 从 1 开始...
                                      // i = length+1 时, 相当于在尾部追加
        printf("position error");
        return;
    }
    if (L->length >= LISTSIZE) {      // 插入的元素超出数组容量
        printf("overflow");
        return;
    }
    // 从最后一个元素开始逐一后移
    for (j = L->length - 1; j >= i-1; j--) {
        L->data[j+1] = L->data[j];
    }
    L->data[i-1] = x;
    L->length++;
}

/**
 * p.47: 删除第 i 个元素
 *
 * 性能:
 * 平均移动次数为 (n-1) / 2
 * 时间复杂度为 O(n)
 */
DataType DeleteList(SeqList *L, int i) {
    int j;
    DataType x;
    if (i < 1 || i > L->length) {
        printf("position error");
        exit(0);
    }
    x = L->data[i-1];
    // 元素前移
    for (j = i; j < L->length; j++) {
        L->data[j-1] = L->data[j];
    }
    L->length--;
    return x;
}

// 用例
// ===============================================================

/**
 * p.48:  逆置线性表
 *
 * 性能:
 * 时间复杂度为 O(n)
 */
SeqList Reverse(SeqList L) {
    DataType x;
    int i, k;
    k = L.length / 2; // 以表长的一半为循环控制次数
    for (i = 0; i < k; i++) {
        x = L.data[i];
        L.data[i] = L.data[L.length-i-1];
        L.data[L.length-i-1] = x;
    }
    return L;
}

/**
 * p.49: 找出最大值和最小值及其所在位置
 *
 * 性能: 比较次数
 * 最坏情况 (元素递减): if 和 else if 的比较都为 n-1 次, 共 2(n-1) 次
 * 最好情况 (元素递增): if 的比较次数为 n-1, else if 的比较为 0, 共 n-1 次
 * 平均: (2(n-1) + (n-1)) / 2 = 3(n-1) / 2
 * 时间复杂度: O(n)
 */
void MaxMin(SeqList L, DataType *max, DataType *min, int *k, int *j) {
    int i;
    *max = L.data[0];
    *min = L.data[0];
    *k = *j = 1;
    for (i = 1; i < L.length; i++) {
        if (L.data[i] > *max) {
            *max = L.data[i];
            *k = i + 1; // @err
        } else if (L.data[i] < *min) {
            *min = L.data[i];
            *j = i + 1; // @err
        }
    }
}


/**
 * p.43: 将集合 LB 中元素并入集合 LA
 */
void UnionList(SeqList *LA, SeqList *LB) {
    int n = ListLength(LA);
    for (int i = 1; i <= ListLength(LB); i++) {
        DataType x = GetNode(LB, i);
        if (LocateNode(LA, x) == 0) {
            InsertList(LA, ++n, x);
        }
    }
}

/**
 * p.44: 删除重复元素
 */
void PurgeList(SeqList *L) {
    int i = 1;
    while (i <= L->length) {
        DataType x = GetNode(L, i);
        int j = i + 1;
        while (j <= L->length) {
            DataType y = GetNode(L, j);
            if (x == y) {
                DeleteList(L, j);
        	// 注意, DeleteList() 之后, L->length 会 -1, 故无需 j++
            } else {
                j++;
            }
        }
        i++;
    }
}

// 测试
// ===============================================================

int main(void) {
    SeqList L, *l = &L;
    InitList(l);
    printf("l initial length: %d\n\n", l->length);

    InsertList(l, 1, 1); // l: 1
    InsertList(l, 2, 1); // l: 1, 1
    InsertList(l, 3, 2); // l: 1, 1, 2
    printf("l after Insert: length: %d\n", l->length);
    for (int i = 1; i <= l->length; i++) {
        printf("  data at %d: %d\n", i, l->data[i-1]);
    }
    int pos = LocateNode(l, 2);
    printf("found 2 in l at postion %d\n", pos);

    SeqList R, *r = &R;
    R = Reverse(L); // r: 2, 1, 1
    InsertList(r, r->length+1, 3); // r: 2, 1, 1, 3
    printf("\nr after Reverse: length: %d\n", r->length);
    for (int i = 1; i <= r->length; i++) {
        printf("  data at %d: %d\n", i, r->data[i-1]);
    }

    DataType x = DeleteList(l, 3); // l: 1, 1
    printf("l after Delete: length: %d, deleted data: %d\n", l->length, x);
    for (int i = 1; i <= l->length; i++) {
    	printf("  data at %d: %d\n", i, l->data[i-1]);
    }

    UnionList(l, r); // l: 1, 1, 2, 3
    printf("\nl after union r: length: %d\n", l->length);
    for (int i = 1; i <= l->length; i++) {
        printf("  data at %d: %d\n", i, l->data[i-1]);
    }

    PurgeList(l);  // l: 1, 2
    printf("\nl after Purge: length: %d\n", l->length);
    for (int i = 1; i <= l->length; i++) {
        printf("  data at %d: %d\n", i, l->data[i-1]);
    }

    DataType max, min, *pmax = &max, *pmin = &min;
    int k, j, *pk = &k, *pj = &j;
    MaxMin(L, pmax, pmin, pk, pj); // max: 3, min: 1, k: 3, j: 1
    printf("\nmax: %d, min: %d, k: %d, j: %d\n", max, min, k, j);
}