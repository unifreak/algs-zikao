#include <stdio.h>

/**
 * p.90: 矩阵的转置 (假设把 5*8 转置为 8*5 矩阵, n=5, m=8)
 */
void trsmat(int a[][8], int b[][5], int m, int n) {
    int i, j;
    for (j = 0; j < m; j++) {
        for (i = 0; i < n; i++) {
            b[i][j] = a[j][i];
        }
    }
}

/**
 * p.91: 寻找马鞍点
 *
 * 假如 a[i][j] 是第 i 行的最小值, 又是第 j 列的最大值, 则称此元素为该矩阵的马鞍点
 */
void MaxMin(int a[5][8], int m, int n) {
    int i, j;
    int max[n], min[m];
    for (i = 0; i < m; i++) { // 计算每行的最小值, 存入 min 数组
        min[i] = a[i][0];
        for (j = 1; j < n; j++) {
            if (a[i][j] < min[i]) {
                min[i] = a[i][j];
            }
        }
    }
    for (j = 0; j < n; j++) { // 计算每列的最大值, 存入 max 数组
        max[j] = a[0][j];
        for (i = 1; i < m; i++) {
            if (a[i][j] > max[j]) {
                max[j] = a[i][j];
            }
        }
    }
    for (i = 0; i < m; i++) { // 判断是否为马鞍点
        for (j = 0; j < n; j++) {
            if (min[i] == max[j]) {
                printf("%d, %d", i, j);
            }
        }
    }
}

int main(void) {
    int a[5][8] = {{1, 2, 3, 4, 5, 6, 7, 8},
                   {21, 22, 23, 24, 25, 26, 27, 28},
                   {31, 32, 33, 34, 35, 36, 37, 38},
                   {41, 42, 43, 44, 45, 46, 47, 48},
                   {51, 52, 53, 54, 55, 56, 57, 58}};
    int b[8][5];
    trsmat(a, b, 5, 8);
    printf("trsmat result:\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d  ", b[i][j]);
        }
        printf("\n");
    }

    printf("MaxMin result: ");
    MaxMin(a, 5, 8); // 4, 0
}