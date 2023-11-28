#include "CirQueue.c"
#include "SeqStack.c"

// 栈和队列的用例: 计算中缀表达式
// 这个实现规定: 只处理 +, -, *, / 四种运算符, 以及一位数字操作数 (0~9)
// ===============================================================

/**
 * p.82: 判断运算符优先级别
 */
int Priority(DataType op) {
    switch (op) {
        case '(':
        case '#': return 0; // # 用于表示输入结束
        case '-':
        case '+': return 1;
        case '*':
        case '/': return 2;
    }
    return -1;
}

/**
 * p.83: 把中缀表达式转换为后缀表达式
 *
 * 使用栈追踪运算符的优先级
 * 最终的后缀表达式存入队列中
 *
 * 如转换中缀表达式 8*5-(7+3)#
 *      8 入队: 8
 *      * 入栈: *
 *      5 入队: 85
 *      * 出栈, - 入栈: 85*
 *      ( 入栈: -(
 *      7 入队: 85*7
 *      + 入栈: -(+
 *      3 入队: 85*73
 *      遇到 ) 出所有栈中 ( 之后运算符以及 ( 本身: 85*73+
 *      遇到 # 把栈中所有运算符入队: 85*73+-
 * 最终结果: 85*73+-
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
    SeqStack S; // 保存中间结果, 因为最后计算出的中间结果在后续最先参与计算. 故使用后进先出的栈
    char ch;
    int x, y;
    InitStack(&S);
    while (! QueueEmpty(Q)) {
        ch = DeQueue(Q);
        if (ch >= '0' && ch <= '9') { // 遇到数字则入栈
            Push(&S, ch - '0');
        } else { // 遇到运算符则取出栈中的操作数, 参与计算. 并保存中间结果
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
    return GetTop(&S); // 最终结果
}