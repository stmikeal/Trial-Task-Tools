#pragma once

#include <stack>

/**
 * BalancedTree is a class implementing AVL-tree algorithm.
 * Definition part.
 * @tparam T type of the keys containing in this tree;
 */
template<typename T>
class BalancedTree {
private:
    /**
     * Class representing one node of the tree.
     */
    class Node {
    public:
        Node *left_child;
        Node *right_child;
        Node *parent;
        int height;
        T data;

        explicit Node(const T &data = T())
                : left_child(nullptr), right_child(nullptr), parent(nullptr), data(data), height(0) {};

        ~Node() {
            delete left_child;
            delete right_child;
        }

        inline int get_left_height() { return this->left_child != nullptr ? this->left_child->height + 1 : 0; }

        inline int get_right_height() { return this->right_child != nullptr ? this->right_child->height + 1 : 0; }

        inline int b_factor() { return this->get_left_height() - this->get_right_height(); }

        inline void set_new_height() { this->height = std::max(this->get_left_height(), this->get_right_height()); }
    };

    Node *root;

    void _balance(Node *pivot);

    void _right_rotate(Node *pivot);

    void _left_rotate(Node *pivot);

    void _big_right_rotate(Node *pivot);

    void _big_left_rotate(Node *pivot);

public:
    BalancedTree() : root(nullptr) {};

    virtual ~BalancedTree() { delete root; }

    void insert(const T &key);

    void min_at(const T &key);

    void count_less(const T &key);
};

template<typename T>
void BalancedTree<T>::_big_left_rotate(BalancedTree::Node *pivot) {
    this->_right_rotate(pivot->right_child);
    this->_left_rotate(pivot);
}

template<typename T>
void BalancedTree<T>::_big_right_rotate(BalancedTree::Node *pivot) {
    this->_left_rotate(pivot->left_child);
    this->_right_rotate(pivot);
}

template<typename T>
void BalancedTree<T>::_left_rotate(BalancedTree::Node *pivot) {
    if (pivot->parent != nullptr) {
        if (pivot->parent->left_child == pivot)
            pivot->parent->left_child = pivot->right_child;
        else
            pivot->parent->right_child = pivot->right_child;
    } else {
        this->root = pivot->right_child;
    }
    pivot->right_child->parent = pivot->parent;
    pivot->parent = pivot->right_child;
    auto temp = pivot->right_child->left_child;
    pivot->right_child->left_child = pivot;
    pivot->right_child = temp;
    pivot->set_new_height();
    pivot->parent->set_new_height();
}

template<typename T>
void BalancedTree<T>::_right_rotate(BalancedTree::Node *pivot) {
    if (pivot->parent != nullptr) {
        if (pivot->parent->left_child == pivot)
            pivot->parent->left_child = pivot->left_child;
        else
            pivot->parent->right_child = pivot->left_child;
    } else {
        this->root = pivot->left_child;
    }
    pivot->left_child->parent = pivot->parent;
    pivot->parent = pivot->left_child;
    auto temp = pivot->left_child->right_child;
    pivot->left_child->right_child = pivot;
    pivot->left_child = temp;
    pivot->set_new_height();
    pivot->parent->set_new_height();
}

template<typename T>
void BalancedTree<T>::_balance(BalancedTree::Node *pivot) {
    pivot->set_new_height();
    int b_factor = pivot->b_factor();

    if (b_factor == 2) {
        if (pivot->left_child->get_right_height() <= pivot->left_child->get_left_height())
            _right_rotate(pivot);
        else
            _big_right_rotate(pivot);
    } else if (b_factor == -2) {
        if (pivot->right_child->get_left_height() <= pivot->right_child->get_right_height())
            _left_rotate(pivot);
        else
            _big_left_rotate(pivot);
    }
}

template<typename T>
void BalancedTree<T>::insert(const T &key) {
    auto *new_element = new BalancedTree<T>::Node(key);

    BalancedTree<T>::Node *prev = nullptr;
    BalancedTree<T>::Node *next = this->root;

    if (next == nullptr) {
        this->root = new_element;
        return;
    }

    std::stack<BalancedTree<T>::Node *> stack{};

    while (next != nullptr) {
        prev = next;
        stack.push(prev);
        if (next->data < key)
            next = next->right_child;
        else
            next = next->left_child;
    }
    stack.push(new_element);

    new_element->parent = prev;

    if (prev->data < key)
        prev->right_child = new_element;
    else
        prev->left_child = new_element;

    while (!stack.empty()) {
        auto vertex = stack.top();
        this->_balance(vertex);
        stack.pop();
    }

}

template<typename T>
void BalancedTree<T>::min_at(const T &key) {

}

template<typename T>
void BalancedTree<T>::count_less(const T &key) {

}
