#include <stdlib.h>
#include <stdio.h>

/**
 * p.122: 线索链表 (线索二叉树)
 */
typedef char DataType;

typedef struct node {
    DataType data;
    int ltag, rtag; // 指示左右指针域是否是线索指针
    struct node *lchild, *rchild;
} BinThrNode;

typedef BinThrNode *BinThrTree;


/**
 * 根据广义表表示创建线索二叉树 (改自 BinTree.c)
 */
BinThrNode *CreateTree(char *str) {
    BinThrNode *St[100];    // 用作栈, 栈顶始终指向当前处理的父结点
    BinThrNode *p = NULL;
    int top, k, j = 0;      // top 指示栈顶, k 指示下一个结点是左孩子还是右孩子
    top = -1;               // 置空栈
    char ch = str[j];
    BinThrNode *b = NULL;   // 最终生成的树的根
    while (ch != '\0') {    // 循环读入广义表表示字符
        switch (ch) {
            case '(': {     // 遇到 (, 代表子树开始
                top++;
                St[top] = p; // 将栈顶指向上次生成的新结点, 代表当前所处理的子树的父结点
                k = 1;       // 下一项为左孩子
                break;
            };
            case ')': top--; break; // 子树处理结束, 回到上层
            case ',': k = 2; break; // 下一项为右孩子
            default: {
                p = (BinThrNode *) malloc(sizeof(BinThrNode)); // 创建新结点
                p->data = ch;
                p->lchild = p->rchild = NULL;
                if (b == NULL) {    // 如果尚未生成根结点, 则生成
                    b = p;
                } else {            // 否则将新生成的结点挂到父结点上
                    switch (k) {
                        case 1: St[top]->lchild = p; break;
                        case 2: St[top]->rchild = p; break;
                    }
                }
            }
        }
        j++;
        ch = str[j];
    }
    return b;
}

/**
 * p.123: 按中序线索化
 *
 * 该算法与中序遍历算法类似, 只是将遍历算法中访问结点的操作改为建立线索操作
 * 以类似方法, 也可以得到前序线索化和后序线索化的算法
 */
void InorderThread(BinThrTree bt) {
    static BinThrNode *pre = NULL;  // 指向前趋结点的指针, 保存刚访问过的结点
    if (bt != NULL) {               // 当二叉树为空时结束递归
        InorderThread(bt->lchild);  // 左子树线索化
        if (bt->lchild == NULL) {
            bt->ltag = 1;
        } else {
            bt->ltag = 0;
        }
        if (bt->rchild == NULL) {
            bt->rtag = 1;
        } else {
            bt->rtag = 0;
        }
        if (pre) {
            if (pre->rtag == 1) {
                pre->rchild = bt;   // 给前趋结点加后继线索
            }
            if (bt->ltag == 1) {
                bt->lchild = pre;   // 给当前结点加前趋线索
            }
        }
        pre = bt;
        InorderThread(bt->rchild);  // 右子树线索化
    }
}

/**
 * p.124: 在中序线索二叉树上求结点 p 的中序后继结点
 *
 * 分两种情况:
 * - 若 p 的 rtag=1, 表明 p->rchild 即其右线索, 即要找的后继结点
 * - 若 p 的 rtag=1, 则它的中序后继结点必是其右子树第一个中序遍历到的结点 (左子树中最左下的结点)
 *
 * 性能:
 * 时间复杂度不超过二叉树的高度, 即 O(h)
 */
BinThrNode *InorderNext(BinThrNode *p) {
    if (p->rtag == 1) {
        return p->rchild;
    } else {
        p = p->rchild;
        while (p->ltag == 0) { // 沿左指针链往下查找
            p = p->lchild;
        }
        return p;
    }
}

/**
 * p.124: 中序遍历线索二叉树
 *
 * 首先从根结点沿左指针链向下查找, 找到一个做线索标识为 1 的结点为止, 它就是中序序列的第一个结点
 * 访问该结点, 然后就可以利用 InorderNext() 依次找结点的后继结点
 */
void TInorderThrTree(BinThrTree bt) {
    BinThrNode *p;
    if (bt != NULL) {
        p = bt;
        while (p->ltag == 0) {      // 找到起始结点
            p = p->lchild;
        }
        do {
            printf("%c", p->data);  // 访问结点
            p = InorderNext(p);     // 查找中序后继结点
        } while (p != NULL);
    }
}

int main(void) {
    /**
    *          a
    *        /  \
    *      b     c
    *       \
    *        d
    *       / \
    *      e   f
    */
    char *tree = "(a(b(,d(e,f)),c))";
    BinThrTree t = CreateTree(tree);

    InorderThread(t);
    TInorderThrTree(t); // bedfac
}