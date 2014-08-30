//
//  RBTree.h
//  Code
//
//  Created by Zhi Xing on 8/24/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#ifndef __Code__RBTree__
#define __Code__RBTree__

#include <stack>

namespace Code {
    template <typename T>
    class RBTree {
    public:
        RBTree(): _root(nullptr), _size(0) {}
        RBTree(const RBTree<T> &other);
        RBTree(RBTree<T> &&other);
        ~RBTree();
        RBTree<T> &operator=(const RBTree<T> &other);
        RBTree<T> &operator=(RBTree<T> &&other);
        int size() const;
        void insert(const T &value);
        void remove(const T &value);
        void inorderTraversal(void (*)(T&));
        void preorderTraversal(void (*)(T&));
        void postorderTraversal(void (*)(T&));

    private:
        struct Node {
            T elem;
            bool red;
            Node *left;
            Node *right;
            Node *parent;
            Node(const T &value): elem(value), red(true), left(nullptr), right(nullptr), parent(nullptr) {}
        };
        
        Node *_root;
        int _size;
        
        void _clean(Node *root);
        Node *_copy(const Node *root);
        void _insertBalance(Node *node);
        void _removeBalance(Node *remove, Node *replace);
        Node *_rotateLeft(Node *root);
        Node *_rotateRight(Node *root);
    };
}

using namespace std;
using namespace Code;

///////////////////////////////////////////////////////////////////////////////
template <typename T>
RBTree<T>::RBTree(const RBTree<T> &other): _root(_copy(other._root)), _size(other._size) {}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
RBTree<T>::RBTree(RBTree<T> &&other): _root(other._root), _size(other._size) {
    other._root = nullptr;
    other._size = 0;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
RBTree<T>::~RBTree() {
    _clean(_root);
    _root = nullptr;
    _size = 0;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
RBTree<T> &RBTree<T>::operator=(const RBTree<T> &other) {
    _clean(_root);
    _root = _copy(other._root);
    _size = other._size;
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
RBTree<T> &RBTree<T>::operator=(RBTree<T> &&other) {
    _clean(_root);
    _root = other._root;
    _size = other._size;
    other._root = nullptr;
    other._size = 0;
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
int RBTree<T>::size() const {
    return _size;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void RBTree<T>::insert(const T &value) {
    Node *cur = _root, *prev = nullptr;
    while (cur) {
        prev = cur;
        if (value < cur->elem)
            cur = cur->left;
        else if (value > cur->elem)
            cur = cur->right;
        else // value == cur->elem
            return;
    }
    
    Node *newNode = new Node(value);
    if (!prev)
        _root = newNode;
    else if (value < prev->elem) {
        prev->left = newNode;
        newNode->parent = prev;
    }
    else { // value > prev->elem
        prev->right = newNode;
        newNode->parent = prev;
    }
    
    _insertBalance(newNode);
    ++_size;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void RBTree<T>::remove(const T &value) {
    Node *cur = _root;
    while (cur) {
        if (value < cur->elem)
            cur = cur->left;
        else if (value > cur->elem)
            cur = cur->right;
        else // value == cur->elem;
            break;
    }
    
    if (!cur)
        return;
    
    if (cur->left) {
        Node *tmp = cur;
        cur = cur->left;
        while (cur->right)
            cur = cur->right;
        tmp->elem = cur->elem;
    }
    
    Node *replace = cur->left ? cur->left : cur->right;
    if (!cur->parent) {
        _root = replace;
    }
    else if (cur->parent->left == cur) {
        cur->parent->left = replace;
        if (replace)
            replace->parent = cur->parent;
    }
    else if (cur->parent->right == cur) {
        cur->parent->right = replace;
        if (replace)
            replace->parent = cur->parent;
    }
    
    _removeBalance(cur, replace);
    delete cur;
    --_size;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void RBTree<T>::inorderTraversal(void (*operation)(T&)) {
    stack<Node*> stk;
    Node *cur = _root;
    while (cur || !stk.empty()) {
        if (cur) {
            stk.push(cur);
            cur = cur->left;
        }
        else {
            cur = stk.top();
            stk.pop();
            operation(cur->elem);
            cur = cur->right;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void RBTree<T>::preorderTraversal(void (*operation)(T&)) {
    stack<Node*> stk;
    Node *cur = _root;
    while (cur || !stk.empty()) {
        if (cur) {
            operation(cur->elem);
            stk.push(cur);
            cur = cur->left;
        }
        else {
            cur = stk.top()->right;
            stk.pop();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void RBTree<T>::postorderTraversal(void (*operation)(T&)) {
    stack<Node*> stk;
    Node *cur = _root, *prev = nullptr;
    while (cur || !stk.empty()) {
        if (cur) {
            stk.push(cur);
            cur = cur->left;
        }
        else {
            cur = stk.top();
            if (!cur->right || cur->right == prev) {
                stk.pop();
                operation(cur->elem);
                prev = cur;
                cur = nullptr;
            }
            else
                cur = cur->right;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void RBTree<T>::_clean(Node *root) {
    if (!root)
        return;
    if (root->left)
        _clean(root->left);
    if (root->right)
        _clean(root->right);
    delete root;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
typename RBTree<T>::Node *RBTree<T>::_copy(const Node *root) {
    if (!root)
        return nullptr;
    Node *newRoot = new Node(root->elem);
    newRoot->red = root->red;
    if (root->left) {
        newRoot->left = _copy(root->left);
        newRoot->left->parent = newRoot;
    }
    if (root->right) {
        newRoot->right = _copy(root->right);
        newRoot->right->parent = newRoot;
    }
    return newRoot;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void RBTree<T>::_insertBalance(Node *node) {
    if (!node->parent) { // root
        node->red = false;
        return;
    }
    if (!node->parent->red) // parent is black
        return;
    
    // parent is red (so parent is not root)
    Node *parent = node->parent;
    Node *grand = parent->parent;
    Node *uncle = grand->left == parent ? grand->right : grand->left;
    if (uncle && uncle->red) { // uncle is red
        parent->red = false;
        uncle->red = false;
        grand->red = true;
        _insertBalance(grand);
    }
    // uncle is black
    else if (grand->left == parent) {
        if (parent->right == node) { // left-right
            _rotateLeft(parent);
            node->red = false;
            grand->red = true;
        }
        else { // left-left
            parent->red = false;
            grand->red = true;
        }
        _rotateRight(grand);
    }
    else { // grand->right == parent
        if (parent->left == node) { // right-left
            _rotateRight(parent);
            node->red = false;
            grand->red = true;
        }
        else { // right-right
            parent->red = false;
            grand->red = true;
        }
        _rotateLeft(grand);
    }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void RBTree<T>::_removeBalance(Node *remove, Node *replace) {
    if (remove->red || (replace && replace->red) || !remove->parent) { // one of the nodes is red or node is root
        if (replace)
            replace->red = false;
        return;
    }
 
    Node *parent = remove->parent;
    Node *sibling = (parent->left == replace ? parent->right : parent->left);
    
    if (sibling->red) { // red sibling
        sibling->red = false;
        parent->red = true;
        if (parent->left == sibling)
            _rotateRight(parent);
        else // parent->right == sibling
           _rotateLeft(parent);
    }
    else if ((!sibling->left || !sibling->left->red) && (!sibling->right || !sibling->right->red)) { // black sibling with black nephews
        sibling->red = true;
        if (parent->red)
            parent->red = false;
        else {
            parent->red = false;
            _removeBalance(parent, parent);
        }
    }
    // black sibling with at least one red nephew
    else if (parent->left == sibling) {
        if (sibling->left && sibling->left->red) // left-left
            sibling->left->red = false;
        else { // left-right
            sibling->right->red = false;
            _rotateLeft(sibling);
        }
        _rotateRight(parent);
    }
    else { // parent->right == sibling
        if (sibling->right && sibling->right->red) // right-right
            sibling->right->red = false;
        else { // right->left
            sibling->left->red = false;
            _rotateRight(sibling);
        }
        _rotateLeft(parent);
    }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
typename RBTree<T>::Node *RBTree<T>::_rotateLeft(Node *root) {
    if (!root || !root->right)
        return root;
    
    Node *newRoot = root->right;
    
    newRoot->parent = root->parent;
    if (root->parent)
        (root->parent->left == root ? root->parent->left : root->parent->right) = newRoot;
    else
        _root = newRoot;
    
    if (newRoot->left)
        newRoot->left->parent = root;
    root->right = newRoot->left;
    
    root->parent = newRoot;
    newRoot->left = root;
    
    return newRoot;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
typename RBTree<T>::Node *RBTree<T>::_rotateRight(Node *root) {
    if (!root || !root->left)
        return root;
    
    Node *newRoot = root->left;
    
    newRoot->parent = root->parent;
    if (root->parent)
        (root->parent->left == root ? root->parent->left : root->parent->right) = newRoot;
    else
        _root = newRoot;
    
    if (newRoot->right)
        newRoot->right->parent = root;
    root->left = newRoot->right;
    
    root->parent = newRoot;
    newRoot->right = root;
    
    return newRoot;
}

#endif /* defined(__Code__RBTree__) */
