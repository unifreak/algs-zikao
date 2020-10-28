#include "CirQueue.c"
#include "SeqStack.c"

/**
 * p.82: 判断运算符优先级别
 */
int Priority(DataType op) {
    switch (op) {
        case '(':
        case '#': return 0;
        case '-':
        case '+': return 1;
        case '*':
        case '/': return 2;
    }
    return -1;
}

/**
 * p.83: 把中缀表达式转换为后缀表达式
 */
void CTPostExp(CirQueue *Q) {
    SeqStack S;                 // 运算符栈
    char c, t;
    InitStack(&S);
    Push(&S, '#');              // # 用于标识栈底
    do {
        c = getchar();
        switch(c) {
            case ' ': break;    // 去除空格符
            case '0':           // 数字入队
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': EnQueue(Q, c); break;
            case '(': Push(&S, c); break;
            case ')':           // 遇到 ) 或输入结束, 则把最后的 ( ) 内的操作符入队
            case '#':
                do {
                    t = Pop(&S);
                    if (t != '(' && t!= '#') EnQueue(Q, t);
                } while (t != '(' && S.top != -1);
                break;
            case '+':           // 当前操作符入栈. 如果有比当前操作符优先级高的操作符, 则统统入队
            case '-':
            case '*':
            case '/':
                while (Priority(c) <= Priority(GetTop(&S))) {
                    t = Pop(&S);
                    EnQueue(Q, t);
                }
                Push(&S, c);
                break;
        }
    } while (c != '#');
}

/**
 * p.83: 计算后缀表达式
 */
int CPostExp(CirQueue *Q) {
    SeqStack S;
    char ch;
    int x, y;
    InitStack(&S);
    while (! QueueEmpty(Q)) {
        ch = DeQueue(Q);
        if (ch >= '0' && ch <= '9') {
            Push(&S, ch - '0');
        } else {
            y = Pop(&S);
            x = Pop(&S);
            switch (ch) {
                case '+': Push(&S, x + y); break;
                case '-': Push(&S, x - y); break;
                case '*': Push(&S, x * y); break;
                case '/': Push(&S, x / y); break;
            }
        }
    }
    return GetTop(&S);
}