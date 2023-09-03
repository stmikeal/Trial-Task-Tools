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
        int width;
        T data;

        explicit Node(const T &data = T())
                : left_child(nullptr), right_child(nullptr), parent(nullptr), data(data), height(0), width(1) {};

        ~Node() {
            delete left_child;
            delete right_child;
        }

        inline T get_left_value() { return this->left_child != nullptr ? this->left_child->data : static_cast<T>(INT32_MIN); }

        inline T get_right_value() { return this->right_child != nullptr ? this->right_child->data : static_cast<T>(INT32_MAX); }

        inline int get_left_width() { return this->left_child != nullptr ? this->left_child->width : 0; }

        inline int get_right_width() { return this->right_child != nullptr ? this->right_child->width : 0; }

        inline void set_new_width() { this->width = this->get_left_width() + this->get_right_width() + 1; }

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

    T min_at(int position, int depth = 0, Node *pivot = nullptr);

    size_t count_less(const T &key, int depth = 0, Node *pivot = nullptr);
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
    if (temp != nullptr)
        temp->parent = pivot;
    pivot->right_child->left_child = pivot;
    pivot->right_child = temp;
    pivot->set_new_height();
    pivot->parent->set_new_height();
    pivot->set_new_width();
    pivot->parent->set_new_width();
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
    if (temp != nullptr)
        temp->parent = pivot;
    pivot->left_child->right_child = pivot;
    pivot->left_child = temp;
    pivot->set_new_height();
    pivot->parent->set_new_height();
    pivot->set_new_width();
    pivot->parent->set_new_width();
}

template<typename T>
void BalancedTree<T>::_balance(BalancedTree::Node *pivot) {
    pivot->set_new_height();
    pivot->set_new_width();
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
T BalancedTree<T>::min_at(int position, int depth, BalancedTree<T>::Node *pivot) {
    if (this->root == nullptr)
        throw std::out_of_range("Tree is empty!");

    if (pivot == nullptr)
        pivot = this->root;

    if (pivot->width + depth < position || position <= 0)
        throw std::out_of_range("Position is out of tree.");

    if (position - depth <= pivot->get_left_width())
        return min_at(position, depth, pivot->left_child);
    else if (position - depth == pivot->get_left_width() + 1)
        return pivot->data;
    else
        return min_at(position, pivot->get_left_width()+ depth + 1, pivot->right_child);
}

template<typename T>
size_t BalancedTree<T>::count_less(const T &key, int depth, Node *pivot) {
    if (this->root == nullptr)
        return 0;

    if (pivot == nullptr)
        pivot = this->root;

    if (key > pivot->data) {
        if (pivot->right_child == nullptr)
            return depth + pivot->get_left_width() + 1;
        else
            return count_less(key, depth + pivot->get_left_width() + 1, pivot->right_child);
    } else if (key < pivot->data) {
        if (pivot->left_child == nullptr)
            return depth;
        else
            return count_less(key, depth, pivot->left_child);
    } else if (pivot->left_child == nullptr || pivot->left_child->data != key) {
        return depth + pivot->get_left_width();
    } else {
        return count_less(key, depth, pivot->left_child);
    }
}
