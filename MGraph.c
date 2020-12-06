#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "CirQueue.c"

/**
 * p.145: 图的邻接矩阵表示
 */
#define N 50                // 最大顶点数
#define MAX 55525           // 定义最大值. 如果用真最大值, Dijkstra 算法中会溢出.

typedef char VertexType;    // 顶点数据类型
typedef int AdjMatrix;

typedef struct {
    VertexType vexs[N];     // 顶点数组
    AdjMatrix arcs[N][N];   // 邻接矩阵
} MGraph;

/**
 * p.145: 创建具有 n 个顶点, e 条边的无向图 G
 * 由于无向图的邻接矩阵是对称的, 可采用压缩存储仅存储主对角线以下的元素.
 *
 * 性能:
 * 时间复杂度为 O(n^2)
 */
void CreateMGraph(MGraph *G, int n, int e) {
    int i, j, k, w;
    // scanf("%d, %d ", &n, &e);            // @note: 从 main 中读入, 以便测试用例共用
    for (i = 0; i < n; i++) {               // 读入顶点信息
        char ch;
        scanf("%c", &ch);
        G->vexs[i] = ch;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            G->arcs[i][j] = MAX;        // 初始化邻接矩阵元素为无穷大
        }
    }
    for (k = 0; k < e; k++) {               // 读入 e 条边, 建立邻接矩阵
        scanf(" %d, %d, %d", &i, &j, &w);   // 读入一条边的两端顶点序号及权 w
        G->arcs[i][j] = w;
        G->arcs[j][i] = w;                  // 置矩阵对称元素权值
    }

    printf("G:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (G->arcs[i][j] == MAX) {
                printf("- ");
            } else {
                printf("%d ", G->arcs[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * p.149: 从顶点 i 开始, 深度优先遍历具有 n 个顶点的图 G
 *
 * 性能:
 * 需要对 n 个顶点进行访问, 时间复杂度为 O(n^2)
 */
void DFS(MGraph G, int i, int n) {
    static int visited[N];
    int j;
    printf("v%d->", i);         // 访问顶点 i
    visited[i] = 1;             // 标记为已访问
    for (j = 0; j < n; j++) {   // 依次搜索 i 的每个邻接点 j
        if (G.arcs[i][j] != MAX && ! visited[j]) { // 若 j 未被访问, 则开始从 j 开始递归访问
            DFS(G, j, n);
        }
    }
}

/**
 * p.150: 从顶点 i 开始广度优先遍历具有 n 个顶点的图 G
 *
 * 性能:
 * 与 DFS 类似, 时间复杂度为 O(n^2), 空间复杂度为 O(n)
 */
void BFS(MGraph G, int i, int n) {
    int visited[N] = {false};
    CirQueue Q;         // 用于记录被访问过的顶点
    int k, j;
    InitQueue(&Q);
    printf("v%d->", i); // 访问 i
    visited[i] = 1;     // 标记 i 为已访问
    EnQueue(&Q, i);
    while (! QueueEmpty(&Q)) {
        k = DeQueue(&Q);
        for (j = 0; j < n; j++) {   // 依次搜索 k 的每个可能的邻接点
            if (G.arcs[k][j] != MAX && ! visited[j]) {
                printf("v%d->", j);
                visited[j] = 1;
                EnQueue(&Q, j);
            }
        }
    }
}

typedef struct edge {
    VertexType ver;
    int lowcost;
} minedge[N];

/**
 * p.155: Prim 算法求 MST
 *
 * @note 书中代码实在对不上号, 可能是本身就有错误. 略.
 *
 * 性能:
 * 时间复杂度为 O(n^2)
 */
void Prim(MGraph G, VertexType u, int n) {

}

/**
 * p.157: Kruskal 算法求 MST: 书中只给出了抽象算法. 略
 *
 * 性能:
 * 时间复杂度为 O(eloge)
 */
void Kruskal(G) {

}

/**
 * p.159: Dijkstra 算法求单源 v0 最短路径
 *
 * 注意:
 * - 书中顶点索引从 1 开始, 为了兼容其他示例, 这里保持与其他示例代码一致, 从 0 开始
 * - 书中很多错误代码, 这里做了纠正
 */
bool S[N];
int dist[N];
int path[N];
void Dijkstra(MGraph G, int v0, int n) {
    int v, i, w, min;
    // 初始化 S, dist, path
    for (v = 0; v < n; v++) {
        S[v] = false;
        dist[v] = G.arcs[v0][v];
        if (dist[v] < MAX) {
            path[v] = v0;       // v0 是 v 的前趋
        } else {
            path[v] = 0;        // v 无前趋
        }
    }
    // S 初始只有源点, 源点到源点距离为 0
    dist[v0] = 0;
    S[v0] = true;
    // 求 v1 到其他各点最短路径
    for (i = 1; i < n; i++) {
        min = MAX;
        // 找出下一条最短路径的顶点 v
        for (w = 0; w < n; w++) {
            if (! S[w] && dist[w] < min) {
                v = w;
                min = dist[w];
            }
        }
        // 标记已找到到 v 的最短路径
        S[v] = true;
        // 重新计算其他各点的最短距离
        for (w = 0; w < n; w++) {
            if (! S[w] && (dist[v] + G.arcs[v][w] < dist[w])) {
                dist[w] = dist[v] + G.arcs[v][w];
                path[w] = v;
            }
        }
    }
}

int main(void) {
    MGraph G;
    int n, e;
    // p.160 图 6.720 例子: 5 个顶点, 7 条边.
    // 注意: 与书中图不一样, 这里生成的是无向图, 且顶点序号从 0 开始.
    //
    // 输入:
    // 5,7
    // abcde
    // 0,1,10
    // 0,2,3
    // 0,3,20
    // 1,3,5
    // 2,1,2
    // 2,4,15
    // 3,4,9
    printf("input n, e:");
    scanf("%d, %d ", &n, &e);
    CreateMGraph(&G, n, e);

    printf("\ndfs:");
    DFS(G, 0, n); // dfs:v0->v1->v2->v4->v3->

    printf("\nbfs:");
    BFS(G, 0, n); // bfs:v0->v1->v2->v3->v4->

    //   S dist    path:
    // 0:1 0   0
    // 1:1 5   2
    // 2:1 3   0
    // 3:1 10  1
    // 4:1 18  2
    Dijkstra(G, 0, n);
    printf("\n\n  S\tdist\tpath:\n");
    for (int i = 0; i < n; i++) {
        printf("%d:%d\t%d\t%d\n", i, S[i], dist[i], path[i]);
    }
}