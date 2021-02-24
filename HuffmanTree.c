#include <stdio.h>
#include <string.h>

// p.132: 哈夫曼树
// ===============================================================

#define N 8         // 叶子结点数
#define M (2*N-1)   // 哈夫曼树中结点总数: 对 N 个结点进行 N-1 次合并, 将产生 N-1 个新结点
                    // 故结点总数为 2*N-1


typedef char DataType;

// 树中结点类型
typedef struct {
    DataType data;
    float weight;               // 权值
    int lchild, rchild, parent; // 左右孩子及双亲指针
} HTNode;

// 哈弗曼树
typedef HTNode HuffmanTree[M+1]; // 0 号单元不用, 故加 1

/**
 * p.133: 在 HT[1..k] 中选出两个权值最小的根结点, 将其下标保存在 s1, s2 中
 */
void select(HuffmanTree HT, int k, int *s1, int *s2) {
    int i, j;
    int minl = 101; // @?
    for (i = 1; i <= k; i++) {
        if (HT[i].weight < minl && HT[i].parent == 0) {
            j = i;
            minl = HT[i].weight;
        }
    }
    *s1 = j;
    minl = 32767;
    for (i = 1; i <= k; i++) {
        if (HT[i].weight < minl && HT[i].parent == 0 && i != *s1) {
            j = i;
            minl = HT[i].weight;
        }
    }
    *s2 = j;
}

/**
 * p.133: 构造哈弗曼树
 */
void CHuffmanTree(HuffmanTree HT) {
    int s1, s2;
    for (int i = 1; i <= M; i++) {
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].parent = 0;
        HT[i].weight = 0;
    }
    for (int i = 1; i <= N; i++) {
        scanf("%c:%f,", &HT[i].data, &HT[i].weight);
    }
    for (int i = N + 1; i <= M; i++) { // 在 HT[1..i-1] 中选择 parent 为 0 且权值最小的两个根结点
        select(HT, i-1, &s1, &s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;   // 新的根结点为刚选出的两个结点权值之和
    }
}

// p.136: 哈夫曼编码
// ===============================================================
 
typedef struct {
    char ch;        // 存放编码的字符
    char bits[N+1]; // 存放编码位串. 每个字符的编码长度不同, 但不会超过字符集的大小 N, 再加上串结束符 \0
    int len;
} CodeNode;

typedef CodeNode HuffmanCode[N+1];


/**
 * p.136: 根据哈弗曼树 HT 求哈夫曼编码表 HC
 *
 * 从哈弗曼树叶子结点 HT[i] 出发, 一直向上回溯到根结点.
 * 回溯过程中, 利用双亲指针找到 HT[i] 的双亲 HT[p]
 * 再利用该双亲的指针域 lchild, rchild 可知 HT[i] 是 HT[p] 的左孩子还是右孩子
 * 若是左孩子则生成代码 0, 否则生成代码 1
 * 重复上述过程, 直到找到根节点为止
 *
 * 显然, 这样生成的代码序列与要求的编码次序相反, 因此将生成的代码从后向前存放在临时变量 cd 中
 * 并设一个指针 start 指示编码在该串中的起始位置
 * 当某字符编码完成时, 从临时串的 start 处将编码复制到该字符相应的 bits 中即可.
 *
 * ---
 *
 * 哈夫曼树也可以用来译码. 与编码过程相反, 译码过程是从树根节点出发, 逐个读入电文中的二进制码.
 * 若读入 0, 走向左孩子
 * 若读入 1, 走向右孩子
 * 一旦到达叶子结点, 便译出相应的字符
 */
void HuffmanEncoding(HuffmanTree HT, HuffmanCode HC) {
    int c, p, i;    // c 指示 HT 中孩子位置, p 指示 HT 中双亲位置
    char cd[N+1];   // 存放临时编码串
    int start;      // 指示编码在 cd 中的起始位置
    cd[N] = '\0';   // 最后一位放上串结束符
    for (i = 1; i <= N; i++) {
        start = N;  // 初始位置设为最后一个位置, 以从后往前放置代码
        c = i;      // 从叶子结点 HT[i] 开始回溯
        HC[i].ch = HT[i].data;
        while ((p = HT[c].parent) > 0) {    // 直至回溯到 HT[c] 是树根为止
            cd[--start] = (HT[p].lchild == c) ? '0' : '1'; // 生成代码
            c = p;
        }
        strcpy(HC[i].bits, &cd[start]);     // 拷贝到编码表中
        HC[i].len = N-start;                // 保存编码长度
    }
}

int main(void) {
    HuffmanTree HT;
    CHuffmanTree(HT); // 输入书中 p.135 例子: d:9,g:8,h:12,a:6,c:7,f:27,b:15,e:16
    HuffmanCode HC;
    HuffmanEncoding(HT, HC);

    /**
     * huffman encoding:
     * d: 001
     * g: 000
     * h: 010
     * a: 0110
     * c: 0111
     * f: 10
     * b: 110
     * e: 111
     */
    printf("huffman encoding:\n");
    for (int i = 1; i <= N; i++) {
        printf("%c: ", HC[i].ch);
        for (int j = 0; j < HC[i].len; j++) {
            printf("%c", HC[i].bits[j]);
        }
        printf("\n");
    }
}