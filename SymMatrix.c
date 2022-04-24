
// 对称矩阵用例
// ===============================================================

/**
 * p.93: 求两个对称矩阵的乘积
 *
 * a, b 分别为矩阵 A, B 的压缩存储一维数组
 * n 为 A, B 的下三角元素个数
 * c 存放 A 和 B 的乘积
 */
void matrixmult(int a[], int b[], int c[][20], int n) {
    int i, j, k, s, l1, l2;
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 20; j++) {
            s = 0;
            for (k = 0; k < n; k++) {
                if (i >= k) {
                    int l1 = i * (i + 1) / 2 + k;
                } else {
                    int l1 = k * (k + 1) / 2 + i;
                }
                if (k >= j) {
                    int l2 = k * (k + 1) / 2 + j;
                } else {
                    int l2 = j * (j + 1) / 2 + k;
                }
                s = s + a[l1] * b[l2];
            }
        }
        c[i][j] = s;
    }
}

int main(void) {

}