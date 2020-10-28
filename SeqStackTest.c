#include "SeqStack.c"

void dump(SeqStack *S) {
    printf("[top: %d --", S->top);
    for (int i = 0; i <= S->top; i++) {
        printf("%c,", S->data[i]);
    }
    printf("]\n");
}

int main(void) {
    SeqStack s, *S = &s;
    InitStack(S);
    dump(S);

    Push(S, 'a');
    Push(S, 'b');
    printf("top: %c\n", GetTop(S)); // b

    char ch = Pop(S);
    printf("got: %c, top: %c\n", ch, GetTop(S)); // b, a

    // ===============================================================

    int match = Expr(); // 输入一些小括号, 如 ((())
    printf("bracket match: %d\n", match); // 打印小括号个数是否匹配, 如 0 不匹配

    char word[10];
    gets(word);
    int sym;
    sym = symmetry(word); // 输入一串字符, 如 abcba
    printf("%s is symmetry: %d\n", word, sym); // 打印是否是回文, 如 1 是

    printf("10 based number 3553 is 8 based number:");
    conversion(3553, 8); // 6741
}