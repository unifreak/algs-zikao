#include <stdlib.h>
#include <stdio.h>
#include "CirQueue.c"
#include "SeqStack.c"

// p.146: 图的邻接表表示
// ===============================================================

/**
 * 对于无向图而言, 顶点 v 的邻接表中的每个表结点对应于与 v 相关联的一条边.
 * 对于有向图而言, 则对应于顶点 v 为起点射出的一条边.
 * 因此将无向图邻接表称为 **边表**.
 * 有向图的邻接表称为 **出边表**. 并且还需要建立一个逆邻接表 (**入边表**)
 * 将邻接表的表头向量称为 **顶点表**.
 *
 * 图的邻接表表示不是唯一的, 具体链接次序与边的输入次序和生成算法有关.
 * 这也导致 DFS 和 BFS 得到的遍历序列也可不同.
 *
 * 对于有 n 个顶点和 e 条边的图:
 * - 若是无向图, 则它的邻接表共有 n 个头结点和 2e 个表结点. 顶点 v 的度即其链表中的结点数.
 * - 若是有向图, 链表的结点数只是其出度, 为了求入度, 必须遍历整个邻接表.
 *
 * 要判断任意两个顶点之间是否相连, 需搜索两个顶点中的任一链表. 不如邻接矩阵表示法方便.
 */
#define N 20                // 最大顶点数

typedef char VertexType;    // 顶点类型

// 边表结点类型
// 若要表示带权图的结点, 则需要在边表的结点中增加一个存储权值的数据域
typedef struct node {
    int adjvex;             // 顶点序号
    struct node *next;      // 指向下一条边的指针
} EdgeNode;

// 顶点表结点类型, 邻接表
typedef struct vnode {
    VertexType vertex;      // 顶点域
    EdgeNode *link;         // 边表头指针
} VNode, Adjlist[N];

// 邻接表表示的图
typedef Adjlist ALGraph;

/**
 * p.147: 创建一个具有 n 个顶点和 e 条边的无向图 GL
 * 建立有向图类似, 只是更简单: 仅需要生成一个邻接点序号为 j 的边表结点
 *
 * 性能:
 * 时间复杂度为 O(n+e)
 */
void CreateGraph(ALGraph GL, int n, int e) {
    int i, j, k;
    EdgeNode *p;

    // 建立顶点表
    for (i = 0; i < n; i++) {
        GL[i].vertex = getchar();   // 读入顶点信息
        GL[i].link = NULL;          // 边表头指针置空
    }

    // 采用头插法建立每个顶点的邻接表
    for (k = 0; k < e; k++) {
        scanf("%d, %d", &i, &j);     // 读入一对顶点序号表示的边

        // 插入到 i 的边表头部
        p = (EdgeNode *) malloc(sizeof(EdgeNode));
        p->adjvex = j;
        p->next = GL[i].link;
        GL[i].link = p;

        // 插入到 j 的边表头部
        p = (EdgeNode *) malloc(sizeof(EdgeNode));
        p->adjvex = i;
        p->next = GL[j].link;
        GL[j].link = p;
    }
}

/**
 * p.149: 从顶点 i 开始, 深度优先遍历图 G
 *
 * 性能:
 * 需要将边表中所有 O(e) 个结点搜索一遍, 时间复杂度为 O(n+e)
 */
void DFS(ALGraph G, int i) {
    static int visited[N];
    EdgeNode *p;
    int j;
    printf("v%d->", i);         // 访问顶点 i
    visited[i] = 1;             // 标记 i 为已访问
    p = G[i].link;              // 取 i 表头指针
    while (p != NULL) {         // 依次搜索顶点 i 的每个邻接点
        j = p->adjvex;          // 找到一个邻接点 j
        if (! visited[j]) {     // 若 j 未被访问过, 则开始递归访问
            DFS(G, j);
        }
        p = p->next;            // 下一个邻接点
    }
}

/**
 * p.152: 深度优先遍历的非递归算法
 */
void DFS2(ALGraph G, int i, int n) {
    EdgeNode *S[N];                  // 用作栈
    EdgeNode *p;
    int visited[N], top = 0;        // top 为栈顶
    printf("v%c->", G[i].vertex);   // 跟其他遍历示例不同, 这个示例中, 访问的是顶点的数据
    visited[i] = 1;
    p = G[i].link;
    while (top > 0 || p != NULL) {  // 栈非空或 p 非空
        while (p) {
            if (visited[p->adjvex]) {
                p = p->next;
            } else {
                printf("v%c->", G[p->adjvex].vertex);
                visited[p->adjvex] = 1;
                S[++top] = p;       // 入栈
                p = G[p->adjvex].link;
            }
        }
        if (top != 0) {
            p = S[top--];
            p = p->next;
        }
    }
}

/**
 * p.151: 从顶点 i 开始广度优先遍历有 n 个顶点的图 G
 *
 * 性能:
 * 与 DFS 类似, 时间复杂度为 O(n+e), 空间复杂度为 O(n)
 */
void BFS(ALGraph G, int i, int n) {
    int j, k;
    static int visited[N];
    CirQueue Q;
    InitQueue(&Q);
    EdgeNode *p;
    printf("v%d->", i);         // 访问顶点 i
    visited[i] = 1;             // 标记 i 为已访问
    EnQueue(&Q, i);
    while (! QueueEmpty(&Q)) {
        k = DeQueue(&Q);
        p = G[k].link;
        while (p != NULL) {
            j = p->adjvex;
            if (! visited[j]) {
                printf("v%d->", j);
                visited[j] = 1;
                EnQueue(&Q, j);
            }
            p = p->next;
        }
    }
}

/**
 * p.164: 拓扑排序
 *
 * 实现: 用一维数组 inde 存储每个顶点入度值.
 * 用栈暂存所有入度为零的顶点, 以后每次选取入度为零的顶点时, 只需出栈操作即可.
 * 删除顶点及其边的操作, 只需要检查出栈的顶点的出边表, 把每条出边终点的入度减一, 若入度为零, 则将终点入栈.
 *
 * 性能:
 * 实际上是对图进行遍历的过程, 加上建立入度数组需要访问表头数组中的每个域和其单链表中的每个结点
 * 时间复杂度为 O(n+e)
 *
 * @todo:
 * - 有向图的 CreateGraph()
 * - 测试用例
 * - 如何让 SeqStack 的 DataType 动态兼容?
 */
void TopuSort(ALGraph G, int n) {
    int i, j, m = 0;            // m 用来统计输出的顶点数
    int inde[N];                // 入度数组
    SeqStack S;
    EdgeNode *p;
    // 初始化入度数组
    for (i = 0; i < n; i++) {
        inde[i] = 0;
    }
    for (i = 0; i < n; i++) {
        p = G[i].link;
        while (p) {
            inde[p->adjvex]++;
            p = p->next;
        }
    }
    // 将入度为零的顶点入栈
    InitStack(&S);
    for (i = 0; i < n; i++) {
        if (inde[i] == 0) {
            Push(&S, i);
        }
    }
    // 拓扑排序
    while (! StackEmpty(&S)) {
        i = Pop(&S);
        printf("v%d ", i);
        m++;
        p = G[i].link;
        while (p) {             // 扫描顶点 i 的出边表
            j = p->adjvex;
            inde[j]--;          // vj 入度减一, 相当于删除边 <vi, vj>
            if (inde[j] == 0) { // 若 vj 入度为零则入栈
                Push(&S, j);
            }
            p = p->next;
        }
    }
    if (m < n) {
        printf("The Graph has a cycle!\n");
    }
}

int main(void) {
    ALGraph GL;
    // 输入 p.145 图 6.7 例子: 4 个顶点, 5 条边
    // abcd
    // 0,2
    // 0,3
    // 2,3
    // 2,1
    // 1,3
    CreateGraph(GL, 4, 5);

    printf("\ndfs:");
    DFS(GL, 0);     // v0->v3->v1->v2->
    printf("\ndfs with stack:"); // va->vd->vb->vc->
    DFS2(GL, 0, 4);

    printf("\nbfs:");
    BFS(GL, 0, 4);  // v0->v3->v2->v1->
}