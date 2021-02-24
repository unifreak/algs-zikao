#include <stdio.h>
#include <stdlib.h>

// p.100: 广义表
// ===============================================================

typedef char DataType;

typedef enum {atom, list} NodeTag; // atom = 0 表示原子; list = 1 表示子表

typedef struct GLNode {
    NodeTag tag;        // 区分原子结点还是表结点
    union {
        DataType data;  // 原子结点值
        struct GLNode *slink;  // 指向子表的指针
    };
    struct GLNode *next;       // 指向下一个表结点
} GLNode, *GList;

/**
 * p.100: 创建广义表
 *
 * 遇到左括号 ( 时递归构造子表, 否则构造原子结点
 * 遇见逗号 , 时, 递归构造后续广义表
 * 直到遇到输入结束符 (假设为 ;)
 */
GList CreateGList(GList GL) {
    char ch;
    scanf("%c", &ch);
    if (ch != ' ') {
        GL = (GLNode *) malloc(sizeof(GLNode));
        if (ch == '(') {
            GL->tag = list;
            GL->slink = CreateGList(GL->slink); // 递归调用构造子表
        } else {
            GL->tag = atom;                     // 构造原子结点
            GL->data = ch;
        }
    } else {
        GL = NULL;
    }

    scanf("%c", &ch);
    if (GL != NULL) {
        if (ch == ',') {
            GL->next = CreateGList(GL->next);   // 递归构造后续广义表
        } else {
            GL->next = NULL;                    // 表示遇到 ) 或 ; 时, 无后续表
        }
    }
    return GL;
}

/**
 * p.101: 输出广义表
 */
void PrintGList(GList GL) {
    if (GL != NULL) {
        if (GL->tag == list) {
            printf("(");
            if (GL->slink == NULL) {
                printf(" ");
            } else {
                PrintGList(GL->slink); // 递归调用输出子表
            }
        } else {
            printf("%c", GL->data);    // 输出结点数据域值
        }

        if (GL->tag == list) {
            printf(")");
        }
        if (GL->next != NULL) {
            printf(",");
            PrintGList(GL->next);       // 递归调用输出下一个结点
        }
    }
}

/**
 * p.101: 查找值为 x 的元素, 若查找成功, mark=true, p 指向相应的结点
 */
void FindGListX(GList GL, DataType x, int *mark, GList p) {
    if (GL != NULL) {
        if (GL->tag == atom && GL->data == x) {
            p = GL;
            *mark = 1;
        } else {
            if (GL->tag == list) {
                FindGListX(GL->slink, x, mark, p);
            }
        }
        FindGListX(GL->next, x, mark, p);
    }
}

/**
 * p.102: 求广义表表头
 */
GList head(GList GL) {
    GList p;
    if (GL != NULL && GL->tag != atom) { // 不为空表且不只是原子
        p = GL->slink;
        p->next = NULL;
        return p;
    } else {        // @?: 原子情况呢? 为什么不用处理?
                    // @a: 即使第一个原素是原子, 如 (5, (3, 2)), GL->slink 也正是 5
        return NULL;
    }
}

/**
 * p.102: 求广义表表尾
 * 注意: 表尾不是最后一个元素, 而是除表头之外的所有元素
 */
GList tail(GList GL) {
    GList p;
    if (GL != NULL && GL->tag != 0) {
        p = GL->slink;
        p = p->next;    // p 指向第二个元素
        GL->slink = p;  // 删除广义表第一个元素
    }
    return p;
}

/**
 * p.103: 求广义表深度
 */
void depth(GList GL, int *maxdh) {
    int h;
    if (GL->tag == 0) { // 广义表为单个元素
        *maxdh = 0;
    } else {
        if (GL->tag == 1 && GL->slink == NULL) {
            *maxdh = 1; // 广义表为空表
        } else {        // 进行递归求解
            GL = GL->slink;         // 进入第一层
            *maxdh = 0;
            do {                    // 循环扫描表的第一层的每个结点, 对每个结点求其子表深度
                depth(GL, &h);
                if (h > *maxdh) {   // 取最大的子表深度
                    *maxdh = h;
                }
                GL = GL->next;
            } while (GL != NULL);
            *maxdh += 1;            // 子表最大深度加 1
        }
    }
}

int main(void) {
    GList GL;
    GL = CreateGList(GL); // 输入 (a,(b,c));
    PrintGList(GL);       // 打印 (a,(b,c))

    int d;
    depth(GL, &d);
    printf("\nmax depth: %d\n", d); // 2

    int f = 0, *mark = &f;
    GList p = (GLNode *) malloc(sizeof(GLNode));
    FindGListX(GL, 'a', mark, p);
    // @?: p->data 打印不出来
    printf("\nfound a?:%d, p->tag: %d, p->data: %c\n", f, p->tag, p->data); // 1

    f = 0;
    FindGListX(GL, 'd', mark, p);
    printf("found d?:%d, p->tag: %d, p->data: %c\n", f, p->tag, p->data); // 0

    GList h = (GLNode *) malloc(sizeof(GLNode));
    h = head(GL);
    printf("head data: %c\n", h->data); // a

    // @?: segment fault 11
    // GList t = (GLNode *)malloc(sizeof(GLNode));
    // t = tail(GL);
    // GList h2 = (GLNode *) malloc(sizeof(GLNode));
    // h2 = head(t);
    // printf("head data of tail: %c\n", h2->data);
}