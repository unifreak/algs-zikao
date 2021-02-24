#include <stdlib.h>
#include <stdio.h>
#include "SeqStack.c"

// 二叉树
// ===============================================================

/**
 * p.111: 二叉链表
 */
typedef char DataType;

typedef struct node {
    DataType data;
    struct node *lchild, *rchild;
} BinTNode;

typedef BinTNode *BinTree;

/**
 * p.113: 根据广义表表示 str 生成二叉树
 *
 * 注意广义表的表示形式, 如 (A(B(,D(E,F)), C))
 * - 结点后的括号内结点即其子树
 * - 其中靠近左括号的结点是在左子树上
 * - 逗号右边的结点是在右子树上
 * 其生成的树为:
 *
 *          a
 *        /  \
 *      b     c
 *       \
 *        d
 *       / \
 *      e   f
 */
BinTNode *CreateTree(char *str) {
    BinTNode *St[100];  // 用作栈, 栈顶始终指向当前处理的父结点
    BinTNode *p = NULL;
    int top, k, j = 0;  // top 指示栈顶, k 指示下一个结点是左孩子还是右孩子
    top = -1;           // 置空栈
    char ch = str[j];
    BinTNode *b = NULL; // 最终生成的树的根
    while (ch != '\0') { // 循环读入广义表表示字符
        switch (ch) {
            case '(': {  // 遇到 (, 代表子树开始
                top++;
                St[top] = p; // 将栈顶指向上次生成的新结点, 代表当前所处理的子树的父结点
                k = 1;       // 下一项为左孩子
                break;
            };
            case ')': top--; break; // 子树处理结束, 回到上层
            case ',': k = 2; break; // 下一项为右孩子
            default: {
                p = (BinTNode *) malloc(sizeof(BinTNode)); // 创建新结点
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
 * p.114: 通过按编号输入结点值的方式创建二叉树
 *
 * 用 @ 代表虚结点, # 代表输入结束. 如输入: abc@d@@@@ef#, 则生成的树为
 *
 *          a
 *        /  \
 *      b     c
 *       \
 *        d
 *       / \
 *      e   f
 *
 * 注意结点编号从 1 开始.
 */
BinTree CreateBinTree(BinTree bt) {
    BinTNode *Q[100]; // 用作队列, 先进先出的指示新结点当前的父结点
    BinTNode *s;      // 新结点
    int front = 1, rear = 0; // front 指向队头, 父结点. rear 指向队尾, 也代表当前结点编号
    char ch;
    bt = NULL;        // 置空二叉树
    ch = getchar();
    while (ch != '#') {
        s = NULL;
        if (ch != '@') {    // 不是虚结点: 生成新结点
            s = (BinTNode *) malloc(sizeof(BinTNode));
            s->data = ch;
            s->lchild = s->rchild = NULL;
        }
        rear++;             // 新结点编号
        Q[rear] = s;        // 指向新结点
        if (rear == 1) {    // 是根结点
            bt = s;
        } else {
            if (s != NULL && Q[front] != NULL) { // 新结点及其双亲都不是虚结点
                if (rear % 2 == 0) {        // 编号为偶数, 是左孩子
                    Q[front]->lchild = s;
                } else {                    // 编号为奇数, 是右孩子
                    Q[front]->rchild = s;
                }
            }
            if (rear % 2 != 0) {            // 新结点是一个右孩子, 当前父结点处理完毕
                front++;                    // 队列中下一个结点成为新的待处理父结点
            }
        }
        ch = getchar();
    }
    return bt;
}

// 递归遍历
// ===============================================================

/**
 * p.115: 前序遍历
 */
void Preorder(BinTree bt) {
    if (bt != NULL) {
        printf("%c", bt->data);
        Preorder(bt->lchild);
        Preorder(bt->rchild);
    }
}

/**
 * p.116: 中序遍历
 */
void Inorder(BinTree bt) {
    if (bt != NULL) {
        Inorder(bt->lchild);
        printf("%c", bt->data);
        Inorder(bt->rchild);
    }
}

/**
 * p.116: 后序遍历
 */
void Postorder(BinTree bt) {
    if (bt != NULL) {
        Postorder(bt->lchild);
        Postorder(bt->rchild);
        printf("%c", bt->data);
    }
}

// 非递归遍历: 自己维护调用栈
// ===============================================================

/**
 * p.117: 中序遍历
 *
 * 当栈顶指向的结点的指针域为非空时, 应该遍历左子树, 即指向左子树根结点的指针进栈
 * 当栈顶指向的结点的指针域为空时, 应退至上一层, 此时
 * - 若是从左子树返回, 则应访问栈顶指向的根结点
 * - 若是从右子树返回, 说明当前层遍历结束, 继续退栈
 */
void Inorder1(BinTree bt) {
    BinTNode *ST[100];
    int top = 0;
    BinTNode *p;
    ST[top++] = bt; // 根结点入栈
    while (top > 0) {   // 栈不为空
        while (ST[top-1] != NULL) {     // 从根结点开始, 所有左子树入栈, 直到左子树空
            ST[top] = ST[top-1]->lchild;
            top++;
        }
        p = ST[--top];  // 空指针退栈
        if (top > 0) {
            printf("%c", ST[top-1]->data); // 访问根结点
            p = ST[--top];                 // 左子树出栈
            ST[top++] = p->rchild;         // 右子树进栈
        }
    }
}

/**
 * p.117: 中序遍历 (使用指针数组实现)
 *
 * 实质与上面改版的 Inorder1 一样
 */
void Inorder2(BinTree bt) {
    BinTNode *ST[100];
    int top = 0;
    ST[top] = bt;
    do {
        while (ST[top] != NULL) {
            top++;
            ST[top] = ST[top-1]->lchild;
        }
        top--;
        if (top >= 0) {
            printf("%c", ST[top]->data);
            ST[top] = ST[top]->rchild;
        }
    } while (top != -1);
}

/**
 * p.118: 前序遍历
 *
 * 与 Inorder1() 一样的原因, 使用 BT 模拟 SeqStack
 */
void Preorder1(BinTree bt) {
    BinTNode *BT[100];  // 初始化栈
    int top = 0;
    BT[top++] = bt;     // 根结点入栈
    while (top > 0) {
        bt = BT[--top];     // 出栈
        if (bt != NULL) {   // 如果结点不为空
            printf("%c", bt->data);  // 访问结点
            BT[top++] = bt->rchild;  // 因为后进先出, 故右子树先入栈
            BT[top++] = bt->lchild;  // 然后左子树入栈
        }
    }
}

/**
 * p.118: 按层遍历
 *
 * 与 Inorder1() 一样的原因, 使用 Q 数组模拟 CirQueue
 */
void TransLevel(BinTree bt) {
    BinTNode *Q[100];
    int front = 0, rear = 0;
    if (bt == NULL) {
        return;
    } else {
        printf("%c", bt->data);
        Q[rear++] = bt;
        while (front != rear) {
            bt = Q[front++];
            if (bt->lchild != NULL) {
                printf("%c", bt->lchild->data);
                Q[rear++] = bt->lchild;
            }
            if (bt->rchild != NULL) {
                printf("%c", bt->rchild->data);
                Q[rear++] = bt->rchild;
            }
        }
    }
}

/**
 * p.120: 求二叉树的深度
 *
 * 若一颗二叉树为空, 则它的深度为 0
 * 否则它的深度等于其左右子树中的最大深度加 1
 */
int BinTreeDepth(BinTree bt) {
    int depl, depr;
    if (bt == NULL) {
        return 0;
    } else {
        depl = BinTreeDepth(bt->lchild);
        depr = BinTreeDepth(bt->rchild);
        if (depl > depr) {
            return depl + 1;
        } else {
            return depr + 1;
        }
    }
}

/**
 * p.120: 按值查找
 *
 * 三种遍历方式都可以用来实现按值查找. 本函数使用前序遍历算法
 */
int found = 0;
BinTNode *p;
void *FindBT(BinTree bt, DataType x) {
    if ((bt != NULL) && (!found)) {
        if (bt->data == x) {
            p = bt;
            found = 1;
            return p;
        } else {
            FindBT(bt->lchild, x);
            FindBT(bt->rchild, x);
        }
    }
    return NULL;
}

/**
 * p.120: 求结点 p 所在的层次
 *
 * lh 指示当前查找的 bt 的层次
 */
int Level(BinTree bt, BinTNode *p, int lh) {
    static int h = 0;
    if (bt == NULL) {
        h = 0;
    } else if (bt == p) {
        h = lh;
    } else {
        Level(bt->lchild, p, lh+1); // 进入左子树查找, 当前层数加 1
        if (h == 0) { // h 为 0 代表左子树未查找到, 进入右子树查找
            Level(bt->rchild, p, lh+1);
        }
    }
    return h;
}

// 测试
// ===============================================================

/**
 * 例中生成的树 t1, t2 都是:
 *
 *          a
 *        /  \
 *      b     c
 *       \
 *        d
 *       / \
 *      e   f
 */
int main(void) {
    char *tree = "(a(b(,d(e,f)),c))";
    BinTree t1 = CreateTree(tree);

    BinTree t2;
    t2 = CreateBinTree(t2); // 输入 abc@d@@@@ef#, 生成与 t1 一样的二叉树

    printf("recursive:\n");
    printf("  - preorder\n");
    printf("  t1: ");
    Preorder(t1); // abdefc
    printf("\n  t2: ");
    Preorder(t2); // abdefc

    printf("\n  - inorder\n");
    printf("  t1: ");
    Inorder(t1);  // bedfac
    printf("\n  t2: ");
    Inorder(t2);  // bedfac

    printf("\n  - postorder\n");
    printf("  t1: ");
    Postorder(t1); // efdbca
    printf("\n  t2: ");
    Postorder(t2); // efdbca

    printf("\n non recursive:\n");
    printf("  - inorder1\n");
    printf("  t1: ");
    Inorder1(t1);  // bedfac
    printf("\n  t2: ");
    Inorder1(t2);  // bedfac

    printf("\n  - inorder2\n");
    printf("  t1: ");
    Inorder2(t1);  // bedfac
    printf("\n  t2: ");
    Inorder2(t2);  // bedfac

    printf("\n  - preorder1\n");
    printf("  t1: ");
    Preorder1(t1); // abdefc
    printf("\n  t2: ");
    Preorder1(t2); // abdefc

    printf("\ntranval level:\n");
    printf("  t1: ");
    TransLevel(t1); // abcdef
    printf("\n  t2: ");
    TransLevel(t2); // abcdef

    printf("\ndepth:\n");
    printf(" t1: %d\n", BinTreeDepth(t1)); // 4
    printf(" t2: %d\n", BinTreeDepth(t2)); // 4

    found = 0; // 全局变量, 在 FindBT() 前定义的
    FindBT(t1, 'a');
    printf("found a in t1: %d\n", found); // 1
    printf("a in t1 is at level: %d\n", Level(t1, p, 1)); // 1

    found = 0;
    FindBT(t2, 'e');
    printf("found e in t2: %d\n", found); // 1
    printf("e in t2 is at level: %d\n", Level(t2, p, 1)); // 4

    found = 0;
    FindBT(t2, 'g');
    printf("found g in t2: %d\n", found); // 0
}