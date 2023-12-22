#include <iostream>

/*
1.将两个降序链表合并为一个新的降序链表并返回，
合并后的链表是通过拼接给定的两个链表的所有节点组成的（15分）
示例：
链表1: 5->2->1
链表2: 6->3->1
合并后为：6->5->3->2->1->1，合并后的链表节点全部来源于链表1和链表2

*/

struct Node {
    int value {};
    Node *next {};
};

Node *slove(Node *n1, Node *n2) {
    if (n1 == nullptr) {
        return n2;
    }
    if (n2 == nullptr) {
        return n1;
    }
    Node *res = new Node { -1 };
    Node *temp = res;
    while (n1 && n2) {
        if (n1->value > n2->value) {
            temp->next = n1;
            n1 = n1->next;
        } else {
            temp->next = n2;
            n2 = n2->next;
        }
        temp = temp->next;
    }
    if (n1) {
        temp->next = n1;
    }
    if (n2) {
        temp->next = n2;
    }
    return res->next;
}

void printList(Node *n) {
    while (n) {
        std::cout << n->value << " ";
        n = n->next;
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    // 链表1: 5->2->1
    // 链表2: 6->3->1
    Node *n1 = new Node { 5 };
    n1->next = new Node { 2 };
    n1->next->next = new Node { 1 };
    printList(n1);

    Node *n2 = new Node { 6 };
    n2->next = new Node { 3 };
    n2->next->next = new Node { 1 };
    printList(n2);
    printList(slove(n1, n2));

    return 0;
}
