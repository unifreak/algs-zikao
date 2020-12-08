#include "LinkList.c"

int main(void) {
    LinkList La = CreateListF(); // 输入 abc
    dumpLinkList(La); // |0:c| -> |1:b| -> |2:a| ->

    LinkList Lb = CreateListR(); // 输入 abc
    dumpLinkList(Lb); // |0:a| -> |1:b| -> |2:c| ->

    LinkList Lc = CreateListR1(); // 输入 abc
    dumpLinkList(Lc); // |0:| -> |1:a| -> |2:b| -> |3:c| ->

    ListNode *p = GetNode(Lc, 2);
    printf("%c\n", p->data); // b

    p = LocateNodeK(Lc, 'c');
    printf("%c\n", p->data); // c

    InsertList(Lc, 4, 'd');
    dumpLinkList(Lc); // |0:| -> |1:a| -> |2:b| -> |3:c| -> |4:d| ->

    DeleteList(Lc, 4);
    dumpLinkList(Lc); // |0:| -> |1:a| -> |2:b| -> |3:c| ->

    LinkList Ld = CreateListR1(); // 不输入
    Split(Lc, Ld);
    dumpLinkList(Lc); // |0:| -> |1:a| -> |2:c| ->
    dumpLinkList(Ld); // |0:d| -> |1:b| ->

    dumpLinkList(MergeList(Lc, Ld)); // |0:| -> |1:a| -> |2:b| -> |3:c| ->
}