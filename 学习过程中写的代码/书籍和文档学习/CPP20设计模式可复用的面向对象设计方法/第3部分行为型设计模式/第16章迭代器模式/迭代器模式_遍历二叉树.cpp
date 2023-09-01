#include <iostream>

template <typename T>
struct Node;

template <typename T>
struct BinaryTree {
    Node<T> *root { nullptr };

    explicit BinaryTree(Node<T> *const root) : root { root } {
        root->set_tree(this);
    }
};

template <typename T>
struct Node {
    T value;
    Node<T> *left { nullptr };
    Node<T> *right { nullptr };
    Node<T> *parent { nullptr };
    BinaryTree<T> *tree { nullptr };

    explicit Node(T const &value) : value { value } {}

    Node(T const &value, Node<T> *const left, Node<T> *const right)
        : value { value }, left { left }, right { right } {
        this->left->tree = this->right->tree = tree;
        this->left->parent = this->right->parent = this;
    }

    void set_tree(BinaryTree<T> *t) {
        tree = t;
        if (left) {
            left->set_tree(t);
        }
        if (right) {
            right->set_tree(t);
        }
    }
};

template <typename U>
struct PreOrderIterator {
    Node<U> *current;

    explicit PreOrderIterator(Node<U> *current) : current { current } {}

    bool operator!=(PreOrderIterator<U> &other) {
        return current != other.current;
    }

    Node<U> &operator*() { return *current; }

    PreOrderIterator<U> &operator++() {
        if (current->right) {
            current = current->right;
            while (current->left) {
                current = current->left;
            }
        } else {
            Node<U> *p { current->parent };
            while (p && current == p->right) {
                current = p;
                p = p->parent;
            }
            current = p;
        }
        return *this;
    }

    // using iterator = PreOrderIterator<U>;

    // iterator begin() { Node<U> *n = root;
    //  }
};

int main(int argc, char *argv[]) { return 0; }
