#include <stdio.h>
#include <stdlib.h>

// 稀疏矩阵
// ===============================================================

/**
 * p.94: 三元组表表示的稀疏矩阵
 */
#define MAXSIZE 1000
#define MAXROW  500

typedef int DataType;

typedef struct {
    int i, j;   // 非零元素的行号, 列号
    DataType v; // 非零元素的值
} TriTupleNode;

typedef struct {
    TriTupleNode data[MAXSIZE]; // 存储三元组的数组
    int m, n, t;                // 矩阵的行数, 列数和非零元素个数
} TSMatrix;

/**
 * p.97: 带行表的三元组表
 */
typedef struct {
    TriTupleNode data[MAXSIZE];
    int RowPos[MAXROW];         // 每行第一个非零元素的位置表
    int m, n, t;
} RLSMatrix;

// 用例
// ===============================================================

/**
 * p.95: 从 m 行, n 列的数组 a 创建稀疏矩阵的三元组表
 */
void CreateTriTable(TSMatrix *b, int a[][5], int m, int n) {
    int i, j, k = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                b->data[k].i = i;
                b->data[k].j = j;
                b->data[k].v = a[i][j];
                k++;
            }
        }
    }
    b->m = m;
    b->n = n;
    b->t = k;
}

/**
 * p.96: a 和 *b 是矩阵 M, T 的三元组表表示, 求稀疏矩阵 M 的转置 T
 *
 * 性能:
 * 主要操作是二重循环
 * 时间复杂度为 O(n*t), 即与 M 的列数和非零元素个数的乘积成正比
 * 该算法仅适用于非零元素个数 t 远远小于矩阵元素个数 m*n 的情况
 */
void TransMatrix(TSMatrix a, TSMatrix  *b) {
    int p, q, col;
    b->m = a.n; // 行列数互换
    b->n = a.m;
    b->t = a.t;
    if (b->t <= 0) {
        printf("M has no element\n");
    } else {
        q = 0;
        for (col = 0; col < a.n; ++col) {       // 按列递增的扫描全表
            for (p = 0; p < a.t; ++p) {
                if (a.data[p].j == col) {       // 找到与当前列相等的三元组
                    b->data[q].i = a.data[p].j; // 互换行列
                    b->data[q].j = a.data[p].i;
                    b->data[q].v = a.data[p].v;
                    ++q;
                }
            }
        }
    }
}

/**
 * p.96: 快速转置矩阵
 *
 * 假设一个稀疏矩阵, 有 m=2 行, n=3 列
 * 
 *       0 1 2
 *       -----      
 *    0 |2 0 5
 *    1 |0 4 0
 *    
 * 这个算法使用两个辅助数组
 * - num 存储每列上的非零元素数 [0:1, 1:1, 2:1]
 * - rownext 初始化时, 计算并存储转储到 b 时, 每行第一个元素对应应转储到的位置 [0:0, 1:1, 2:2]
 * 
 * 然后逐个遍历并转储 a 中的元素到对应 rownext 中计算出的位置, 并递增 rownext 保存该行下一元素位置
 *      2: 存储到位置 0, rownext -> [0:1, 1:1, 2:2]
 *      5: 存储到位置 2, rownext -> [0:1, 1:1, 2:3]
 *      4: 存储到位置 1, rownext -> [0:1, 1:2, 2:3]
 * 转储完成
 */
void FastTrans(TSMatrix a, TSMatrix *b) {
    int col, p, t, q;
    int *num, *rownext;
    // num[j] 存放矩阵第 j 列上非零元素个数
    //     calloc 分配了 a.n+1 个每块为 4 字节的内存块, 并把内存内容清 0
    //     这相当于创建了 num[a.n+1] 数组, 且每个元素置空
    num = (int *) calloc(a.n+1, 4);
    // rownext[i] 代表转置矩阵第 i 行的下一个非零元素在 b 中的位置
    rownext = (int *) calloc(a.m+1, 4);
    b->m = a.n;
    b->n = a.m;
    b->t = a.t;
    if (b->t) {
        for (col = 0; col < a.n; ++col) { // 初始化 num
            num[col] = 0;
        }
        for (t = 0; t < a.t; ++t) {       // 计算每列非零元素个数
            ++num[a.data[t].j];
        }

        rownext[0] = 0;
        for (col = 1; col < a.n; ++col) { // 给出 b 中每一行的起始点
            rownext[col] = rownext[col-1] + num[col-1];
        }
        for (p = 0; p < a.t; ++p) {       // 转置操作
            col = a.data[p].j;
            q = rownext[col];
            b->data[q].i = a.data[p].j;
            b->data[q].j = a.data[p].i;
            b->data[q].v = a.data[p].v;
            ++rownext[col];               // 计算 b 中该行的下一个位置
        }
    }
}

// 测试
// ===============================================================

int main(void) {
    int a[4][5] = {{0, 3, 0, 5, 0},
                   {0, 0, -2, 0, 0},
                   {1, 0, 0, 0, 6},
                   {0, 0, 8, 0, 0}};
    TSMatrix M, *m = &M;
    CreateTriTable(m, a, 4, 5);
    printf("matrix:\n");
    for (int k = 0; k < m->t; k++) {
        printf("  %d:%d:%d\n", m->data[k].i, m->data[k].j, m->data[k].v);
    }

    TSMatrix T, *trans = &T;
    TransMatrix(M, trans);
    printf("transmatrix result:\n");
    for (int k = 0; k < trans->t; k++) {
        printf("  %d:%d:%d\n", trans->data[k].i, trans->data[k].j, trans->data[k].v);
    }

    TSMatrix T2, *fasttrans = &T2;
    FastTrans(M, fasttrans);
    printf("fasttrans result:\n");
    for (int k = 0; k < fasttrans->t; k++) {
        printf("  %d:%d:%d\n", fasttrans->data[k].i, fasttrans->data[k].j, fasttrans->data[k].v);
    }
}