#include <stdio.h>
#include "LinkList.c"

#define N 100

// 记录
typedef int KeyType;        // 关键字
typedef char InfoType;      // 其他信息
typedef struct {
    KeyType key;            // 关键字
    InfoType otherinfo;     // 其他信息
} RecType;

// 记录表 (顺序结构)
typedef RecType SeqList[N+1]; // 0 元素用作哨兵单元

// 结点

/**
 * p.170: 直接插入排序 (稳定, 就地)
 *
 * 性能:
 * 时间复杂度
 *     内循环的每趟排序中, 最多可能进行 i 次比较, 移动 i-1+2=i+1 个记录 (内循环前和后做两次移动)
 *     - 最坏: O(n^2)
 *     - 最好: O(n)
 *     - 平均: O(n^2)
 * 空间复杂度: O(1)
 */
void InsertSort(SeqList R, int n) {
    int i, j;
    for (i = 2; i <= n; i++) {
        if (R[i].key < R[i-1].key) { // 若当前记录小于有序区中所有记录, 则移动到有序区合适位置
            R[0] = R[i];             // 当前记录复制为哨兵
            for (j = i-1; R[0].key < R[j].key; j--) {   // 把比之大的记录逐个后移, 腾出合适位置
                R[j+1] = R[j];
            }
            R[j+1] = R[0];           // 插入到合适位置
        }
    }
}

/**
 * p.172: 希尔排序 -- 一趟插入排序
 * dk 为当前增量
 *
 * 性能:
 * 无论理论还是实践都以证明, 总比较和移动次数比直接插入排序小得多, 且记录越多越明显.
 * 依赖于增量序列, 但如何选择增量序列以达到最佳性能, 这个问题至今未能从数学上解决
 * 应尽量避免各个增量互为倍数的情况
 */
void ShellInsert(SeqList R, int dk, int n) {
    int i, j;
    for (i = dk+1; i <= n; i++) {
        if (R[i].key < R[i-dk].key) {
            R[0] = R[i];
            j = i - dk;
            while (j > 0 && R[0].key < R[j].key) {
                R[j + dk] = R[j];
                j = j - dk;
            }
            R[j + dk] = R[0];
        }
    }
}

/**
 * p.172: 希尔排序 (不稳定) -- 进行排序
 * d 为增量序列
 * t 为增量个数
 */
void ShellSort(SeqList R, int d[], int t, int n) {
    int k;
    for (k = 0; k < t; k++) {
        ShellInsert(R, d[k], n);
    }
}

/**
 * p.173: 冒泡排序 (稳定)
 *
 * 性能:
 * - 最好情况 (有序): 一趟扫描完成, 比较 n-1 次, 没有移动, 时间复杂度为 O(n)
 * - 最坏情况 (反序): n-1 趟排序, 每趟 n-i 次比较, 每次比较移动记录 3 次进行交换
 * - 平均情况: 时间复杂度为 O(n^2)
 */
void BubbleSort(SeqList R, int n) {
    int i, j, flag; // flag 标记是否有交换发生, 用于提前结束排序
    for (i = 1; i < n; i++) {
        flag = 0;
        for (j = n; j >= i+1; j--) {
            if (R[j].key < R[j-1].key) { // 比较, 交换
                R[0] = R[j-1];
                R[j-1] = R[j];
                R[j] = R[0];
                flag = 1;
            }
        }
        if (flag == 0) {
            return;
        }
    }
}

/**
 * p.174: 双向冒泡排序
 *
 * @note:
 * - 书中变量名 NoSwap 改为 hasSwap
 * - 书中临时变量 t 替代为 R[0]
 */
void DbubbleSort(SeqList R, int n) {
    int i = 1, j;
    int hasSwap = 1;    // 是否有交换发生. 用于提前结束排序
    while (hasSwap) {
        hasSwap = 0;
        // 自底向上扫描, 小者上浮
        for (j = n-i+1; j >= i+1; j--) {
            if (R[j].key < R[j-1].key) {
                R[0] = R[j];
                R[j] = R[j-1];
                R[j-1] = R[0];
                hasSwap = 1;
            }
        }
        // 自顶向下扫描, 大者下沉
        for (j = i+1; j <= n-i; j++) {
            if (R[j].key > R[j+1].key) {
                R[0] = R[j];
                R[j] = R[j+1];
                R[j+1] = R[0];
                hasSwap = 1;
            }
        }
        i++;
    }
}

/**
 * p.175: 快速排序 -- 一次划分
 */
int Partition(SeqList R, int i, int j) {
    RecType x = R[i];   // 用区间内第一个记录作为基准记录
    while (i < j) {
        while (i < j && R[j].key >= x.key) { // 从 j 所指位置向前搜索较 x 小的第一个记录
            j--;
        }
        if (i < j) {                         // 存入 i 所指位置
            R[i] = R[j];
            i++;
        }
        while (i < j && R[i].key <= x.key) { // 从 i 所指位置向后搜索较 x 大的第一个记录
            i++;
        }
        if (i < j) {                         // 存入 j 所指位置
            R[j] = R[i];
            j--;
        }
    }
    R[i] = x; // 基准记录存入合适位置
    return i;
}

/**
 * p.177: 快速排序 (不稳定) -- 进行排序
 *
 * 性能:
 * 时间性能优于其他排序算法. 平均时间复杂度为 O(nlogn). 但是当文件基本有序时, 复杂度反而增加了.
 * 空间性能, 因为需要递归, 需要一个栈空间, 栈的大小取决于递归调用的深度. 附加空间为 O(logn).
 */
void QuickSort(SeqList R, int low, int high) {
    int p; // 记录区间边界
    if (low < high) {
        p = Partition(R, low, high); // 做一次划分排序
        QuickSort(R, low, p-1);      // 对左区间递归排序
        QuickSort(R, p+1, high);     // 对右区间递归排序
    }
}

/**
 * p.179: 直接选择排序 (不稳定): 顺序结构
 *
 * 性能:
 * 需要进行 n-1 次选择和交换. 每次选择需要做 n-i 次比较, 移动 3 次做交换.
 * 平均时间复杂度为 O(n^2)
 */
void SelectSort(SeqList R, int n) {
    int i, j, k;
    for (i = 1; i < n; i++) {           // 做 n-1 趟排序
        k = i;                          // k 用于记录最小记录的位置
        for (j = i+1; j <= n; j++) {    // 找出最小记录的位置
            if (R[j].key < R[k].key) {
                k = j;
            }
        }
        if (k != i) {                   // 交换
            R[0] = R[i];
            R[i] = R[k];
            R[k] = R[0];
        }
    }
}

/**
 * p.180: 直接选择排序 -- 链表结构, 交换结点数据域和关键字域值
 *
 * 性能:
 * 时间复杂度为 O(n^2)
 */
void LselectSort1(LinkList head) {
    ListNode *p, *r, *s;
    ListNode q;
    p = head;
    while (p != NULL) {     // 假设链表不带头结点
        s = p;              // s 指向最小结点
        r = p->next;
        while (r != NULL) { // 找出最小结点, 并用 s 指向它
            if (r->data < s->data) {
                s = r;
            }
            r = r->next;
        }
        if (s != p) {       // 需要交换
            q = (*p);
            p->data = s->data;
            s->data = q.data;
        }
        p = p->next;
    }
}

/**
 * p.180: 直接选择排序 -- 链表结构, 脱链并建立新链表, 避免结点域值交换.
 *
 * 性能:
 * 时间复杂度为 O(n^2)
 */
LinkList LselectSort2(LinkList head) {
    ListNode *p, *q, *r, *s, *t, *t1;
    t = NULL;   // 置空新表, 采用尾插法建立新链表
    while (head != NULL) {
        s = head;   // s 指向最小结点
        p = head;   // p 指向当前结点
        q = NULL;   // q 指向 p 前趋结点
        r = NULL;   // r 指向 s 前趋结点, 用于后续脱链操作
        // 查找最小结点, 并让 s 指向它
        while (p != NULL) {
            if (p->data < s->data) {
                s = p;
                r = q;
            }
            q = p;
            p = p->next;
        }

        if (s == head) { // 没有更小的结点, 继续下次循环
            head = head->next;
        } else { // 有更小的结点, s 脱链
            r->next = s->next;
        }

        // 将找到的最小结点用尾插法插入到新链表中
        if (t == NULL) {
            t = s;
            t1 = t;
        } else {
            t1->next = s;
            t1 = s;
        }
    }

    t1->next = NULL;
    return t;
}

/**
 * p.183: 堆排序 -- 使用筛选法, 将 i..h 调整为大堆
 */
void Sift(SeqList R, int i, int h) {
    int j;
    RecType x = R[i]; // x 存储待筛结点
    j = 2*i;          // 左孩子
    while (j <= h) {  // 有左孩子, 则循环
        // 左孩子和右孩子选出较大者
        if (j < h && R[j].key < R[j+1].key) {
            j++;
        }
        // 找到了 x 的最终位置, 终止循环
        if (x.key >= R[j].key) {
            break;
        }
        // 大者放到双亲位置, 继续循环
        R[i] = R[j];
        i = j;
        j = 2*i;
    }
    // 将被筛结点放到最终位置
    R[i] = x;
}

/**
 * p.183: 堆排序 (不稳定)
 *
 * 性能:
 * 需要 n-1 趟选择
 * 每趟选择是在堆的基础上对根结点进行筛选运算实现的, 其时间复杂度为 O(logn)
 * 所以堆排序的时间复杂度为 O(nlogn)
 */
void HeapSort(SeqList R, int n) {
    int i;
    // 对初始数组 1..n 建立大根堆
    for (i = n/2; i > 0; i--) {
        Sift(R, i, n);
    }
    // 对 1..i 进行堆排序, 共 n-1 趟
    for (i = n; i > 1; i--) {
        R[0] = R[1]; // 最大者排到最后
        R[1] = R[i];
        R[i] = R[0];
        Sift(R, 1, i-1); // 对无序区 1..i-1 建立大根堆
    }
}

/**
 * p.185: 归并排序 -- 归并
 * 对有序的 R[low..m] 和 R[m+1..high] 归并为有序的 MR[low..high]
 *
 */
void Merge(SeqList R, SeqList MR, int low, int m, int high) {
    int i, j, k;
    i = low;
    j = m+1;
    k = low;
    while (i <= m && j <= high) {
        if (R[i].key <= R[j].key) { // 左边的记录小, 把左边的记录放入 MR, 然后对比下一对
            MR[k++] = R[i++];
        } else {                    // 右边的记录小...
            MR[k++] = R[j++];
        }
    }
    while (i <= m)  {   // 将左边中剩余的记录复制到 MR
        MR[k++] = R[i++];
    }
    while (j <= high) { // 将右边中剩余的记录复制到 MR
        MR[k++] = R[j++];
    }
}

/**
 * p.186: 归并排序 -- 一趟排序
 * 对 R[1..n] 做一趟归并排序. len 为子文件长度.
 *
 * 性能:
 * 通过代码可知, 每趟的比较次数均小于等于记录的移动次数, 而移动次数均等于文件中记录的个数 n.
 * 故时间复杂度为 O(n)
 */
void MergePass(SeqList R, SeqList MR, int len, int n) {
    int i, j;
    // 循环做两两合并
    //
    // 注意这里的边界算法, 以文件 {a, b, c, d, e} 为例, 此时 n=5, len 假设为 1
    // 则应先归并 [a] [b]. 然后归并 [c] [d], 剩下 [e].
    //
    // i 是当前归并的起始位置 (传入 Merge() 的 low)
    // 2*len 两个子文件的长度
    // i+2*len 则是下一次归并的起始位置
    // i+2*len-1 则是当前归并的末尾位置 (传入 Merge() 的 high)
    // i+len-1 则是两两归并的文件中, 第一个文件的末尾位置 (传入 Merge() 的 m)
    for (i = 1; i+2*len-1 <= n; i = i+2*len) {
        Merge(R, MR, i, i+len-1, i+2*len-1);
    }
    if (i+len-1 < n) { // 尚有两个子文件, 其中最后一个长度小于 len
        Merge(R, MR, i, i+len-1, n);
    } else {           // 文件个数为奇数, 最后一个子文件复制到 MR 中
        for (j = i; j <= n; j++) {
            MR[j] = R[j];
        }
    }
}

/**
 * p.186: 归并排序 -- 整个排序 (稳定)
 *
 * 性能:
 * 已知一趟排序时间复杂度为 O(n). 共需要进行 logn 趟.
 * 故时间复杂度为 O(nlogn)
 */
void MergeSort(SeqList R, SeqList MR, int n) {
    int len = 1;
    while (len < n) { // R 和 MR 来回用
        MergePass(R, MR, len, n);
        len = len * 2;
        MergePass(MR, R, len, n); // 最终还是复制给 R, R 得到最终排序结果
        len = len*2;
    }
}

void dump(SeqList R, int n, char* name) {
    printf("\n%s:\n", name);
    for (int i = 1; i <= n; i++) {
        printf("%d: %d %c\n", i, R[i].key, R[i].otherinfo);
    }
}

int main(void) {
    SeqList R1 = {{}, {46, ' '}, {39, ' '}, {17, ' '}, {23, ' '}, {28, ' '}, {55, ' '}, {18, ' '}, {46, ' '}};
    InsertSort(R1, 8);
    dump(R1, 8, "Insert");

    SeqList R2 = {{}, {46, ' '}, {39, ' '}, {17, ' '}, {23, ' '}, {28, ' '}, {55, ' '}, {18, ' '}, {46, ' '}};
    int dk[3] = {5, 2, 1};
    ShellSort(R2, dk, 3, 8);
    dump(R2, 8, "Shell");

    SeqList R3 = {{}, {46, ' '}, {39, ' '}, {17, ' '}, {23, ' '}, {28, ' '}, {55, ' '}, {18, ' '}, {46, ' '}};
    BubbleSort(R3, 8);
    dump(R3, 8, "Bubble");

    SeqList R4 = {{}, {46, ' '}, {39, ' '}, {17, ' '}, {23, ' '}, {28, ' '}, {55, ' '}, {18, ' '}, {46, ' '}};
    DbubbleSort(R4, 8);
    dump(R4, 8, "Dbuble");

    SeqList R5 = {{}, {46, ' '}, {39, ' '}, {17, ' '}, {23, ' '}, {28, ' '}, {55, ' '}, {18, ' '}, {46, ' '}};
    QuickSort(R5, 1, 8);
    dump(R5, 8, "Quick");

    SeqList R6 = {{}, {46, ' '}, {39, ' '}, {17, ' '}, {23, ' '}, {28, ' '}, {55, ' '}, {18, ' '}, {46, ' '}};
    SelectSort(R6, 8);
    dump(R6, 8, "Select");

    LinkList L1 = CreateListR(); // 输入: adefbbcg
    LselectSort1(L1);
    dumpLinkList(L1); // |0:a| -> |1:b| -> |2:b| -> |3:c| -> |4:d| -> |5:e| -> |6:f| -> |7:g| ->

    LinkList L2 = CreateListR(); // 输入: adefbbcg
    LinkList L3 = LselectSort2(L2);
    dumpLinkList(L3); // // |0:a| -> |1:b| -> |2:b| -> |3:c| -> |4:d| -> |5:e| -> |6:f| -> |7:g| ->

    SeqList R7 = {{}, {46, ' '}, {39, ' '}, {17, ' '}, {23, ' '}, {28, ' '}, {55, ' '}, {18, ' '}, {46, ' '}};
    HeapSort(R7, 8);
    dump(R7, 8, "Heap");

    SeqList R8 = {{}, {46, ' '}, {39, ' '}, {17, ' '}, {23, ' '}, {28, ' '}, {55, ' '}, {18, ' '}, {46, ' '}};
    SeqList MR;
    MergeSort(R8, MR, 8);
    dump(R8, 8, "Merge");


}