#include <iostream>
#include <string>

struct Node {
    int value;
    Node *left;
    Node *right;
    Node(int value) : value(value), left(nullptr), right(nullptr) {}
};

// 序列化
std::string serialByPreHelp(Node *head) {
    if (head == nullptr) {
        return "#!";
    }
    std::string res = std::to_string(head->value) + "!";
    res = res + serialByPreHelp(head->left);
    res = res + serialByPreHelp(head->right);
    return res;
}

// 反序列化
Node *deSerialByPreHelp(char *&str) {
    if (*str == '#') {
        str++; // skip '#'
        str++; // skip '!'
        return nullptr;
    }
    int val = 0;
    while (*str != '!') { // process such '123'
        val = 10 * val + (*str - '0');
        str++;
    }
    str++;
    Node *root = new Node(val); // recur
    root->left = deSerialByPreHelp(str);
    root->right = deSerialByPreHelp(str);
    return root;
}

// 反序列化
Node *deSerialByPre(char *str) {
    if (str == nullptr || *str == '#') { // if null
        return nullptr;
    }
    return deSerialByPreHelp(str);
}

// 前序遍历
void preOrderRecur(Node *head) {
    if (head == nullptr) {
        return;
    }
    std::cout << head->value << ",";
    preOrderRecur(head->left);
    preOrderRecur(head->right);
}

int main() {

    Node *head = new Node(5);
    head->left = new Node(3);
    head->right = new Node(8);
    head->left->left = new Node(2);
    head->left->right = new Node(4);
    head->right->left = new Node(7);
    head->right->right = new Node(10);
    head->right->left->left = new Node(6);
    head->right->right->left = new Node(9);
    head->right->right->right = new Node(11);

    std::cout << "pre-order: ";
    preOrderRecur(head);
    std::cout << "\nserial binary: ";
    std::string res = serialByPreHelp(head);
    std::cout << res << std::endl;
    char *s_char = (char *)res.c_str(); // convert string to char*
    Node *dehead = deSerialByPre(s_char);
    std::cout << "deserial binary: ";
    preOrderRecur(dehead);

    return 0;
}
