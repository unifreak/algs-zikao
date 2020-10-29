/**
 * p.125: 树 (双亲表示法)
 */
#define MAXTREESIZE 100

typedef struct {
    DataType data;
    int parent;
} PTNode;

typedef struct {
    PTNode nodes[MAXTREESIZE];
    int n;
} PTree;

/**
 * p.126: 树 (孩子链表法)
 */
// 孩子链表结点类型
typedef struct cnode {
    int child; // 孩子结点在指针数组中的序号
    struct cnode *next;
} CNode;

// 指针数组结点类型
typedef struct {
    DataType data;
    CNode *firstchild;  // 孩子结点头指针
} PANode;

// 指针数组
typedef struct {
    PANode nodes[MAXTREESIZE];
    int n, r;   // n 为结点数, r 为根结点在指针数组中的位置 (下标)
} CTree;

